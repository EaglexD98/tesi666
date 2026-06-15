#include "inet/power/storage/SimpleCcBattery.h"
#include "omnetpp/ccomponent.h"
#include "omnetpp/csimplemodule.h"
#include "omnetpp.h"

namespace inet {
namespace power {

class WifiBattery : public SimpleCcBattery {
  protected:
    virtual void finish() override {
        // 1. Resolvemos la ambigüedad original llamando a la raíz de OMNeT++
        omnetpp::cComponent::finish();

        // 2. Usamos "this->" para obligar al compilador a reconocer las funciones heredadas
        double initialC = this->par("initialCapacity").doubleValue();
        double voltage = this->par("nominalVoltage").doubleValue();

        // 3. Usamos el Getter oficial de la arquitectura Cc de INET 4.x
        double finalC = this->getResidualChargeCapacity().get();

        // 4. Matemáticas para tu informe
        double consumedC = initialC - finalC;
        double consumed_mAh = consumedC / 3.6;
        double energyJ = consumedC * voltage;

        double timeSec = omnetpp::simTime().dbl();
        double powerW = (timeSec > 0) ? (energyJ / timeSec) : 0.0;

        // 5. Usamos "this->" para guardar los resultados sin errores de "identificador no declarado"
        this->recordScalar("Total_Consumed_Coulombs_C", consumedC);
        this->recordScalar("Total_Consumed_mAh", consumed_mAh);
        this->recordScalar("Total_Energy_Joules_J", energyJ);
        this->recordScalar("Average_Power_Watts_W", powerW);
    }
};

Define_Module(WifiBattery);

} // namespace power
} // namespace inet
