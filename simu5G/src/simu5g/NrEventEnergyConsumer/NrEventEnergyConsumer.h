#ifndef __SIMU5G_NREVENTENERGYCONSUMER_H_
#define __SIMU5G_NREVENTENERGYCONSUMER_H_

#include "omnetpp.h"
#include "inet/power/contract/ICcEnergyConsumer.h"
#include "inet/power/contract/ICcEnergySource.h"
#include "inet/common/ModuleAccess.h"

using namespace inet;
using namespace inet::power;

namespace simu5g {

class NrEventEnergyConsumer : public omnetpp::cSimpleModule, public inet::power::ICcEnergyConsumer, public omnetpp::cListener
{
  protected:
    double supplyVoltage;
    double connectedSupplyCurrent;
    double txSupplyCurrent;
    double rxSupplyCurrent;
    double tti;

    A baseCurrent;
    A txCurrent;
    A rxCurrent;

    A currentConsumption = A(0);
    ICcEnergySource *energySource = nullptr;

    omnetpp::simsignal_t sigTxINET;
    omnetpp::simsignal_t sigRxINET;
    omnetpp::simsignal_t sigTxSimu5G;
    omnetpp::simsignal_t sigRxSimu5G;
    omnetpp::simsignal_t sigTxTransport;
    omnetpp::simsignal_t sigRxTransport;
    omnetpp::simsignal_t sigTxUp;
    omnetpp::simsignal_t sigRxUp;

    omnetpp::simsignal_t sigPacketPushed;
    omnetpp::simsignal_t sigPacketPulled;
    omnetpp::simsignal_t sigPacketPassed;

    omnetpp::simsignal_t sigSinrDl;
    omnetpp::simsignal_t sigServingCell;
    omnetpp::simsignal_t sigHandoverStart;

    // NUEVO: La señal directa desde nuestra antena física
    omnetpp::simsignal_t sigPhyTx;

    omnetpp::simsignal_t currentConsumptionChangedSignal;

    omnetpp::cMessage *resetPowerMsg = nullptr;
    omnetpp::cMessage *logBatteryMsg = nullptr;
    bool logToggle = false;

    double totalConsumedCoulombs = 0.0;

    omnetpp::cOutVector cumulativeEnergyVector;

    omnetpp::simtime_t lastCurrentChangeTime = omnetpp::SimTime::ZERO;

  public:
    virtual ~NrEventEnergyConsumer() {}
    virtual IEnergySource *getEnergySource() const override { return energySource; }
    virtual A getCurrentConsumption() const override { return currentConsumption; }

  protected:
    virtual void initialize(int stage) override;
    virtual int numInitStages() const override { return inet::NUM_INIT_STAGES; }
    virtual void finish() override;
    virtual void handleMessage(omnetpp::cMessage *msg) override;

    void subscribeRecursive(omnetpp::cModule *mod);

    virtual void receiveSignal(omnetpp::cComponent *source, omnetpp::simsignal_t signalID, intval_t value, omnetpp::cObject *details) override;
    virtual void receiveSignal(omnetpp::cComponent *source, omnetpp::simsignal_t signalID, double value, omnetpp::cObject *details) override;
    virtual void receiveSignal(omnetpp::cComponent *source, omnetpp::simsignal_t signalID, omnetpp::cObject *obj, omnetpp::cObject *details) override;
    virtual void receiveSignal(omnetpp::cComponent *source, omnetpp::simsignal_t signalID, const char *s, omnetpp::cObject *details) override;
    virtual void receiveSignal(omnetpp::cComponent *source, omnetpp::simsignal_t signalID, unsigned long l, omnetpp::cObject *details) override;
    virtual void receiveSignal(omnetpp::cComponent *source, omnetpp::simsignal_t signalID, bool b, omnetpp::cObject *details) override;

    void processActivity(omnetpp::simsignal_t signalID, omnetpp::cComponent *source);
    void changeCurrent(A newCurrent, omnetpp::cComponent *source = nullptr);
    void rescheduleResetMsg();
};

} // namespace simu5g

#endif
