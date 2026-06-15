//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 

#include "TelemetryReceiverUdpFinal.h"

#include <cstring>
#include <iomanip>
#include <sstream>

#include <inet/common/packet/Packet.h>
#include <inet/common/packet/chunk/BytesChunk.h>
#include <inet/common/TimeTag_m.h>
#include <inet/networklayer/common/L3AddressTag_m.h>
#include <inet/transportlayer/common/L4PortTag_m.h>

namespace simu5g {

Define_Module(TelemetryReceiverUdpFinal);

using namespace omnetpp;
using namespace inet;

simsignal_t TelemetryReceiverUdpFinal::telemetryLatencySignal_ = registerSignal("telemetryLatency");
simsignal_t TelemetryReceiverUdpFinal::telemetryCo2Signal_ = registerSignal("telemetryCo2");

TelemetryReceiverUdpFinal::~TelemetryReceiverUdpFinal()
{
    for (auto& kv : carVectorsMap_) {
        delete kv.second->networkDelayVec;
        delete kv.second->appDelayVec;
        delete kv.second->jitterVec;
        delete kv.second->receivedBatchesVec;
        delete kv.second;
        delete kv.second->lossRateVec;
    }
}

void TelemetryReceiverUdpFinal::initialize(int stage)
{
    cSimpleModule::initialize(stage);
    if (stage == INITSTAGE_APPLICATION_LAYER) {
        socket.setOutputGate(gate("socketOut"));
        int localPort = par("localPort");
        socket.bind(localPort);
        socket.setCallback(this);
        EV_INFO << "Servidor UDP escuchando en el puerto " << localPort << endl;
    }
}

void TelemetryReceiverUdpFinal::handleMessage(cMessage* msg)
{
    if (msg->isSelfMessage()) {
        delete msg;
        return;
    }
    socket.processMessage(msg);
}

void TelemetryReceiverUdpFinal::socketDataArrived(UdpSocket *s, Packet *packet)
{
    if (packet->getDataLength() < B(4)) {
        delete packet;
        return;
    }

    auto headerChunk = packet->peekAtFront<BytesChunk>(B(4));
    const auto& bytes = headerChunk->getBytes();

    uint32_t msgSize = (static_cast<uint32_t>(bytes[0]) << 24) |
                       (static_cast<uint32_t>(bytes[1]) << 16) |
                       (static_cast<uint32_t>(bytes[2]) << 8) |
                       static_cast<uint32_t>(bytes[3]);

    if (packet->getDataLength() < B(4) + B(msgSize)) {
        delete packet;
        return;
    }

    packet->popAtFront<BytesChunk>(B(4));
    auto payloadChunk = packet->popAtFront<BytesChunk>(B(msgSize));

    processCompleteMessage(packet, payloadChunk->getBytes());
    delete packet;
}

void TelemetryReceiverUdpFinal::processCompleteMessage(Packet* packet, const std::vector<uint8_t>& payload)
{
    if (payload.empty()) return;

    size_t offset = 0;
    uint8_t msgType = readUint8(payload, offset);

    switch (msgType) {
        case MSG_HELLO:
            processHello(packet, payload, offset);
            break;
        case MSG_DATA_BURST:
            processDataBurst(packet, payload, offset);
            break;
        case MSG_END_SESSION:
            processEndSession(packet, payload, offset);
            break;
        default:
            EV_WARN << "Tipo de mensaje UDP desconocido: " << static_cast<int>(msgType) << endl;
            break;
    }
}

void TelemetryReceiverUdpFinal::processHello(Packet* packet, const std::vector<uint8_t>& payload, size_t& offset)
{
    std::string nodeId = readString(payload, offset);
    uint32_t sessionId = readUint32(payload, offset);
    std::string apId = readString(payload, offset);
    std::string stopId = readString(payload, offset);
    std::string laneId = readString(payload, offset);
    bool readyToTransmit = readUint8(payload, offset) != 0;

    EV_DEBUG << "UDP HELLO bus=" << nodeId << " session=" << sessionId << " ap=" << apId << " stop=" << stopId << endl;

    // Extraer origen para poder responder
    auto l3Tag = packet->getTag<L3AddressInd>();
    auto l4Tag = packet->getTag<L4PortInd>();

    sendHelloAck(l3Tag->getSrcAddress(), l4Tag->getSrcPort(), 0);
}

void TelemetryReceiverUdpFinal::processDataBurst(Packet* packet, const std::vector<uint8_t>& payload, size_t& offset)
{
    std::string nodeIdStr = readString(payload, offset);
    uint32_t sessionId = readUint32(payload, offset);
    std::string apId = readString(payload, offset);
    std::string stopId = readString(payload, offset);
    
    double txTimeDbl = readDouble(payload, offset);
    // Extracción individual por paquete
    uint32_t seq = readUint32(payload, offset);
    double posX = readDouble(payload, offset);
    double posY = readDouble(payload, offset);
    double speed = readDouble(payload, offset);
    double co2 = readDouble(payload, offset);
    double sampleTimeSec = readDouble(payload, offset);

    (void)posX;
    (void)posY;
    (void)sessionId;
    (void)apId;

    ensureCsvOpen();

    NodeStats& st = statsMap_[nodeIdStr];

    if (carVectorsMap_.find(nodeIdStr) == carVectorsMap_.end()) {
        CarVectors* vecs = new CarVectors();
        vecs->networkDelayVec = new cOutVector(("networkDelay_" + nodeIdStr).c_str());
        vecs->lossRateVec = new cOutVector(("lossRate_" + nodeIdStr).c_str());
        vecs->appDelayVec = new cOutVector(("appDelay_" + nodeIdStr).c_str());
        vecs->jitterVec = new cOutVector(("jitter_" + nodeIdStr).c_str());
        vecs->receivedBatchesVec = new cOutVector(("receivedBatches_" + nodeIdStr).c_str());
        carVectorsMap_[nodeIdStr] = vecs;
    }
    CarVectors* vecs = carVectorsMap_[nodeIdStr];

    // Extraer tiempo de creación del paquete en la MAC para calcular Network Delay
    simtime_t txTime = txTimeDbl;

    simtime_t arrivalTime = simTime();
    simtime_t networkDelay = arrivalTime - txTime;
    double appDelay = arrivalTime.dbl() - sampleTimeSec;

    simtime_t jitter = SIMTIME_ZERO;
    if (st.rx_count > 0) {
        jitter = networkDelay - st.last_network_delay;
        if (jitter < SIMTIME_ZERO) jitter = -jitter;
    }

    if (st.rx_count > 0 && seq <= st.last_seq_id) return; // Duplicado o fuera de orden

    if (st.rx_count > 0 && seq > st.last_seq_id + 1) {
        st.lost_packets += (seq - st.last_seq_id - 1); // Cálculo PASIVO de Packet Loss UDP
    }

    st.last_seq_id = seq;
    st.last_network_delay = networkDelay;
    st.rx_count++;

    double loss_rate = (seq > 0) ? (static_cast<double>(st.lost_packets) / static_cast<double>(seq)) : 0.0;
    vecs->lossRateVec->record(loss_rate);
    if (csvFile_.is_open()) {
        csvFile_ << arrivalTime.dbl() << ","
                 << nodeIdStr << ","
                 << stopId << ","
                 << seq << ","
                 << networkDelay.dbl() << ","
                 << appDelay << ","
                 << jitter.dbl() << ","
                 << loss_rate << ","
                 << co2 << ","
                 << speed << "\n";
    }

    vecs->appDelayVec->record(appDelay);
    vecs->networkDelayVec->record(networkDelay);
    vecs->jitterVec->record(jitter);
    vecs->receivedBatchesVec->record(st.rx_count);

    emit(telemetryLatencySignal_, networkDelay.dbl());
    emit(telemetryCo2Signal_, co2);

    if (csvFile_.is_open()) csvFile_.flush();
}

void TelemetryReceiverUdpFinal::processEndSession(Packet* packet, const std::vector<uint8_t>& payload, size_t& offset)
{
    std::string nodeId = readString(payload, offset);
    uint32_t sessionId = readUint32(payload, offset);
    std::string apId = readString(payload, offset);
    std::string stopId = readString(payload, offset);
    std::string reason = readString(payload, offset);

    EV_INFO << "UDP END_SESSION bus=" << nodeId << " session=" << sessionId << " stop=" << stopId << " reason=" << reason << endl;
}

void TelemetryReceiverUdpFinal::ensureCsvOpen()
{
    if (csvFile_.is_open()) return;

    int runNumber = getEnvir()->getConfigEx()->getActiveRunNumber();
    std::ostringstream runStr;
    runStr << std::setw(2) << std::setfill('0') << runNumber;
    std::string filename = "results/telemetry_UDP_metrics_run" + runStr.str() + ".csv";

    csvFile_.open(filename.c_str(), std::ios::out);
    if (csvFile_.is_open())
        csvFile_ << "Time,NodeId,BusStop,SeqNo,NetworkDelay_Sec,AppDelay_Sec,Jitter_Sec,LossRate,CO2,Speed_mps\n";
}

void TelemetryReceiverUdpFinal::sendHelloAck(const L3Address& destAddr, int destPort, uint32_t dummyAckSeq)
{
    std::vector<uint8_t> payload;
    payload.push_back(MSG_HELLO_ACK);
    writeUint32(payload, dummyAckSeq);

    std::vector<uint8_t> frame;
    writeUint32(frame, static_cast<uint32_t>(payload.size()));
    frame.insert(frame.end(), payload.begin(), payload.end());

    Packet* ackPacket = new Packet("HelloAckUdp");
    auto bytes = makeShared<BytesChunk>(frame);
    ackPacket->insertAtBack(bytes);
    ackPacket->addTag<CreationTimeTag>()->setCreationTime(simTime());

    socket.sendTo(ackPacket, destAddr, destPort);
}

void TelemetryReceiverUdpFinal::socketErrorArrived(UdpSocket *s, Indication *indication) { delete indication; }
void TelemetryReceiverUdpFinal::socketClosed(UdpSocket *s) {}

void TelemetryReceiverUdpFinal::finish()
{
    if (csvFile_.is_open()) {
        csvFile_.flush();
        csvFile_.close();
    }
}

void TelemetryReceiverUdpFinal::writeUint32(std::vector<uint8_t>& buf, uint32_t v) {
    buf.push_back((v >> 24) & 0xFF); buf.push_back((v >> 16) & 0xFF);
    buf.push_back((v >> 8) & 0xFF); buf.push_back(v & 0xFF);
}
uint8_t TelemetryReceiverUdpFinal::readUint8(const std::vector<uint8_t>& buf, size_t& offset) { return buf[offset++]; }
uint16_t TelemetryReceiverUdpFinal::readUint16(const std::vector<uint8_t>& buf, size_t& offset) {
    uint16_t v = (static_cast<uint16_t>(buf[offset]) << 8) | static_cast<uint16_t>(buf[offset + 1]); offset += 2; return v;
}
uint32_t TelemetryReceiverUdpFinal::readUint32(const std::vector<uint8_t>& buf, size_t& offset) {
    uint32_t v = (static_cast<uint32_t>(buf[offset]) << 24) | (static_cast<uint32_t>(buf[offset + 1]) << 16) |
                 (static_cast<uint32_t>(buf[offset + 2]) << 8) | static_cast<uint32_t>(buf[offset + 3]);
    offset += 4; return v;
}
double TelemetryReceiverUdpFinal::readDouble(const std::vector<uint8_t>& buf, size_t& offset) {
    uint64_t raw = 0; for (int i = 0; i < 8; ++i) raw = (raw << 8) | static_cast<uint64_t>(buf[offset++]);
    double value; std::memcpy(&value, &raw, sizeof(double)); return value;
}
std::string TelemetryReceiverUdpFinal::readString(const std::vector<uint8_t>& buf, size_t& offset) {
    uint16_t len = readUint16(buf, offset);
    std::string s(buf.begin() + offset, buf.begin() + offset + len); offset += len; return s;
}

} // namespace simu5g
