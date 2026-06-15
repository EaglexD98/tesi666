//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 

#include "TelemetrySenderUdpFinal.h"

#include <algorithm>
#include <cctype>
#include <cstring>
#include <sstream>
#include <inet/common/packet/Packet.h>
#include <inet/common/packet/chunk/BytesChunk.h>
#include <inet/common/TimeTag_m.h>
#include "inet/linklayer/ieee80211/mgmt/Ieee80211AgentSta.h"
#include "inet/linklayer/ieee80211/mib/Ieee80211Mib.h"
#include "inet/linklayer/ieee80211/mac/Ieee80211Mac.h"
#include <inet/linklayer/ieee80211/mgmt/Ieee80211MgmtSta.h>
#include <inet/networklayer/common/InterfaceTable.h>

namespace simu5g {

Define_Module(TelemetrySenderUdpFinal);

using namespace omnetpp;
using namespace inet;

TelemetrySenderUdpFinal::~TelemetrySenderUdpFinal()
{
    cancelAndDelete(connectTimer_);
    cancelAndDelete(sampleTimer_);
    cancelAndDelete(burstTimer_);
    cancelAndDelete(helloTimer_);
    cancelAndDelete(conditionTimer_);
    cancelAndDelete(microDelayTimer_);

}

void TelemetrySenderUdpFinal::initialize(int stage)
{
    cSimpleModule::initialize(stage);

    if (stage == INITSTAGE_LOCAL) {
        associatedSignal_ = cComponent::registerSignal("l2AssociatedNewAp");
        associatedOldApSignal_ = cComponent::registerSignal("l2AssociatedOldAp");
        disassociatedSignal_ = cComponent::registerSignal("l2Disassociated");
        return;
    }

    if (stage != INITSTAGE_APPLICATION_LAYER)
        return;

    localPort_ = par("localPort");
    connectPort_ = par("connectPort");
    sampleInterval_ = par("sampleInterval");
    burstInterval_ = par("burstInterval");
    helloInterval_ = par("helloInterval");
    conditionCheckInterval_ = par("conditionCheckInterval");
    reconnectInterval_ = par("reconnectInterval");
    startTime_ = par("startTime");

    activeBuffer_ = &bufferA_;
    inactiveBuffer_ = &bufferB_;

    socket.setOutputGate(gate("socketOut"));
    socket.setCallback(this);

    // CORRECCIÓN: Para evitar el error de "Unknown socket" al recibir respuestas,
    // debemos hacer bind() explícitamente si se ha proporcionado un puerto válido.
    if (localPort_ != -1 && !socket.isOpen()) {
        socket.bind(localPort_);
    }

    connectTimer_ = new cMessage("connectTimer");
    sampleTimer_ = new cMessage("sampleTimer");
    burstTimer_ = new cMessage("burstTimer");
    helloTimer_ = new cMessage("helloTimer");
    conditionTimer_ = new cMessage("conditionTimer");
    microDelayTimer_ = new cMessage("microDelayTimer");

    parseRouteStopsParameter();
    parseValidStopsParameter();
    updateMobilityHandles();

    cModule* host = getContainingNode(this);
    if (host) {
        host->subscribe(associatedSignal_, this);
        host->subscribe(associatedOldApSignal_, this);
        host->subscribe(disassociatedSignal_, this);

        if (cModule* wlan = host->getSubmodule("wlan", 0)) {
            wlan->subscribe(associatedSignal_, this);
            wlan->subscribe(associatedOldApSignal_, this);
            wlan->subscribe(disassociatedSignal_, this);

            if (cModule* mgmt = wlan->getSubmodule("mgmt")) {
                mgmt->subscribe(associatedSignal_, this);
                mgmt->subscribe(associatedOldApSignal_, this);
                mgmt->subscribe(disassociatedSignal_, this);
                EV_INFO << "Aplicación suscrita directamente a wlan[0].mgmt en " << getVehicleId() << endl;
            }

            if (cModule* agent = wlan->getSubmodule("agent")) {
                agent->subscribe(associatedSignal_, this);
                agent->subscribe(associatedOldApSignal_, this);
                agent->subscribe(disassociatedSignal_, this);
                EV_INFO << "Aplicación suscrita directamente al agente WiFi en " << getVehicleId() << endl;
            }
        }
    }

    scheduleAt(simTime() + startTime_, sampleTimer_);
    scheduleAt(simTime() + startTime_ + conditionCheckInterval_, conditionTimer_);
    scheduleAt(simTime() + startTime_ + burstInterval_, burstTimer_);
}
void TelemetrySenderUdpFinal::handleMessage(cMessage* msg)
{
    if (msg->isSelfMessage()) {
        if (msg == connectTimer_) {
            // CORRECCIÓN: Quitamos el check de isOpen(). En UDP no hace falta.
            if (apAssociated_ && !isConnected_) {
                doConnect();
            }
        }
        else if (msg == sampleTimer_) {
            takeSample();
            scheduleAt(simTime() + sampleInterval_, sampleTimer_);
        }
        else if (msg == burstTimer_) {
            if (state_ == TX_ACTIVE && canTransmitNow()) {
                swapBuffersAndQueue();
                triggerBurst();
            }
            scheduleAt(simTime() + burstInterval_, burstTimer_);
        }
        else if (msg == microDelayTimer_) {
            sendNextBurstPacket();
        }
        else if (msg == helloTimer_) {
            if (stateAllowsHello() && !isConnected_) {
                sendHello(canTransmitNow());
                scheduleAt(simTime() + helloInterval_, helloTimer_);
            }
        }
        else if (msg == conditionTimer_) {
            updateStopContext();
            evaluateTransmissionWindow();
            scheduleAt(simTime() + conditionCheckInterval_, conditionTimer_);
        }
        return;
    }

    socket.processMessage(msg);
}

void TelemetrySenderUdpFinal::finish()
{
    if (state_ == TX_ACTIVE || state_ == TX_CLOSING)
        sendEndSession("finish");

    if (!activeBuffer_->empty())
        swapBuffersAndQueue();

    if (isConnected_)
        triggerBurst();

    cModule* host = getContainingNode(this);
    if (host) {
        host->unsubscribe(associatedSignal_, this);
        host->unsubscribe(associatedOldApSignal_, this);
        host->unsubscribe(disassociatedSignal_, this);

        if (cModule* wlan = host->getSubmodule("wlan", 0)) {
            wlan->unsubscribe(associatedSignal_, this);
            wlan->unsubscribe(associatedOldApSignal_, this);
            wlan->unsubscribe(disassociatedSignal_, this);

            if (cModule* mgmt = wlan->getSubmodule("mgmt")) {
                mgmt->unsubscribe(associatedSignal_, this);
                mgmt->unsubscribe(associatedOldApSignal_, this);
                mgmt->unsubscribe(disassociatedSignal_, this);
            }
            if (cModule* agent = wlan->getSubmodule("agent")) {
                agent->unsubscribe(associatedSignal_, this);
                agent->unsubscribe(associatedOldApSignal_, this);
                agent->unsubscribe(disassociatedSignal_, this);
            }
        }
    }
}

void TelemetrySenderUdpFinal::updateMobilityHandles()
{
    if (!mobility_)
        mobility_ = dynamic_cast<IMobility*>(getContainingNode(this)->getSubmodule("mobility"));

    if (!veinsMobility_)
        veinsMobility_ = dynamic_cast<veins::VeinsInetMobility*>(mobility_);

    if (veinsMobility_) {
        if (!traci_)
            traci_ = veinsMobility_->getCommandInterface();
        if (!traciVehicle_)
            traciVehicle_ = veinsMobility_->getVehicleCommandInterface();
    }
}

void TelemetrySenderUdpFinal::takeSample()
{
    updateMobilityHandles();

    double co2 = 0;
    double speed = 0;
    Coord pos(0, 0, 0);

    if (mobility_) {
        pos = mobility_->getCurrentPosition();
        speed = mobility_->getCurrentVelocity().length();
    }
    if (traciVehicle_)
        co2 = traciVehicle_->getCO2Emissions();

    TelemetrySampleUdpFinal s;
    s.seq = sequenceNumber_++;
    s.posX = pos.x;
    s.posY = pos.y;
    s.speed = speed;
    s.co2 = co2;
    s.sampleTimeSec = simTime().dbl();

    activeBuffer_->push_back(s);
}

void TelemetrySenderUdpFinal::updateStopContext()
{
    updateMobilityHandles();

    bool oldAtBusStop = stopCtx_.atBusStop;

    stopCtx_.stopped = false;
    stopCtx_.atBusStop = false;
    stopCtx_.rawStopState = 0;
    stopCtx_.currentLaneId.clear();

    if (!traciVehicle_)
        return;

    stopCtx_.rawStopState = traciVehicle_->getStopState();
    stopCtx_.stopped = (stopCtx_.rawStopState & 0x01) != 0;
    stopCtx_.atBusStop = (stopCtx_.rawStopState & 0x10) != 0;
    stopCtx_.currentLaneId = traciVehicle_->getLaneId();

    // RESTAURADO: Log de depuración exacto de TraCI
    EV_INFO << "--- DEPURA TraCI: Node=" << getVehicleId() 
            << " rawState=0x" << std::hex << (int)stopCtx_.rawStopState << std::dec 
            << " bits(stopped=" << (int)((stopCtx_.rawStopState & 0x01) != 0)
            << ", atBusStop=" << (int)((stopCtx_.rawStopState & 0x10) != 0) << ")" << endl;

    if (stopCtx_.atBusStop && !oldAtBusStop) {
        if (!routeStops_.empty()) {
            stopCtx_.currentStopId = routeStops_[nextStopIndex_];
            nextStopIndex_ = (nextStopIndex_ + 1) % routeStops_.size();
        }
        EV_INFO << "Bus " << getVehicleId() << " entró a bus stop estimada=" << stopCtx_.currentStopId
                << " lane=" << stopCtx_.currentLaneId << " AP=" << currentApId_ << endl;
    }
    else if (!stopCtx_.atBusStop && oldAtBusStop) {
        EV_INFO << "Bus " << getVehicleId() << " salió de bus stop " << stopCtx_.currentStopId << endl;
    }

    previousAtBusStop_ = stopCtx_.atBusStop;
}

bool TelemetrySenderUdpFinal::hasValidStop() const
{
    return validStops_.count(stopCtx_.currentStopId) > 0;
}

bool TelemetrySenderUdpFinal::stateAllowsHello() const
{
    return apAssociated_ && (state_ == ASSOCIATED_WAIT_STOP || state_ == COLLECTING);
}

bool TelemetrySenderUdpFinal::canTransmitNow() const
{
    return apAssociated_ && isConnected_ && stopCtx_.stopped && stopCtx_.atBusStop && hasValidStop();
}

void TelemetrySenderUdpFinal::evaluateTransmissionWindow()
{
    // RESTAURADO: Log de diagnóstico completo cada vez que se evalúa la ventana
    EV_INFO << "--- DIAGNÓSTICO TX: Assoc=" << (int)apAssociated_
             << " | Conn=" << (int)isConnected_
             << " | Stopped=" << (int)stopCtx_.stopped
             << " | AtStop=" << (int)stopCtx_.atBusStop
             << " | ValidStop=" << (int)hasValidStop()
             << " | StopID=" << (stopCtx_.currentStopId.empty() ? "NONE" : stopCtx_.currentStopId) << endl;

    if (!apAssociated_) {
        if (state_ == TX_ACTIVE || state_ == TX_CLOSING)
            startClosingSession("ap_disassociated");
        else
            state_ = COLLECTING;
        return;
    }

    if (!isConnected_) {
        startWaitingForStop();
        ensureConnectTimer();
        return;
    }

    if (canTransmitNow()) {
        if (state_ != TX_ACTIVE)
            startTransmissionWindow();
    }
    else {
        // RESTAURADO: Mensaje de depuración de condiciones fallidas
        if (apAssociated_ && isConnected_ && state_ != TX_CLOSING) {
            EV_INFO << "--- DEPURA TX_FAIL: Assoc=" << apAssociated_ 
                    << " Conn=" << isConnected_ 
                    << " Stopped=" << stopCtx_.stopped 
                    << " AtStop=" << stopCtx_.atBusStop 
                    << " ValidStop=" << hasValidStop() << endl;
        }
        
        if (state_ == TX_ACTIVE)
            startClosingSession("left_valid_stop");
        else
            startWaitingForStop();
    }
}

void TelemetrySenderUdpFinal::startWaitingForStop()
{
    if (!apAssociated_) {
        state_ = COLLECTING;
        cancelEvent(helloTimer_);
        return;
    }

    state_ = ASSOCIATED_WAIT_STOP;
    if (!isConnected_ && !helloTimer_->isScheduled())
        scheduleAt(simTime(), helloTimer_);
}

void TelemetrySenderUdpFinal::startTransmissionWindow()
{
    state_ = TX_ACTIVE;
    cancelEvent(helloTimer_);

    EV_INFO << "Bus " << getVehicleId() << " inicia TX UDP en stop=" << stopCtx_.currentStopId << endl;

    if (!activeBuffer_->empty())
        swapBuffersAndQueue();

    triggerBurst();
}

void TelemetrySenderUdpFinal::startClosingSession(const char* reason)
{
    if (state_ == TX_CLOSING)
        return;

    state_ = TX_CLOSING;
    cancelEvent(helloTimer_);
    cancelEvent(microDelayTimer_); // Detenemos la ráfaga si perdemos conexión

    // Vaciamos la cola para no enviar basura en el próximo AP
    pendingBatches_.clear();
    currentBurst_.clear();

    EV_INFO << "Bus " << getVehicleId() << " cerrando sesión UDP. reason=" << reason << endl;

    sendEndSession(reason);

    // LA SOLUCIÓN DEL BUG: 
    // En UDP jamás cerramos el socket (quitamos el socket.close()).
    // El puerto local debe quedar abierto para que al llegar a la siguiente RSU
    // el envío del paquete HELLO funcione. La "desconexión" es puramente lógica.
    
    isConnected_ = false;
    state_ = apAssociated_ ? ASSOCIATED_WAIT_STOP : COLLECTING;
}
void TelemetrySenderUdpFinal::onAssociationStateChanged(simsignal_t signalID)
{
    Enter_Method_Silent();

    if (signalID == associatedSignal_ || signalID == associatedOldApSignal_) {
        apAssociated_ = true;
        currentApId_ = "VANET_AP_UDP";
        EV_INFO << "--- UDP: Bus " << getVehicleId() << " ASOCIADO a WiFi." << endl;
    } else if (signalID == disassociatedSignal_) {
        apAssociated_ = false;
        currentApId_ = "Disconnected";
        EV_INFO << "--- UDP: Bus " << getVehicleId() << " DESCONECTADO de WiFi." << endl;
    }

    if (apAssociated_) {
        sessionId_++;
        helloAckReceived_ = false;
        startWaitingForStop();
        ensureConnectTimer();
    }
    else {
        if (state_ == TX_ACTIVE || socket.isOpen())
            startClosingSession("wifi_lost");
        else {
            state_ = COLLECTING;
            cancelEvent(helloTimer_);
        }
    }
}

void TelemetrySenderUdpFinal::resolveConnectAddress()
{
    connectAddress_ = L3AddressResolver().resolve(par("connectAddress"));
}

void TelemetrySenderUdpFinal::doConnect()
{
    if (!apAssociated_)
        return;

    if (connectAddress_.isUnspecified())
        resolveConnectAddress();

    // Nos aseguramos de que el socket esté registrado en el sistema del nodo
    if (localPort_ != -1 && !socket.isOpen()) {
        socket.bind(localPort_);
    }
}

void TelemetrySenderUdpFinal::ensureConnectTimer()
{
    if (!apAssociated_) return;

    // CORRECCIÓN: No debemos forzar la desconexión basados en isOpen() 
    // porque un socket UDP aparecerá cerrado hasta el primer sendTo().
    if (!isConnected_ && !connectTimer_->isScheduled())
        scheduleAt(simTime() + reconnectInterval_, connectTimer_);
}

void TelemetrySenderUdpFinal::swapBuffersAndQueue()
{
    if (activeBuffer_->empty())
        return;

    std::vector<TelemetrySampleUdpFinal>* tmp = activeBuffer_;
    activeBuffer_ = inactiveBuffer_;
    inactiveBuffer_ = tmp;

    pendingBatches_.push_back(*inactiveBuffer_);
    inactiveBuffer_->clear();
}

void TelemetrySenderUdpFinal::triggerBurst()
{
    // CORRECCIÓN: Quitamos !socket.isOpen() de la condición.
    if (!isConnected_ || state_ != TX_ACTIVE) return;

    if (microDelayTimer_->isScheduled() || burstIndex_ < currentBurst_.size()) return;

    if (pendingBatches_.empty()) return;

    currentBurst_ = pendingBatches_.front();
    pendingBatches_.pop_front();
    burstIndex_ = 0;

    if (!currentBurst_.empty()) {
        scheduleAt(simTime(), microDelayTimer_);
    } else {
        triggerBurst(); 
    }
}

void TelemetrySenderUdpFinal::sendNextBurstPacket()
{
    if (burstIndex_ >= currentBurst_.size()) {
        // La ráfaga terminó, revisamos si hay más en cola
        triggerBurst();
        return;
    }

    auto& s = currentBurst_[burstIndex_];

    std::vector<uint8_t> payload;
    writeUint8(payload, MSG_DATA_BURST); // UDP PURO (1 paquete x muestra)
    writeString(payload, getVehicleId());
    writeUint32(payload, sessionId_);
    writeString(payload, currentApId_);
    writeString(payload, stopCtx_.currentStopId);
    writeDouble(payload, simTime().dbl());
    writeUint32(payload, s.seq);
    writeDouble(payload, s.posX);
    writeDouble(payload, s.posY);
    writeDouble(payload, s.speed);
    writeDouble(payload, s.co2);
    writeDouble(payload, s.sampleTimeSec);

    std::vector<uint8_t> frame;
    writeUint32(frame, static_cast<uint32_t>(payload.size()));
    frame.insert(frame.end(), payload.begin(), payload.end());

    Packet* packet = new Packet("TelemetryUdpPacket");
    auto bytes = makeShared<BytesChunk>(frame);
    packet->insertAtBack(bytes);
    packet->addTag<CreationTimeTag>()->setCreationTime(simTime());

    if (connectAddress_.isUnspecified()) resolveConnectAddress();
    socket.sendTo(packet, connectAddress_, connectPort_);

    burstIndex_++;

    // Intervalo fijo de 1ms entre paquetes
    scheduleAt(simTime() + 0.001, microDelayTimer_);
}

void TelemetrySenderUdpFinal::sendHello(bool readyToTransmit)
{
    // CORRECCIÓN CLAVE: Quitamos la línea `if (!socket.isOpen()) return;`
    // Al llamar a sendTo() abajo, INET abrirá el socket y le dará un puerto válido.

    std::vector<uint8_t> payload;
    writeUint8(payload, MSG_HELLO);
    writeString(payload, getVehicleId());
    writeUint32(payload, sessionId_);
    writeString(payload, currentApId_);
    writeString(payload, stopCtx_.currentStopId);
    writeString(payload, stopCtx_.currentLaneId);
    writeUint8(payload, readyToTransmit ? 1 : 0);

    std::vector<uint8_t> frame;
    writeUint32(frame, static_cast<uint32_t>(payload.size()));
    frame.insert(frame.end(), payload.begin(), payload.end());

    Packet* packet = new Packet("HelloUdp");
    auto bytes = makeShared<BytesChunk>(frame);
    packet->insertAtBack(bytes);
    packet->addTag<CreationTimeTag>()->setCreationTime(simTime());

    if (connectAddress_.isUnspecified()) resolveConnectAddress();
    socket.sendTo(packet, connectAddress_, connectPort_);
}
void TelemetrySenderUdpFinal::sendEndSession(const char* reason)
{
    // CORRECCIÓN: Quitamos la línea `if (!socket.isOpen()) return;`

    std::vector<uint8_t> payload;
    writeUint8(payload, MSG_END_SESSION);
    writeString(payload, getVehicleId());
    writeUint32(payload, sessionId_);
    writeString(payload, currentApId_);
    writeString(payload, stopCtx_.currentStopId);
    writeString(payload, reason ? reason : "unknown");

    std::vector<uint8_t> frame;
    writeUint32(frame, static_cast<uint32_t>(payload.size()));
    frame.insert(frame.end(), payload.begin(), payload.end());

    Packet* packet = new Packet("EndSessionUdp");
    auto bytes = makeShared<BytesChunk>(frame);
    packet->insertAtBack(bytes);
    packet->addTag<CreationTimeTag>()->setCreationTime(simTime());

    if (connectAddress_.isUnspecified()) resolveConnectAddress();
    socket.sendTo(packet, connectAddress_, connectPort_);
}

void TelemetrySenderUdpFinal::processServerControlMessage(const std::vector<uint8_t>& payload)
{
    if (payload.empty()) return;

    uint8_t msgType = payload[0];
    if (msgType == MSG_HELLO_ACK) {
        helloAckReceived_ = true;
        isConnected_ = true;
        EV_INFO << "UDP: Recibido HELLO_ACK, conexión lógica establecida." << endl;
        cancelEvent(helloTimer_);
        if (canTransmitNow()) {
            startTransmissionWindow();
        }
    }
}

// UDP Callbacks
void TelemetrySenderUdpFinal::socketDataArrived(UdpSocket *s, Packet *msg)
{
    if (msg->getDataLength() < B(4)) {
        delete msg;
        return;
    }

    auto header = msg->peekAtFront<BytesChunk>(B(4));
    const auto& h = header->getBytes();
    uint32_t payloadLen = (static_cast<uint32_t>(h[0]) << 24) |
                          (static_cast<uint32_t>(h[1]) << 16) |
                          (static_cast<uint32_t>(h[2]) << 8) |
                          static_cast<uint32_t>(h[3]);

    if (msg->getDataLength() < B(4 + payloadLen)) {
        delete msg;
        return;
    }

    msg->popAtFront<BytesChunk>(B(4));
    auto payloadChunk = msg->popAtFront<BytesChunk>(B(payloadLen));
    processServerControlMessage(payloadChunk->getBytes());
    delete msg;
}

void TelemetrySenderUdpFinal::socketErrorArrived(UdpSocket *s, Indication *indication)
{
    delete indication;
}

void TelemetrySenderUdpFinal::socketClosed(UdpSocket *s)
{
    isConnected_ = false;
    state_ = apAssociated_ ? ASSOCIATED_WAIT_STOP : COLLECTING;
    if (apAssociated_) ensureConnectTimer();
}

std::string TelemetrySenderUdpFinal::getVehicleId() const
{
    if (veinsMobility_) return veinsMobility_->getExternalId();
    return getContainingNode(this)->getName();
}

void TelemetrySenderUdpFinal::parseRouteStopsParameter()
{
    routeStops_.clear();
    std::string raw = par("routeStops").stdstringValue();
    for (const auto& token : split(raw, ',')) {
        std::string t = trim(token);
        if (!t.empty()) routeStops_.push_back(t);
    }
}

void TelemetrySenderUdpFinal::parseValidStopsParameter()
{
    validStops_.clear();
    std::string raw = par("validStops").stdstringValue();
    for (const auto& stop : split(raw, ',')) {
        std::string s = trim(stop);
        if (!s.empty()) validStops_.insert(s);
    }
}

std::vector<std::string> TelemetrySenderUdpFinal::split(const std::string& text, char delim)
{
    std::vector<std::string> out;
    std::stringstream ss(text);
    std::string item;
    while (std::getline(ss, item, delim)) out.push_back(item);
    return out;
}

std::string TelemetrySenderUdpFinal::trim(const std::string& s)
{
    size_t begin = 0;
    while (begin < s.size() && std::isspace(static_cast<unsigned char>(s[begin]))) ++begin;
    size_t end = s.size();
    while (end > begin && std::isspace(static_cast<unsigned char>(s[end - 1]))) --end;
    return s.substr(begin, end - begin);
}

void TelemetrySenderUdpFinal::receiveSignal(cComponent* source, simsignal_t signalID, bool b, cObject* details) {
    if (signalID == associatedSignal_ || signalID == associatedOldApSignal_ || signalID == disassociatedSignal_) onAssociationStateChanged(signalID);
}

void TelemetrySenderUdpFinal::receiveSignal(cComponent* source, simsignal_t signalID, long l, cObject* details) {
    if (signalID == associatedSignal_ || signalID == associatedOldApSignal_ || signalID == disassociatedSignal_) onAssociationStateChanged(signalID);
}

void TelemetrySenderUdpFinal::receiveSignal(cComponent* source, simsignal_t signalID, unsigned long l, cObject* details) {
    if (signalID == associatedSignal_ || signalID == associatedOldApSignal_ || signalID == disassociatedSignal_) onAssociationStateChanged(signalID);
}

void TelemetrySenderUdpFinal::receiveSignal(cComponent* source, simsignal_t signalID, double d, cObject* details) {
    if (signalID == associatedSignal_ || signalID == associatedOldApSignal_ || signalID == disassociatedSignal_) onAssociationStateChanged(signalID);
}

void TelemetrySenderUdpFinal::receiveSignal(cComponent* source, simsignal_t signalID, const SimTime& t, cObject* details) {
    if (signalID == associatedSignal_ || signalID == associatedOldApSignal_ || signalID == disassociatedSignal_) onAssociationStateChanged(signalID);
}

void TelemetrySenderUdpFinal::receiveSignal(cComponent* source, simsignal_t signalID, const char* s, cObject* details) {
    if (signalID == associatedSignal_ || signalID == associatedOldApSignal_ || signalID == disassociatedSignal_) onAssociationStateChanged(signalID);
}

void TelemetrySenderUdpFinal::receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj, cObject* details) {
    if (signalID == associatedSignal_ || signalID == associatedOldApSignal_ || signalID == disassociatedSignal_) onAssociationStateChanged(signalID);
}

void TelemetrySenderUdpFinal::writeUint8(std::vector<uint8_t>& buf, uint8_t v) { buf.push_back(v); }
void TelemetrySenderUdpFinal::writeUint16(std::vector<uint8_t>& buf, uint16_t v) {
    buf.push_back((v >> 8) & 0xFF); buf.push_back(v & 0xFF);
}
void TelemetrySenderUdpFinal::writeUint32(std::vector<uint8_t>& buf, uint32_t v) {
    buf.push_back((v >> 24) & 0xFF); buf.push_back((v >> 16) & 0xFF);
    buf.push_back((v >> 8) & 0xFF); buf.push_back(v & 0xFF);
}
void TelemetrySenderUdpFinal::writeDouble(std::vector<uint8_t>& buf, double v) {
    uint64_t raw = 0; std::memcpy(&raw, &v, sizeof(double));
    for (int i = 7; i >= 0; --i) buf.push_back((raw >> (i * 8)) & 0xFF);
}
void TelemetrySenderUdpFinal::writeString(std::vector<uint8_t>& buf, const std::string& s) {
    writeUint16(buf, static_cast<uint16_t>(s.size()));
    buf.insert(buf.end(), s.begin(), s.end());
}
uint8_t TelemetrySenderUdpFinal::readUint8(const std::vector<uint8_t>& buf, size_t& offset) { return buf[offset++]; }
uint16_t TelemetrySenderUdpFinal::readUint16(const std::vector<uint8_t>& buf, size_t& offset) {
    uint16_t v = (static_cast<uint16_t>(buf[offset]) << 8) | static_cast<uint16_t>(buf[offset + 1]); offset += 2; return v;
}
uint32_t TelemetrySenderUdpFinal::readUint32(const std::vector<uint8_t>& buf, size_t& offset) {
    uint32_t v = (static_cast<uint32_t>(buf[offset]) << 24) | (static_cast<uint32_t>(buf[offset + 1]) << 16) |
                 (static_cast<uint32_t>(buf[offset + 2]) << 8) | static_cast<uint32_t>(buf[offset + 3]);
    offset += 4; return v;
}
double TelemetrySenderUdpFinal::readDouble(const std::vector<uint8_t>& buf, size_t& offset) {
    uint64_t raw = 0; for (int i = 0; i < 8; ++i) raw = (raw << 8) | static_cast<uint64_t>(buf[offset++]);
    double out; std::memcpy(&out, &raw, sizeof(double)); return out;
}
std::string TelemetrySenderUdpFinal::readString(const std::vector<uint8_t>& buf, size_t& offset) {
    uint16_t len = readUint16(buf, offset);
    std::string s(buf.begin() + offset, buf.begin() + offset + len); offset += len; return s;
}

} // namespace simu5g
