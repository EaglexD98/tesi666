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

#ifndef __WIFITELEMETRY_TELEMETRYRECEIVERTCPFINAL_H_
#define __WIFITELEMETRY_TELEMETRYRECEIVERTCPFINAL_H_

#include <fstream>
#include <map>
#include <string>
#include <vector>

#include <omnetpp.h>

#include <inet/common/INETDefs.h>
#include <inet/transportlayer/contract/tcp/TcpSocket.h>

namespace simu5g {

class TelemetryReceiverTcpFinal : public omnetpp::cSimpleModule, public inet::TcpSocket::ICallback
{
  protected:
    enum MessageType : uint8_t {
        MSG_HELLO = 1,
        MSG_DATA_BATCH = 2,
        MSG_END_SESSION = 3,
        MSG_HELLO_ACK = 4,
        MSG_APP_ACK = 5,
    };

    struct NodeStats {
        uint32_t rx_count = 0;
        uint32_t last_seq_id = 0;
        uint32_t lost_packets = 0;
        omnetpp::simtime_t last_network_delay = 0;
    };

    struct CarVectors {
        omnetpp::cOutVector* networkDelayVec = nullptr;
        omnetpp::cOutVector* appDelayVec = nullptr;
        omnetpp::cOutVector* jitterVec = nullptr;
        omnetpp::cOutVector* receivedBatchesVec = nullptr;
    };

    inet::TcpSocket socket;
    std::map<int, inet::TcpSocket*> clientSockets_;
    std::map<int, inet::Packet*> reassemblyQueues_;
    std::map<std::string, NodeStats> statsMap_;
    std::map<std::string, CarVectors*> carVectorsMap_;
    std::ofstream csvFile_;

    static omnetpp::simsignal_t telemetryLatencySignal_;
    static omnetpp::simsignal_t telemetryCo2Signal_;

  protected:
    virtual ~TelemetryReceiverTcpFinal();
    virtual int numInitStages() const override { return inet::NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleMessage(omnetpp::cMessage* msg) override;
    virtual void finish() override;

    virtual void socketAvailable(inet::TcpSocket* socket, inet::TcpAvailableInfo* availableInfo) override;
    virtual void socketEstablished(inet::TcpSocket* socket) override;
    virtual void socketPeerClosed(inet::TcpSocket* socket) override;
    virtual void socketClosed(inet::TcpSocket* socket) override;
    virtual void socketFailure(inet::TcpSocket* socket, int code) override;
    virtual void socketDataArrived(inet::TcpSocket* socket, inet::Packet* msg, bool urgent) override;
    virtual void socketStatusArrived(inet::TcpSocket* socket, inet::TcpStatusInfo* status) override;
    virtual void socketDeleted(inet::TcpSocket* socket) override;

    void startListening();
    void removeClientConnection(int socketId);
    void processCompleteMessage(inet::TcpSocket* socket, const std::vector<uint8_t>& payload);
    void processHello(inet::TcpSocket* socket, const std::vector<uint8_t>& payload, size_t& offset);
    void processDataBatch(inet::TcpSocket* socket, const std::vector<uint8_t>& payload, size_t& offset);
    void processEndSession(inet::TcpSocket* socket, const std::vector<uint8_t>& payload, size_t& offset);

    void ensureCsvOpen();
    void sendHelloAck(inet::TcpSocket* socket, uint32_t highestAckedSeq);
    void sendAppAck(inet::TcpSocket* socket, uint32_t highestAckedSeq);

    static void writeUint32(std::vector<uint8_t>& buf, uint32_t v);
    static uint8_t readUint8(const std::vector<uint8_t>& buf, size_t& offset);
    static uint16_t readUint16(const std::vector<uint8_t>& buf, size_t& offset);
    static uint32_t readUint32(const std::vector<uint8_t>& buf, size_t& offset);
    static double readDouble(const std::vector<uint8_t>& buf, size_t& offset);
    static std::string readString(const std::vector<uint8_t>& buf, size_t& offset);
};

} // namespace simu5g

#endif
