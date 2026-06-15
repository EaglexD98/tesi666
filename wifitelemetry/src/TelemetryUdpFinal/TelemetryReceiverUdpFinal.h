//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 

#ifndef __WIFITELEMETRY_TELEMETRYRECEIVERUDPFINAL_H_
#define __WIFITELEMETRY_TELEMETRYRECEIVERUDPFINAL_H_

#include <fstream>
#include <map>
#include <string>
#include <vector>

#include <omnetpp.h>

#include <inet/common/INETDefs.h>
#include <inet/transportlayer/contract/udp/UdpSocket.h>

namespace simu5g {

class TelemetryReceiverUdpFinal : public omnetpp::cSimpleModule, public inet::UdpSocket::ICallback
{
  protected:
    enum MessageType : uint8_t {
        MSG_HELLO = 1,
        MSG_DATA_BURST = 2,
        MSG_END_SESSION = 3,
        MSG_HELLO_ACK = 4
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
        omnetpp::cOutVector* lossRateVec = nullptr;
    };

    inet::UdpSocket socket;
    std::map<std::string, NodeStats> statsMap_;
    std::map<std::string, CarVectors*> carVectorsMap_;
    std::ofstream csvFile_;

    static omnetpp::simsignal_t telemetryLatencySignal_;
    static omnetpp::simsignal_t telemetryCo2Signal_;

  protected:
    virtual ~TelemetryReceiverUdpFinal();
    virtual int numInitStages() const override { return inet::NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleMessage(omnetpp::cMessage* msg) override;
    virtual void finish() override;

    // Callbacks de UDP
    virtual void socketDataArrived(inet::UdpSocket *socket, inet::Packet *packet) override;
    virtual void socketErrorArrived(inet::UdpSocket *socket, inet::Indication *indication) override;
    virtual void socketClosed(inet::UdpSocket *socket) override;

    void processCompleteMessage(inet::Packet* packet, const std::vector<uint8_t>& payload);
    void processHello(inet::Packet* packet, const std::vector<uint8_t>& payload, size_t& offset);
    void processDataBurst(inet::Packet* packet, const std::vector<uint8_t>& payload, size_t& offset);
    void processEndSession(inet::Packet* packet, const std::vector<uint8_t>& payload, size_t& offset);

    void ensureCsvOpen();
    void sendHelloAck(const inet::L3Address& destAddr, int destPort, uint32_t dummyAckSeq);

    static void writeUint32(std::vector<uint8_t>& buf, uint32_t v);
    static uint8_t readUint8(const std::vector<uint8_t>& buf, size_t& offset);
    static uint16_t readUint16(const std::vector<uint8_t>& buf, size_t& offset);
    static uint32_t readUint32(const std::vector<uint8_t>& buf, size_t& offset);
    static double readDouble(const std::vector<uint8_t>& buf, size_t& offset);
    static std::string readString(const std::vector<uint8_t>& buf, size_t& offset);
};

} // namespace simu5g

#endif
