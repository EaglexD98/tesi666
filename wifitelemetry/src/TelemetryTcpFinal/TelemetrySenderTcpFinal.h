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

#ifndef __WIFITELEMETRY_TELEMETRYSENDERTCPFINAL_H_
#define __WIFITELEMETRY_TELEMETRYSENDERTCPFINAL_H_

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
#include <inet/transportlayer/contract/tcp/TcpSocket.h>

#include "veins_inet/VeinsInetMobility.h"
#include "veins/modules/mobility/traci/TraCICommandInterface.h"

namespace simu5g {

struct TelemetrySampleTcpFinal {
    uint32_t seq = 0;
    double posX = 0;
    double posY = 0;
    double speed = 0;
    double co2 = 0;
    double sampleTimeSec = 0;
};

class TelemetrySenderTcpFinal : public omnetpp::cSimpleModule,
                                public inet::TcpSocket::ICallback,
                                public omnetpp::cListener
{
  protected:
    enum MessageType : uint8_t {
        MSG_HELLO = 1,
        MSG_DATA_BATCH = 2,
        MSG_END_SESSION = 3,
        MSG_HELLO_ACK = 4,
        MSG_APP_ACK = 5,
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

    inet::TcpSocket socket;
    inet::L3Address connectAddress_;
    inet::IMobility* mobility_ = nullptr;
    veins::VeinsInetMobility* veinsMobility_ = nullptr;
    veins::TraCICommandInterface* traci_ = nullptr;
    veins::TraCICommandInterface::Vehicle* traciVehicle_ = nullptr;

    int localPort_ = -1;
    int connectPort_ = -1;
    simtime_t sampleInterval_;
    simtime_t batchInterval_;
    simtime_t helloInterval_;
    simtime_t conditionCheckInterval_;
    simtime_t reconnectInterval_;
    simtime_t startTime_;

    omnetpp::cMessage* connectTimer_ = nullptr;
    omnetpp::cMessage* sampleTimer_ = nullptr;
    omnetpp::cMessage* batchTimer_ = nullptr;
    omnetpp::cMessage* helloTimer_ = nullptr;
    omnetpp::cMessage* conditionTimer_ = nullptr;

    std::vector<TelemetrySampleTcpFinal> bufferA_;
    std::vector<TelemetrySampleTcpFinal> bufferB_;
    std::vector<TelemetrySampleTcpFinal>* activeBuffer_ = nullptr;
    std::vector<TelemetrySampleTcpFinal>* inactiveBuffer_ = nullptr;

    std::deque<std::vector<TelemetrySampleTcpFinal>> pendingBatches_;
    std::deque<std::vector<TelemetrySampleTcpFinal>> unackedBatches_;

    bool isConnected_ = false;
    bool apAssociated_ = false;
    bool helloAckReceived_ = false;
    TxState state_ = COLLECTING;

    uint32_t sequenceNumber_ = 0;
    uint32_t sessionId_ = 0;
    uint32_t lastAckedSeqSeen_ = 0;
    uint32_t serverHighestAckedSeq_ = 0;

    StopContext stopCtx_;
    bool previousAtBusStop_ = false;
    std::vector<std::string> routeStops_;
    size_t nextStopIndex_ = 0;

    std::set<std::string> validStops_;

    std::string currentApId_ = "Disconnected";

    // AQUÍ ESTÁN LAS MODIFICACIONES
    omnetpp::simsignal_t associatedSignal_ = SIMSIGNAL_NULL;
    omnetpp::simsignal_t associatedOldApSignal_ = SIMSIGNAL_NULL; // <-- Señal añadida
    omnetpp::simsignal_t disassociatedSignal_ = SIMSIGNAL_NULL;

  protected:
    virtual ~TelemetrySenderTcpFinal();
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
    void flushPendingBatches();
    void rescueUnackedBatches();
    void pruneAckedData(uint32_t ackSeq);

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
