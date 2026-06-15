//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 

#ifndef __WIFITELEMETRY_TELEMETRYSENDERUDPFINAL_H_
#define __WIFITELEMETRY_TELEMETRYSENDERUDPFINAL_H_

#include <deque>
#include <map>
#include <set>
#include <string>
#include <vector>

#include <omnetpp.h>

#include <inet/common/INETDefs.h>
#include <inet/common/ModuleAccess.h>
#include <inet/mobility/contract/IMobility.h>
#include <inet/networklayer/common/L3AddressResolver.h>
#include <inet/transportlayer/contract/udp/UdpSocket.h>

#include "veins_inet/VeinsInetMobility.h"
#include "veins/modules/mobility/traci/TraCICommandInterface.h"

namespace simu5g {

struct TelemetrySampleUdpFinal {
    uint32_t seq = 0;
    double posX = 0;
    double posY = 0;
    double speed = 0;
    double co2 = 0;
    double sampleTimeSec = 0;
};

class TelemetrySenderUdpFinal : public omnetpp::cSimpleModule,
                                public inet::UdpSocket::ICallback,
                                public omnetpp::cListener
{
  protected:
    enum MessageType : uint8_t {
        MSG_HELLO = 1,
        MSG_DATA_BURST = 2,
        MSG_END_SESSION = 3,
        MSG_HELLO_ACK = 4
    };

    enum TxState {
        COLLECTING = 0,
        ASSOCIATED_WAIT_STOP = 1,
        TX_ACTIVE = 2,
        TX_CLOSING = 3,
    };

    struct StopContext {
        bool stopped = false;
        bool atBusStop = false;
        std::string currentStopId;
        std::string currentLaneId;
        uint8_t rawStopState = 0;
    };

    inet::UdpSocket socket;
    inet::L3Address connectAddress_;
    inet::IMobility* mobility_ = nullptr;
    veins::VeinsInetMobility* veinsMobility_ = nullptr;
    veins::TraCICommandInterface* traci_ = nullptr;
    veins::TraCICommandInterface::Vehicle* traciVehicle_ = nullptr;

    int localPort_ = -1;
    int connectPort_ = -1;
    simtime_t sampleInterval_;
    simtime_t burstInterval_;
    simtime_t helloInterval_;
    simtime_t conditionCheckInterval_;
    simtime_t reconnectInterval_;
    simtime_t startTime_;

    omnetpp::cMessage* connectTimer_ = nullptr;
    omnetpp::cMessage* sampleTimer_ = nullptr;
    omnetpp::cMessage* burstTimer_ = nullptr;
    omnetpp::cMessage* helloTimer_ = nullptr;
    omnetpp::cMessage* conditionTimer_ = nullptr;
    omnetpp::cMessage* microDelayTimer_ = nullptr; // Timer para UDP puro (1ms)

    std::vector<TelemetrySampleUdpFinal> bufferA_;
    std::vector<TelemetrySampleUdpFinal> bufferB_;
    std::vector<TelemetrySampleUdpFinal>* activeBuffer_ = nullptr;
    std::vector<TelemetrySampleUdpFinal>* inactiveBuffer_ = nullptr;

    std::deque<std::vector<TelemetrySampleUdpFinal>> pendingBatches_;
    std::vector<TelemetrySampleUdpFinal> currentBurst_;
    uint32_t burstIndex_ = 0;

    bool isConnected_ = false;
    bool apAssociated_ = false;
    bool helloAckReceived_ = false;
    TxState state_ = COLLECTING;

    uint32_t sequenceNumber_ = 0;
    uint32_t sessionId_ = 0;

    StopContext stopCtx_;
    bool previousAtBusStop_ = false;
    std::vector<std::string> routeStops_;
    size_t nextStopIndex_ = 0;

    std::set<std::string> validStops_;

    std::string currentApId_ = "Disconnected";

    omnetpp::simsignal_t associatedSignal_ = SIMSIGNAL_NULL;
    omnetpp::simsignal_t associatedOldApSignal_ = SIMSIGNAL_NULL;
    omnetpp::simsignal_t disassociatedSignal_ = SIMSIGNAL_NULL;

  protected:
    virtual ~TelemetrySenderUdpFinal();
    virtual int numInitStages() const override { return inet::NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleMessage(omnetpp::cMessage* msg) override;
    virtual void finish() override;

    // Callbacks UDP
    virtual void socketDataArrived(inet::UdpSocket *socket, inet::Packet *packet) override;
    virtual void socketErrorArrived(inet::UdpSocket *socket, inet::Indication *indication) override;
    virtual void socketClosed(inet::UdpSocket *socket) override;

    // Listeners INET
    virtual void receiveSignal(omnetpp::cComponent* source, omnetpp::simsignal_t signalID, bool b, omnetpp::cObject* details) override;
    virtual void receiveSignal(omnetpp::cComponent* source, omnetpp::simsignal_t signalID, long l, omnetpp::cObject* details) override;
    virtual void receiveSignal(omnetpp::cComponent* source, omnetpp::simsignal_t signalID, unsigned long l, omnetpp::cObject* details) override;
    virtual void receiveSignal(omnetpp::cComponent* source, omnetpp::simsignal_t signalID, double d, omnetpp::cObject* details) override;
    virtual void receiveSignal(omnetpp::cComponent* source, omnetpp::simsignal_t signalID, const omnetpp::SimTime& t, omnetpp::cObject* details) override;
    virtual void receiveSignal(omnetpp::cComponent* source, omnetpp::simsignal_t signalID, const char* s, omnetpp::cObject* details) override;
    virtual void receiveSignal(omnetpp::cComponent* source, omnetpp::simsignal_t signalID, omnetpp::cObject* obj, omnetpp::cObject* details) override;

    void takeSample();
    void updateMobilityHandles();
    void updateStopContext();
    bool canTransmitNow() const;
    bool hasValidStop() const;
    bool stateAllowsHello() const;
    void evaluateTransmissionWindow();

    void startWaitingForStop();
    void startTransmissionWindow();
    void startClosingSession(const char* reason);
    void onAssociationStateChanged(omnetpp::simsignal_t signalID);

    void resolveConnectAddress();
    void doConnect();
    void ensureConnectTimer();

    void swapBuffersAndQueue();
    void triggerBurst();
    void sendNextBurstPacket();

    void sendHello(bool readyToTransmit);
    void sendEndSession(const char* reason);
    void processServerControlMessage(const std::vector<uint8_t>& payload);

    std::string getVehicleId() const;

    void parseRouteStopsParameter();
    void parseValidStopsParameter();

    static std::vector<std::string> split(const std::string& text, char delim);
    static std::string trim(const std::string& s);

    static void writeUint8(std::vector<uint8_t>& buf, uint8_t v);
    static void writeUint16(std::vector<uint8_t>& buf, uint16_t v);
    static void writeUint32(std::vector<uint8_t>& buf, uint32_t v);
    static void writeDouble(std::vector<uint8_t>& buf, double v);
    static void writeString(std::vector<uint8_t>& buf, const std::string& s);

    static uint8_t readUint8(const std::vector<uint8_t>& buf, size_t& offset);
    static uint16_t readUint16(const std::vector<uint8_t>& buf, size_t& offset);
    static uint32_t readUint32(const std::vector<uint8_t>& buf, size_t& offset);
    static double readDouble(const std::vector<uint8_t>& buf, size_t& offset);
    static std::string readString(const std::vector<uint8_t>& buf, size_t& offset);
};

} // namespace simu5g

#endif
