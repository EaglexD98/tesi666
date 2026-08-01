#include "NrEventEnergyConsumer.h"

namespace simu5g {

Define_Module(NrEventEnergyConsumer);

void NrEventEnergyConsumer::initialize(int stage)
{
    if (stage == inet::INITSTAGE_LOCAL) {
        supplyVoltage = par("supplyVoltage").doubleValue();
        connectedSupplyCurrent = par("connectedSupplyCurrent").doubleValue();
        txSupplyCurrent = par("txSupplyCurrent").doubleValue();
        rxSupplyCurrent = par("rxSupplyCurrent").doubleValue();
        tti = par("tti").doubleValue();

        baseCurrent = A(connectedSupplyCurrent / 1000.0);
        txCurrent   = A(txSupplyCurrent / 1000.0);
        rxCurrent   = A(rxSupplyCurrent / 1000.0);

        sigTxINET = registerSignal("packetSentToLower");
        sigRxINET = registerSignal("packetReceivedFromLower");
        sigTxSimu5G = registerSignal("sentPacketToLowerLayer");
        sigRxSimu5G = registerSignal("receivedPacketFromLowerLayer");
        sigTxTransport = registerSignal("packetSent");
        sigRxTransport = registerSignal("packetReceived");
        sigTxUp = registerSignal("packetSentToUpper");
        sigRxUp = registerSignal("packetReceivedFromUpper");

        sigPacketPushed = registerSignal("packetPushed");
        sigPacketPulled = registerSignal("packetPulled");
        sigPacketPassed = registerSignal("packetPassed");

        sigSinrDl = registerSignal("measuredSinrDl");
        sigServingCell = registerSignal("servingCellChanged");
        sigHandoverStart = registerSignal("handoverStarted");

        // NUEVO: Registramos la señal pura de la antena
        sigPhyTx = registerSignal("phyTxSignal");

        currentConsumptionChangedSignal = registerSignal("currentConsumptionChanged");

        omnetpp::cModule *parent = getParentModule();
        if (parent != nullptr) {
            const char *scope = par("subscriptionScope").stringValue();
            omnetpp::cModule *target = parent;
            if (scope[0] != '\0') {
                omnetpp::cModule *sub = parent->getSubmodule(scope);
                if (sub != nullptr)
                    target = sub;          // scope capture to e.g. cellularNic
                else
                    EV_WARN << "subscriptionScope '" << scope
                            << "' not found; subscribing to whole node\n";
            }
            subscribeRecursive(target);
        }

        resetPowerMsg = new omnetpp::cMessage("resetPowerMsg");
        logBatteryMsg = new omnetpp::cMessage("logBatteryMsg");

        const char *energySourceModule = par("energySourceModule").stringValue();
        energySource = omnetpp::check_and_cast<inet::power::ICcEnergySource *>(getModuleByPath(energySourceModule));

        cumulativeEnergyVector.setName("Cumulative_Energy_Joules_J");

        currentConsumption = baseCurrent;
        lastCurrentChangeTime = simTime();
    }
    else if (stage == inet::INITSTAGE_POWER) {
        energySource->addEnergyConsumer(this);
        emit(currentConsumptionChangedSignal, currentConsumption.get());

        scheduleAt(simTime() + 0.1, logBatteryMsg);
    }
}

void NrEventEnergyConsumer::subscribeRecursive(omnetpp::cModule *mod)
{
    if (!mod) return;

    mod->subscribe(sigTxINET, this);
    mod->subscribe(sigRxINET, this);
    mod->subscribe(sigTxSimu5G, this);
    mod->subscribe(sigRxSimu5G, this);
    mod->subscribe(sigTxTransport, this);
    mod->subscribe(sigRxTransport, this);
    mod->subscribe(sigTxUp, this);
    mod->subscribe(sigRxUp, this);

    mod->subscribe(sigPacketPushed, this);
    mod->subscribe(sigPacketPulled, this);
    mod->subscribe(sigPacketPassed, this);

    mod->subscribe(sigSinrDl, this);
    mod->subscribe(sigServingCell, this);
    mod->subscribe(sigHandoverStart, this);

    // NUEVO: Nos anclamos a la señal limpia que inyectamos en LtePhyBase
    mod->subscribe(sigPhyTx, this);

    for (omnetpp::cModule::SubmoduleIterator it(mod); !it.end(); ++it) {
        subscribeRecursive(*it);
    }
}

void NrEventEnergyConsumer::finish()
{
    omnetpp::simtime_t now = simTime();
    if (now > lastCurrentChangeTime) {
        double dt = (now - lastCurrentChangeTime).dbl();
        totalConsumedCoulombs += currentConsumption.get() * dt;
    }

    double total_mAh = totalConsumedCoulombs / 3.6;
    double total_Joules = totalConsumedCoulombs * supplyVoltage;
    double simDuration = now.dbl();
    double avg_power_W = (simDuration > 0) ? (total_Joules / simDuration) : 0.0;

    recordScalar("Total_Consumed_Coulombs_C", totalConsumedCoulombs);
    recordScalar("Total_Consumed_mAh", total_mAh);
    recordScalar("Total_Energy_Joules_J", total_Joules);
    recordScalar("Average_Power_Watts_W", avg_power_W);

    if (resetPowerMsg) {
        cancelAndDelete(resetPowerMsg);
    }
    if (logBatteryMsg) {
        cancelAndDelete(logBatteryMsg);
    }
}

void NrEventEnergyConsumer::handleMessage(omnetpp::cMessage *msg)
{
    if (msg == resetPowerMsg) {
        changeCurrent(baseCurrent);
    }
    else if (msg == logBatteryMsg) {

        omnetpp::simtime_t now = simTime();
        if (now > lastCurrentChangeTime) {
            double dt = (now - lastCurrentChangeTime).dbl();
            totalConsumedCoulombs += currentConsumption.get() * dt;
            lastCurrentChangeTime = now;
        }

        double currentJoules = totalConsumedCoulombs * supplyVoltage;
        cumulativeEnergyVector.record(currentJoules);

        emit(currentConsumptionChangedSignal, currentConsumption.get());
        scheduleAt(simTime() + 0.1, logBatteryMsg);
    }
    else {
        delete msg;
    }
}

void NrEventEnergyConsumer::receiveSignal(omnetpp::cComponent *source, omnetpp::simsignal_t signalID, intval_t value, omnetpp::cObject *details) {
    Enter_Method_Silent();
    processActivity(signalID, source);
}

void NrEventEnergyConsumer::receiveSignal(omnetpp::cComponent *source, omnetpp::simsignal_t signalID, double value, omnetpp::cObject *details) {
    Enter_Method_Silent();
    processActivity(signalID, source);
}

void NrEventEnergyConsumer::receiveSignal(omnetpp::cComponent *source, omnetpp::simsignal_t signalID, omnetpp::cObject *obj, omnetpp::cObject *details) {
    Enter_Method_Silent();
    processActivity(signalID, source);
}

void NrEventEnergyConsumer::receiveSignal(omnetpp::cComponent *source, omnetpp::simsignal_t signalID, const char *s, omnetpp::cObject *details) {
    Enter_Method_Silent();
    processActivity(signalID, source);
}

void NrEventEnergyConsumer::receiveSignal(omnetpp::cComponent *source, omnetpp::simsignal_t signalID, unsigned long l, omnetpp::cObject *details) {
    Enter_Method_Silent();
    processActivity(signalID, source);
}

void NrEventEnergyConsumer::receiveSignal(omnetpp::cComponent *source, omnetpp::simsignal_t signalID, bool b, omnetpp::cObject *details) {
    Enter_Method_Silent();
    processActivity(signalID, source);
}

void NrEventEnergyConsumer::processActivity(omnetpp::simsignal_t signalID, omnetpp::cComponent *source)
{
    // AHORA DETECTAMOS EL TX DE LA CAPA FÍSICA AÑADIENDO sigPhyTx
    if (signalID == sigTxINET || signalID == sigTxSimu5G || signalID == sigTxTransport || signalID == sigTxUp ||
        signalID == sigPacketPushed || signalID == sigPacketPulled || signalID == sigPacketPassed ||
        signalID == sigPhyTx) {

        changeCurrent(txCurrent, source);
        rescheduleResetMsg();
    }
    else if (signalID == sigRxINET || signalID == sigRxSimu5G || signalID == sigRxTransport || signalID == sigRxUp ||
             signalID == sigSinrDl || signalID == sigServingCell || signalID == sigHandoverStart) {

        if (currentConsumption != txCurrent) {
            changeCurrent(rxCurrent, source);
        }
        rescheduleResetMsg();
    }
}

void NrEventEnergyConsumer::rescheduleResetMsg()
{
    if (resetPowerMsg->isScheduled()) {
        cancelEvent(resetPowerMsg);
    }
    scheduleAt(simTime() + tti, resetPowerMsg);
}

void NrEventEnergyConsumer::changeCurrent(A newCurrent, omnetpp::cComponent *source)
{
    if (currentConsumption != newCurrent) {

        if (newCurrent == txCurrent) {
            EV_INFO << "[[ BATERÍA 5G ]] ---> PICO TX (Enviando) | Origen: " << (source ? source->getFullPath() : "N/A") << "\n";
        } else if (newCurrent == rxCurrent) {
            EV_INFO << "[[ BATERÍA 5G ]] ---> PICO RX / CONTROL | Origen: " << (source ? source->getFullPath() : "N/A") << "\n";
        }

        omnetpp::simtime_t now = simTime();
        if (now > lastCurrentChangeTime) {
            double dt = (now - lastCurrentChangeTime).dbl();
            totalConsumedCoulombs += currentConsumption.get() * dt;
            lastCurrentChangeTime = now;
        }

        currentConsumption = newCurrent;
        emit(currentConsumptionChangedSignal, currentConsumption.get());
    }
}

} // namespace simu5g
