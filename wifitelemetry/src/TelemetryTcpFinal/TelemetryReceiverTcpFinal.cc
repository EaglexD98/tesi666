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

#include "TelemetryReceiverTcpFinal.h"

#include <cstring>
#include <iomanip>
#include <sstream>

#include <inet/common/packet/Packet.h>
#include <inet/common/packet/chunk/BytesChunk.h>
#include <inet/common/TimeTag_m.h>

namespace simu5g {

Define_Module(TelemetryReceiverTcpFinal);

using namespace omnetpp;
using namespace inet;

simsignal_t TelemetryReceiverTcpFinal::telemetryLatencySignal_ = registerSignal("telemetryLatency");
simsignal_t TelemetryReceiverTcpFinal::telemetryCo2Signal_ = registerSignal("telemetryCo2");

TelemetryReceiverTcpFinal::~TelemetryReceiverTcpFinal()
{
    for (auto& kv : reassemblyQueues_)
        delete kv.second;
    for (auto& kv : clientSockets_)
        delete kv.second;
    for (auto& kv : carVectorsMap_) {
        delete kv.second->networkDelayVec;
        delete kv.second->appDelayVec;
        delete kv.second->jitterVec;
        delete kv.second->receivedBatchesVec;
        delete kv.second;
    }
}

void TelemetryReceiverTcpFinal::initialize(int stage)
{
    cSimpleModule::initialize(stage);
    if (stage == INITSTAGE_APPLICATION_LAYER) {
        socket.setOutputGate(gate("socketOut"));
        socket.setCallback(this);
        startListening();
    }
}

void TelemetryReceiverTcpFinal::startListening()
{
    int localPort = par("localPort");
    socket.bind(localPort);
    socket.listen();
}

void TelemetryReceiverTcpFinal::handleMessage(cMessage* msg)
{
    if (msg->isSelfMessage()) {
        delete msg;
        return;
    }

    for (auto const& [socketId, clientSocket] : clientSockets_) {
        if (clientSocket->belongsToSocket(msg)) {
            clientSocket->processMessage(msg);
            return;
        }
    }

    socket.processMessage(msg);
}

void TelemetryReceiverTcpFinal::removeClientConnection(int socketId)
{
    auto qIt = reassemblyQueues_.find(socketId);
    if (qIt != reassemblyQueues_.end()) {
        delete qIt->second;
        reassemblyQueues_.erase(qIt);
    }

    auto sIt = clientSockets_.find(socketId);
    if (sIt != clientSockets_.end()) {
        delete sIt->second;
        clientSockets_.erase(sIt);
    }
}

void TelemetryReceiverTcpFinal::socketAvailable(TcpSocket* s, TcpAvailableInfo* info)
{
    int newConnId = info->getNewSocketId();
    TcpSocket* newSocket = new TcpSocket(info);
    newSocket->setOutputGate(gate("socketOut"));
    newSocket->setCallback(this);
    clientSockets_[newConnId] = newSocket;
    s->accept(newConnId);
}

void TelemetryReceiverTcpFinal::socketDataArrived(TcpSocket* socket, Packet* pPacket, bool urgent)
{
    int connId = socket->getSocketId();

    if (reassemblyQueues_.find(connId) == reassemblyQueues_.end())
        reassemblyQueues_[connId] = new Packet(("ReassemblyQueue_" + std::to_string(connId)).c_str());

    Packet* queue = reassemblyQueues_[connId];
    queue->insertAtBack(pPacket->peekData());
    delete pPacket;

    while (queue->getDataLength() >= B(4)) {
        auto headerChunk = queue->peekAtFront<BytesChunk>(B(4));
        const auto& bytes = headerChunk->getBytes();

        uint32_t msgSize = (static_cast<uint32_t>(bytes[0]) << 24) |
                           (static_cast<uint32_t>(bytes[1]) << 16) |
                           (static_cast<uint32_t>(bytes[2]) << 8) |
                           static_cast<uint32_t>(bytes[3]);

        if (queue->getDataLength() < B(4) + B(msgSize))
            break;

        queue->popAtFront<BytesChunk>(B(4));
        auto payloadChunk = queue->popAtFront<BytesChunk>(B(msgSize));
        processCompleteMessage(socket, payloadChunk->getBytes());
    }
}

void TelemetryReceiverTcpFinal::processCompleteMessage(TcpSocket* socket, const std::vector<uint8_t>& payload)
{
    if (payload.empty())
        return;

    size_t offset = 0;
    uint8_t msgType = readUint8(payload, offset);

    switch (msgType) {
        case MSG_HELLO:
            processHello(socket, payload, offset);
            break;
        case MSG_DATA_BATCH:
            processDataBatch(socket, payload, offset);
            break;
        case MSG_END_SESSION:
            processEndSession(socket, payload, offset);
            break;
        default:
            EV_WARN << "Tipo de mensaje TCP desconocido: " << static_cast<int>(msgType) << endl;
            break;
    }
}

void TelemetryReceiverTcpFinal::processHello(TcpSocket* socket, const std::vector<uint8_t>& payload, size_t& offset)
{
    std::string nodeId = readString(payload, offset);
    uint32_t sessionId = readUint32(payload, offset);
    std::string apId = readString(payload, offset);
    std::string stopId = readString(payload, offset);
    std::string laneId = readString(payload, offset);
    bool readyToTransmit = readUint8(payload, offset) != 0;
    uint32_t firstPendingSeq = readUint32(payload, offset);
    uint32_t busLastAckSeen = readUint32(payload, offset);

    NodeStats& st = statsMap_[nodeId];

    EV_DEBUG << "HELLO bus=" << nodeId
             << " session=" << sessionId
             << " ap=" << apId
             << " stop=" << stopId
             << " lane=" << laneId
             << " ready=" << readyToTransmit
             << " firstPendingSeq=" << firstPendingSeq
             << " busLastAckSeen=" << busLastAckSeen << endl;

    sendHelloAck(socket, st.last_seq_id);
}

void TelemetryReceiverTcpFinal::processDataBatch(TcpSocket* socket, const std::vector<uint8_t>& payload, size_t& offset)
{
    std::string nodeIdStr = readString(payload, offset);
    uint32_t sessionId = readUint32(payload, offset);
    std::string apId = readString(payload, offset);
    std::string stopId = readString(payload, offset);
    uint32_t sampleCount = readUint32(payload, offset);
    simtime_t txTime = readDouble(payload, offset);

    ensureCsvOpen();

    NodeStats& st = statsMap_[nodeIdStr];

    if (carVectorsMap_.find(nodeIdStr) == carVectorsMap_.end()) {
        CarVectors* vecs = new CarVectors();
        vecs->networkDelayVec = new cOutVector(("networkDelay_" + nodeIdStr).c_str());
        vecs->appDelayVec = new cOutVector(("appDelay_" + nodeIdStr).c_str());
        vecs->jitterVec = new cOutVector(("jitter_" + nodeIdStr).c_str());
        vecs->receivedBatchesVec = new cOutVector(("receivedBatches_" + nodeIdStr).c_str());
        carVectorsMap_[nodeIdStr] = vecs;
    }
    CarVectors* vecs = carVectorsMap_[nodeIdStr];

    simtime_t networkDelay = simTime() - txTime;
    simtime_t jitter = SIMTIME_ZERO;
    if (st.rx_count > 0) {
        jitter = networkDelay - st.last_network_delay;
        if (jitter < SIMTIME_ZERO)
            jitter = -jitter;
    }

    simtime_t arrivalTime = simTime();
    bool hasNewSamples = false;

    for (uint32_t i = 0; i < sampleCount; ++i) {
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

        double appDelay = arrivalTime.dbl() - sampleTimeSec;

        if (st.rx_count > 0 && seq <= st.last_seq_id)
            continue;

        hasNewSamples = true;

        if (st.rx_count > 0 && seq > st.last_seq_id + 1)
            st.lost_packets += (seq - st.last_seq_id - 1);

        st.last_seq_id = seq;

        double loss_rate = (seq > 0) ? (static_cast<double>(st.lost_packets) / static_cast<double>(seq)) : 0.0;
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
        emit(telemetryLatencySignal_, networkDelay.dbl());
        emit(telemetryCo2Signal_, co2);
    }

    if (hasNewSamples) {
        st.last_network_delay = networkDelay;
        st.rx_count++;
        vecs->networkDelayVec->record(networkDelay);
        vecs->jitterVec->record(jitter);
        vecs->receivedBatchesVec->record(st.rx_count);
    }

    if (csvFile_.is_open())
        csvFile_.flush();

    sendAppAck(socket, st.last_seq_id);
}

void TelemetryReceiverTcpFinal::processEndSession(TcpSocket* socket, const std::vector<uint8_t>& payload, size_t& offset)
{
    std::string nodeId = readString(payload, offset);
    uint32_t sessionId = readUint32(payload, offset);
    std::string apId = readString(payload, offset);
    std::string stopId = readString(payload, offset);
    std::string reason = readString(payload, offset);
    uint32_t busLastAckSeen = readUint32(payload, offset);

    NodeStats& st = statsMap_[nodeId];

    EV_INFO << "END_SESSION bus=" << nodeId
            << " session=" << sessionId
            << " ap=" << apId
            << " stop=" << stopId
            << " reason=" << reason
            << " busLastAckSeen=" << busLastAckSeen
            << " serverLastAck=" << st.last_seq_id << endl;

    sendAppAck(socket, st.last_seq_id);
}

void TelemetryReceiverTcpFinal::ensureCsvOpen()
{
    if (csvFile_.is_open())
        return;

    int runNumber = getEnvir()->getConfigEx()->getActiveRunNumber();
    std::ostringstream runStr;
    runStr << std::setw(2) << std::setfill('0') << runNumber;
    std::string filename = "results/telemetry_metrics_run" + runStr.str() + ".csv";

    csvFile_.open(filename.c_str(), std::ios::out);
    if (csvFile_.is_open())
        csvFile_ << "Time,NodeId,BusStop,SeqNo,NetworkDelay_Sec,AppDelay_Sec,Jitter_Sec,LossRate,CO2,Speed_mps\n";
}

void TelemetryReceiverTcpFinal::sendHelloAck(TcpSocket* socket, uint32_t highestAckedSeq)
{
    std::vector<uint8_t> payload;
    payload.push_back(MSG_HELLO_ACK);
    writeUint32(payload, highestAckedSeq);

    std::vector<uint8_t> frame;
    writeUint32(frame, static_cast<uint32_t>(payload.size()));
    frame.insert(frame.end(), payload.begin(), payload.end());

    Packet* ackPacket = new Packet("HelloAckTcp");
    auto bytes = makeShared<BytesChunk>(frame);
    ackPacket->insertAtBack(bytes);
    ackPacket->addTag<CreationTimeTag>()->setCreationTime(simTime());
    socket->send(ackPacket);
}

void TelemetryReceiverTcpFinal::sendAppAck(TcpSocket* socket, uint32_t highestAckedSeq)
{
    std::vector<uint8_t> payload;
    payload.push_back(MSG_APP_ACK);
    writeUint32(payload, highestAckedSeq);

    std::vector<uint8_t> frame;
    writeUint32(frame, static_cast<uint32_t>(payload.size()));
    frame.insert(frame.end(), payload.begin(), payload.end());

    Packet* ackPacket = new Packet("AppAckTcp");
    auto bytes = makeShared<BytesChunk>(frame);
    ackPacket->insertAtBack(bytes);
    ackPacket->addTag<CreationTimeTag>()->setCreationTime(simTime());
    socket->send(ackPacket);
}

void TelemetryReceiverTcpFinal::writeUint32(std::vector<uint8_t>& buf, uint32_t v)
{
    buf.push_back((v >> 24) & 0xFF);
    buf.push_back((v >> 16) & 0xFF);
    buf.push_back((v >> 8) & 0xFF);
    buf.push_back(v & 0xFF);
}

uint8_t TelemetryReceiverTcpFinal::readUint8(const std::vector<uint8_t>& buf, size_t& offset)
{
    return buf[offset++];
}

uint16_t TelemetryReceiverTcpFinal::readUint16(const std::vector<uint8_t>& buf, size_t& offset)
{
    uint16_t v = (static_cast<uint16_t>(buf[offset]) << 8) | static_cast<uint16_t>(buf[offset + 1]);
    offset += 2;
    return v;
}

uint32_t TelemetryReceiverTcpFinal::readUint32(const std::vector<uint8_t>& buf, size_t& offset)
{
    uint32_t v = (static_cast<uint32_t>(buf[offset]) << 24) |
                 (static_cast<uint32_t>(buf[offset + 1]) << 16) |
                 (static_cast<uint32_t>(buf[offset + 2]) << 8) |
                 static_cast<uint32_t>(buf[offset + 3]);
    offset += 4;
    return v;
}

double TelemetryReceiverTcpFinal::readDouble(const std::vector<uint8_t>& buf, size_t& offset)
{
    uint64_t raw = 0;
    for (int i = 0; i < 8; ++i)
        raw = (raw << 8) | static_cast<uint64_t>(buf[offset++]);
    double value;
    std::memcpy(&value, &raw, sizeof(double));
    return value;
}

std::string TelemetryReceiverTcpFinal::readString(const std::vector<uint8_t>& buf, size_t& offset)
{
    uint16_t len = readUint16(buf, offset);
    std::string s(buf.begin() + offset, buf.begin() + offset + len);
    offset += len;
    return s;
}

void TelemetryReceiverTcpFinal::socketPeerClosed(TcpSocket* s)
{
    if (s->getState() == TcpSocket::PEER_CLOSED)
        s->close();
    removeClientConnection(s->getSocketId());
}

void TelemetryReceiverTcpFinal::socketClosed(TcpSocket* s)
{
    removeClientConnection(s->getSocketId());
}

void TelemetryReceiverTcpFinal::socketFailure(TcpSocket* s, int code)
{
    removeClientConnection(s->getSocketId());
}

void TelemetryReceiverTcpFinal::socketEstablished(TcpSocket* socket)
{
}

void TelemetryReceiverTcpFinal::socketStatusArrived(TcpSocket* socket, TcpStatusInfo* status)
{
    delete status;
}

void TelemetryReceiverTcpFinal::socketDeleted(TcpSocket* socket)
{
}

void TelemetryReceiverTcpFinal::finish()
{
    if (csvFile_.is_open()) {
        csvFile_.flush();
        csvFile_.close();
    }
}

} // namespace simu5g
