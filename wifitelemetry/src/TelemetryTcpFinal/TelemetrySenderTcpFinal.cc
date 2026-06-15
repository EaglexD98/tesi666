//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

#include "TelemetrySenderTcpFinal.h"

#include <algorithm>
#include <cctype>
#include <cstring>
#include <sstream>
#include <inet/common/packet/Packet.h>
#include "inet/linklayer/ieee80211/mgmt/Ieee80211AgentSta.h"
#include "inet/linklayer/ieee80211/mib/Ieee80211Mib.h"
#include "inet/linklayer/ieee80211/mac/Ieee80211Mac.h"
#include <inet/common/packet/chunk/BytesChunk.h>
#include <inet/common/TimeTag_m.h>
#include <inet/linklayer/ieee80211/mgmt/Ieee80211MgmtSta.h>
#include <inet/networklayer/common/InterfaceTable.h>
#include <inet/networklayer/common/NetworkInterface.h>
#include <inet/common/ModuleAccess.h>
#include <inet/linklayer/ieee80211/mac/Ieee80211Mac.h>
#include "inet/physicallayer/wireless/common/energyconsumer/StateBasedCcEnergyConsumer.h"

namespace simu5g {

Define_Module(TelemetrySenderTcpFinal);

using namespace omnetpp;
using namespace inet;

TelemetrySenderTcpFinal::~TelemetrySenderTcpFinal()
{
    cancelAndDelete(connectTimer_);
    cancelAndDelete(sampleTimer_);
    cancelAndDelete(batchTimer_);
    cancelAndDelete(helloTimer_);
    cancelAndDelete(conditionTimer_);
}

void TelemetrySenderTcpFinal::initialize(int stage)
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
    batchInterval_ = par("batchInterval");
    helloInterval_ = par("helloInterval");
    conditionCheckInterval_ = par("conditionCheckInterval");
    reconnectInterval_ = par("reconnectInterval");
    startTime_ = par("startTime");

    activeBuffer_ = &bufferA_;
    inactiveBuffer_ = &bufferB_;

    socket.setOutputGate(gate("socketOut"));
    socket.setCallback(this);
    if (localPort_ != -1)
        socket.bind(localPort_);

    connectTimer_ = new cMessage("connectTimer");
    sampleTimer_ = new cMessage("sampleTimer");
    batchTimer_ = new cMessage("batchTimer");
    helloTimer_ = new cMessage("helloTimer");
    conditionTimer_ = new cMessage("conditionTimer");

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
                EV_INFO << "Aplicación suscrita directamente a las señales de wlan[0].mgmt en el bus " << getVehicleId() << endl;
            }

            if (cModule* agent = wlan->getSubmodule("agent")) {
                agent->subscribe(associatedSignal_, this);
                agent->subscribe(associatedOldApSignal_, this);
                agent->subscribe(disassociatedSignal_, this);
                EV_INFO << "Aplicación suscrita directamente al agente WiFi en el bus " << getVehicleId() << endl;
            }
        }
    }

    scheduleAt(simTime() + startTime_, sampleTimer_);
    scheduleAt(simTime() + startTime_ + conditionCheckInterval_, conditionTimer_);
    scheduleAt(simTime() + startTime_ + batchInterval_, batchTimer_);
}

void TelemetrySenderTcpFinal::handleMessage(cMessage* msg)
{
    if (msg->isSelfMessage()) {
        if (msg == connectTimer_) {
            if (apAssociated_ && !isConnected_) {
                if (!socket.isOpen() || socket.getState() == inet::TcpSocket::LOCALLY_CLOSED || socket.getState() == inet::TcpSocket::CLOSED) {
                    doConnect();
                }
            }
        }
        else if (msg == sampleTimer_) {
            takeSample();
            scheduleAt(simTime() + sampleInterval_, sampleTimer_);
        }
        else if (msg == batchTimer_) {
            swapBuffersAndQueue();
            scheduleAt(simTime() + batchInterval_, batchTimer_);
        }
        else if (msg == helloTimer_) {
            if (stateAllowsHello() && isConnected_) {
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

void TelemetrySenderTcpFinal::finish()
{
    if (state_ == TX_ACTIVE || state_ == TX_CLOSING)
        sendEndSession("finish");

    if (!activeBuffer_->empty())
        swapBuffersAndQueue();

    if (isConnected_)
        flushPendingBatches();

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


void TelemetrySenderTcpFinal::updateMobilityHandles()
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

void TelemetrySenderTcpFinal::takeSample()
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

    TelemetrySampleTcpFinal s;
    s.seq = sequenceNumber_++;
    s.posX = pos.x;
    s.posY = pos.y;
    s.speed = speed;
    s.co2 = co2;
    s.sampleTimeSec = simTime().dbl();

    activeBuffer_->push_back(s);
}

void TelemetrySenderTcpFinal::updateStopContext()
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


bool TelemetrySenderTcpFinal::hasValidStop() const
{
    return validStops_.count(stopCtx_.currentStopId) > 0;
}

bool TelemetrySenderTcpFinal::stateAllowsHello() const
{
    return apAssociated_ && (state_ == ASSOCIATED_WAIT_STOP || state_ == COLLECTING);
}

bool TelemetrySenderTcpFinal::canTransmitNow() const
{
    return apAssociated_ && isConnected_ && stopCtx_.stopped && stopCtx_.atBusStop && hasValidStop();
}

void TelemetrySenderTcpFinal::evaluateTransmissionWindow()
{

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

void TelemetrySenderTcpFinal::startWaitingForStop()
{
    if (!apAssociated_) {
        state_ = COLLECTING;
        cancelEvent(helloTimer_);
        return;
    }

    if (state_ != ASSOCIATED_WAIT_STOP)
        EV_INFO << "Bus " << getVehicleId() << " asociado a " << currentApId_
                << " esperando stop válido. stop=" << stopCtx_.currentStopId
                << " stopped=" << stopCtx_.stopped << " atBusStop=" << stopCtx_.atBusStop << endl;

    state_ = ASSOCIATED_WAIT_STOP;
    if (isConnected_ && !helloTimer_->isScheduled())
        scheduleAt(simTime(), helloTimer_);
}

void TelemetrySenderTcpFinal::startTransmissionWindow()
{
    state_ = TX_ACTIVE;
    cancelEvent(helloTimer_);

    EV_INFO << "Bus " << getVehicleId() << " inicia TX en stop=" << stopCtx_.currentStopId
            << " AP=" << currentApId_ << " sessionId=" << sessionId_ << endl;

    if (!activeBuffer_->empty())
        swapBuffersAndQueue();

    flushPendingBatches();
}

void TelemetrySenderTcpFinal::startClosingSession(const char* reason)
{
    if (state_ == TX_CLOSING)
        return;

    state_ = TX_CLOSING;
    cancelEvent(helloTimer_);

    EV_INFO << "Bus " << getVehicleId() << " cerrando sesión TCP. reason=" << reason
            << " stop=" << stopCtx_.currentStopId << " AP=" << currentApId_ << endl;

    sendEndSession(reason);

    if (socket.isOpen()) {
        if (strcmp(reason, "wifi_lost") == 0) {
            socket.abort();
        } else {
            socket.close();
        }
    }

    rescueUnackedBatches();
    isConnected_ = false;
    state_ = apAssociated_ ? ASSOCIATED_WAIT_STOP : COLLECTING;
}

void TelemetrySenderTcpFinal::onAssociationStateChanged(simsignal_t signalID)
{
    Enter_Method_Silent();

    if (signalID == associatedSignal_ || signalID == associatedOldApSignal_) {
        apAssociated_ = true;
        currentApId_ = "VANET_AP";
        EV_INFO << "--- SEÑAL RECIBIDA: Bus " << getVehicleId() << " ASOCIADO a WiFi." << endl;
    } else if (signalID == disassociatedSignal_) {
        apAssociated_ = false;
        currentApId_ = "Disconnected";
        EV_INFO << "--- SEÑAL RECIBIDA: Bus " << getVehicleId() << " DESCONECTADO de WiFi." << endl;
    }

    // --- TRUCO DE ENERGÍA POR SOFTWARE ---
    cModule* host = getContainingNode(this);
    if (host) {
        cModule* wlan = host->getSubmodule("wlan", 0);
        if (wlan) {
            cModule* radioMod = wlan->getSubmodule("radio");
            if (radioMod) {
                auto consumer = dynamic_cast<inet::physicallayer::StateBasedCcEnergyConsumer*>(radioMod->getSubmodule("energyConsumer"));
                if (consumer) {
                    // Si se asocia, quitamos el sleep (false). Si se desconecta, activamos el sleep (true).
                  //  consumer->setSoftwareSleep(!apAssociated_);
                    EV_INFO << "--- ENERGÍA SOFTWARE: " << (apAssociated_ ? "MODO ACTIVO (Asociado)" : "MODO SLEEP (Desconectado)") << endl;
                }
            }
        }
    }
    // -------------------------------------

    if (apAssociated_) {
        sessionId_++;
        helloAckReceived_ = false;
        serverHighestAckedSeq_ = lastAckedSeqSeen_;
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




void TelemetrySenderTcpFinal::resolveConnectAddress()
{
    connectAddress_ = L3AddressResolver().resolve(par("connectAddress"));
}

void TelemetrySenderTcpFinal::doConnect()
{
    if (!apAssociated_)
        return;

    if (connectAddress_.isUnspecified())
        resolveConnectAddress();

    socket.renewSocket();
    socket.setCallback(this);
    socket.setOutputGate(gate("socketOut"));
    if (localPort_ != -1)
        socket.bind(localPort_);
    socket.connect(connectAddress_, connectPort_);
}

void TelemetrySenderTcpFinal::ensureConnectTimer()
{
    if (!apAssociated_)
        return;

    if (socket.getState() == inet::TcpSocket::LOCALLY_CLOSED || socket.getState() == inet::TcpSocket::CLOSED) {
        isConnected_ = false;
    }

    if (!isConnected_ && !connectTimer_->isScheduled())
        scheduleAt(simTime() + reconnectInterval_, connectTimer_);
}

void TelemetrySenderTcpFinal::swapBuffersAndQueue()
{
    if (activeBuffer_->empty())
        return;

    std::vector<TelemetrySampleTcpFinal>* tmp = activeBuffer_;
    activeBuffer_ = inactiveBuffer_;
    inactiveBuffer_ = tmp;

    pendingBatches_.push_back(*inactiveBuffer_);
    inactiveBuffer_->clear();
}


void TelemetrySenderTcpFinal::rescueUnackedBatches()
{
    if (unackedBatches_.empty())
        return;

    EV_WARN << "Rescatando " << unackedBatches_.size() << " lotes no confirmados en bus " << getVehicleId() << endl;
    pendingBatches_.insert(pendingBatches_.begin(), unackedBatches_.begin(), unackedBatches_.end());
    unackedBatches_.clear();
}

void TelemetrySenderTcpFinal::pruneAckedData(uint32_t ackSeq)
{
    serverHighestAckedSeq_ = std::max(serverHighestAckedSeq_, ackSeq);
    lastAckedSeqSeen_ = std::max(lastAckedSeqSeen_, ackSeq);

    auto eraseAckedBatches = [ackSeq](std::deque<std::vector<TelemetrySampleTcpFinal>>& dq) {
        auto it = dq.begin();
        while (it != dq.end()) {
            if (!it->empty() && it->back().seq <= ackSeq)
                it = dq.erase(it);
            else
                ++it;
        }
    };

    eraseAckedBatches(pendingBatches_);
    eraseAckedBatches(unackedBatches_);
}

void TelemetrySenderTcpFinal::sendHello(bool readyToTransmit)
{
    if (!isConnected_ || !socket.isOpen() || socket.getState() == inet::TcpSocket::LOCALLY_CLOSED) {
        EV_WARN << "Intento de enviar HELLO cancelado: socket TCP no está listo. Bus " << getVehicleId() << endl;
        return;
    }

    std::vector<uint8_t> payload;
    writeUint8(payload, MSG_HELLO);
    writeString(payload, getVehicleId());
    writeUint32(payload, sessionId_);
    writeString(payload, currentApId_);
    writeString(payload, stopCtx_.currentStopId);
    writeString(payload, stopCtx_.currentLaneId);
    writeUint8(payload, readyToTransmit ? 1 : 0);
    writeUint32(payload, serverHighestAckedSeq_ + 1);
    writeUint32(payload, lastAckedSeqSeen_);

    std::vector<uint8_t> frame;
    writeUint32(frame, static_cast<uint32_t>(payload.size()));
    frame.insert(frame.end(), payload.begin(), payload.end());

    Packet* packet = new Packet("HelloTcp");
    auto bytes = makeShared<BytesChunk>(frame);
    packet->insertAtBack(bytes);
    packet->addTag<CreationTimeTag>()->setCreationTime(simTime());
    socket.send(packet);
}

void TelemetrySenderTcpFinal::sendEndSession(const char* reason)
{
    if (!isConnected_ || !socket.isOpen() || socket.getState() == inet::TcpSocket::LOCALLY_CLOSED)
        return;

    std::vector<uint8_t> payload;
    writeUint8(payload, MSG_END_SESSION);
    writeString(payload, getVehicleId());
    writeUint32(payload, sessionId_);
    writeString(payload, currentApId_);
    writeString(payload, stopCtx_.currentStopId);
    writeString(payload, reason ? reason : "unknown");
    writeUint32(payload, lastAckedSeqSeen_);

    std::vector<uint8_t> frame;
    writeUint32(frame, static_cast<uint32_t>(payload.size()));
    frame.insert(frame.end(), payload.begin(), payload.end());

    Packet* packet = new Packet("EndSessionTcp");
    auto bytes = makeShared<BytesChunk>(frame);
    packet->insertAtBack(bytes);
    packet->addTag<CreationTimeTag>()->setCreationTime(simTime());
    socket.send(packet);
}

void TelemetrySenderTcpFinal::flushPendingBatches()
{
    if (!isConnected_ || state_ != TX_ACTIVE || pendingBatches_.empty() || !socket.isOpen() || socket.getState() == inet::TcpSocket::LOCALLY_CLOSED)
        return;

    const std::string vehId = getVehicleId();

    while (!pendingBatches_.empty()) {
        const auto& batch = pendingBatches_.front();
        if (batch.empty()) {
            pendingBatches_.pop_front();
            continue;
        }

        std::vector<uint8_t> payload;
        writeUint8(payload, MSG_DATA_BATCH);
        writeString(payload, vehId);
        writeUint32(payload, sessionId_);
        writeString(payload, currentApId_);
        writeString(payload, stopCtx_.currentStopId);
        writeUint32(payload, static_cast<uint32_t>(batch.size()));
        writeDouble(payload, simTime().dbl());

        for (const auto& s : batch) {
            writeUint32(payload, s.seq);
            writeDouble(payload, s.posX);
            writeDouble(payload, s.posY);
            writeDouble(payload, s.speed);
            writeDouble(payload, s.co2);
            writeDouble(payload, s.sampleTimeSec);
        }

        std::vector<uint8_t> frame;
        writeUint32(frame, static_cast<uint32_t>(payload.size()));
        frame.insert(frame.end(), payload.begin(), payload.end());

        Packet* packet = new Packet("TelemetryBatchTcp");
        auto bytes = makeShared<BytesChunk>(frame);
        packet->insertAtBack(bytes);
        packet->addTag<CreationTimeTag>()->setCreationTime(simTime());
        socket.send(packet);

        unackedBatches_.push_back(batch);
        pendingBatches_.pop_front();
    }
}


void TelemetrySenderTcpFinal::processServerControlMessage(const std::vector<uint8_t>& payload)
{
    if (payload.empty())
        return;

    uint8_t msgType = payload[0];
    if (msgType == MSG_APP_ACK || msgType == MSG_HELLO_ACK) {
        size_t offset = 1;
        uint32_t ackSeq = readUint32(payload, offset);
        pruneAckedData(ackSeq);

        if (msgType == MSG_HELLO_ACK) {
            helloAckReceived_ = true;
            EV_INFO << "Recibido HELLO_ACK. ackSeq=" << ackSeq << endl;
        }
        else {
            EV_INFO << "Recibido APP_ACK. ackSeq=" << ackSeq << endl;
        }
    }
}

std::string TelemetrySenderTcpFinal::getVehicleId() const
{
    if (veinsMobility_)
        return veinsMobility_->getExternalId();
    return getContainingNode(this)->getName();
}

void TelemetrySenderTcpFinal::parseRouteStopsParameter()
{
    routeStops_.clear();
    std::string raw = par("routeStops").stdstringValue();
    for (const auto& token : split(raw, ',')) {
        std::string t = trim(token);
        if (!t.empty())
            routeStops_.push_back(t);
    }
}

void TelemetrySenderTcpFinal::parseValidStopsParameter()
{
    validStops_.clear();
    std::string raw = par("validStops").stdstringValue();

    for (const auto& stop : split(raw, ',')) {
        std::string s = trim(stop);
        if (!s.empty())
            validStops_.insert(s);
    }
}

std::vector<std::string> TelemetrySenderTcpFinal::split(const std::string& text, char delim)
{
    std::vector<std::string> out;
    std::stringstream ss(text);
    std::string item;
    while (std::getline(ss, item, delim))
        out.push_back(item);
    return out;
}

std::string TelemetrySenderTcpFinal::trim(const std::string& s)
{
    size_t begin = 0;
    while (begin < s.size() && std::isspace(static_cast<unsigned char>(s[begin])))
        ++begin;

    size_t end = s.size();
    while (end > begin && std::isspace(static_cast<unsigned char>(s[end - 1])))
        --end;

    return s.substr(begin, end - begin);
}

void TelemetrySenderTcpFinal::socketAvailable(TcpSocket* socket, TcpAvailableInfo* availableInfo)
{
    delete availableInfo;
}

void TelemetrySenderTcpFinal::socketEstablished(TcpSocket* s)
{
    isConnected_ = true;
    helloAckReceived_ = false;
    EV_INFO << "TCP conectado para bus " << getVehicleId() << " AP=" << currentApId_ << endl;
    startWaitingForStop();
    if (!helloTimer_->isScheduled())
        scheduleAt(simTime(), helloTimer_);
}

void TelemetrySenderTcpFinal::socketPeerClosed(TcpSocket* s)
{
    if (s->getState() == TcpSocket::PEER_CLOSED)
        s->close();
}

void TelemetrySenderTcpFinal::socketClosed(TcpSocket* s)
{
    isConnected_ = false;
    rescueUnackedBatches();
    state_ = apAssociated_ ? ASSOCIATED_WAIT_STOP : COLLECTING;
    if (apAssociated_)
        ensureConnectTimer();
}

void TelemetrySenderTcpFinal::socketFailure(TcpSocket* s, int code)
{
    EV_WARN << "Fallo TCP en bus " << getVehicleId() << " code=" << code << endl;
    isConnected_ = false;
    rescueUnackedBatches();
    state_ = apAssociated_ ? ASSOCIATED_WAIT_STOP : COLLECTING;
    if (apAssociated_)
        ensureConnectTimer();
}

void TelemetrySenderTcpFinal::socketDataArrived(TcpSocket* s, Packet* msg, bool urgent)
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

void TelemetrySenderTcpFinal::socketStatusArrived(TcpSocket* s, TcpStatusInfo* status)
{
    delete status;
}

void TelemetrySenderTcpFinal::socketDeleted(TcpSocket* s)
{
}

void TelemetrySenderTcpFinal::receiveSignal(cComponent* source, simsignal_t signalID, bool b, cObject* details)
{
    if (signalID == associatedSignal_ || signalID == associatedOldApSignal_ || signalID == disassociatedSignal_) onAssociationStateChanged(signalID);
}

void TelemetrySenderTcpFinal::receiveSignal(cComponent* source, simsignal_t signalID, long l, cObject* details)
{
    if (signalID == associatedSignal_ || signalID == associatedOldApSignal_ || signalID == disassociatedSignal_) onAssociationStateChanged(signalID);
}

void TelemetrySenderTcpFinal::receiveSignal(cComponent* source, simsignal_t signalID, unsigned long l, cObject* details)
{
    if (signalID == associatedSignal_ || signalID == associatedOldApSignal_ || signalID == disassociatedSignal_) onAssociationStateChanged(signalID);
}

void TelemetrySenderTcpFinal::receiveSignal(cComponent* source, simsignal_t signalID, double d, cObject* details)
{
    if (signalID == associatedSignal_ || signalID == associatedOldApSignal_ || signalID == disassociatedSignal_) onAssociationStateChanged(signalID);
}

void TelemetrySenderTcpFinal::receiveSignal(cComponent* source, simsignal_t signalID, const SimTime& t, cObject* details)
{
    if (signalID == associatedSignal_ || signalID == associatedOldApSignal_ || signalID == disassociatedSignal_) onAssociationStateChanged(signalID);
}

void TelemetrySenderTcpFinal::receiveSignal(cComponent* source, simsignal_t signalID, const char* s, cObject* details)
{
    if (signalID == associatedSignal_ || signalID == associatedOldApSignal_ || signalID == disassociatedSignal_) onAssociationStateChanged(signalID);
}

void TelemetrySenderTcpFinal::receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj, cObject* details)
{
    if (signalID == associatedSignal_ || signalID == associatedOldApSignal_ || signalID == disassociatedSignal_) onAssociationStateChanged(signalID);
}
void TelemetrySenderTcpFinal::writeUint8(std::vector<uint8_t>& buf, uint8_t v)
{
    buf.push_back(v);
}

void TelemetrySenderTcpFinal::writeUint16(std::vector<uint8_t>& buf, uint16_t v)
{
    buf.push_back((v >> 8) & 0xFF);
    buf.push_back(v & 0xFF);
}

void TelemetrySenderTcpFinal::writeUint32(std::vector<uint8_t>& buf, uint32_t v)
{
    buf.push_back((v >> 24) & 0xFF);
    buf.push_back((v >> 16) & 0xFF);
    buf.push_back((v >> 8) & 0xFF);
    buf.push_back(v & 0xFF);
}

void TelemetrySenderTcpFinal::writeDouble(std::vector<uint8_t>& buf, double v)
{
    uint64_t raw = 0;
    std::memcpy(&raw, &v, sizeof(double));
    for (int i = 7; i >= 0; --i)
        buf.push_back((raw >> (i * 8)) & 0xFF);
}

void TelemetrySenderTcpFinal::writeString(std::vector<uint8_t>& buf, const std::string& s)
{
    writeUint16(buf, static_cast<uint16_t>(s.size()));
    buf.insert(buf.end(), s.begin(), s.end());
}

uint8_t TelemetrySenderTcpFinal::readUint8(const std::vector<uint8_t>& buf, size_t& offset)
{
    return buf[offset++];
}

uint16_t TelemetrySenderTcpFinal::readUint16(const std::vector<uint8_t>& buf, size_t& offset)
{
    uint16_t v = (static_cast<uint16_t>(buf[offset]) << 8) | static_cast<uint16_t>(buf[offset + 1]);
    offset += 2;
    return v;
}

uint32_t TelemetrySenderTcpFinal::readUint32(const std::vector<uint8_t>& buf, size_t& offset)
{
    uint32_t v = (static_cast<uint32_t>(buf[offset]) << 24) |
                 (static_cast<uint32_t>(buf[offset + 1]) << 16) |
                 (static_cast<uint32_t>(buf[offset + 2]) << 8) |
                 static_cast<uint32_t>(buf[offset + 3]);
    offset += 4;
    return v;
}

double TelemetrySenderTcpFinal::readDouble(const std::vector<uint8_t>& buf, size_t& offset)
{
    uint64_t raw = 0;
    for (int i = 0; i < 8; ++i)
        raw = (raw << 8) | static_cast<uint64_t>(buf[offset++]);
    double out;
    std::memcpy(&out, &raw, sizeof(double));
    return out;
}

std::string TelemetrySenderTcpFinal::readString(const std::vector<uint8_t>& buf, size_t& offset)
{
    uint16_t len = readUint16(buf, offset);
    std::string s(buf.begin() + offset, buf.begin() + offset + len);
    offset += len;
    return s;
}

} // namespace simu5g
