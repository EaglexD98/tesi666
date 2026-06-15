/*
 * MyHostAutoConfigurator.h
 *
 *  Created on: Dec 10, 2025
 *      Author: eagle
 */

#ifndef CUSTOMCONFIG_MYHOSTAUTOCONFIGURATOR_H_
#define CUSTOMCONFIG_MYHOSTAUTOCONFIGURATOR_H_

#include "../../inet/src/inet/networklayer/configurator/ipv4/HostAutoConfigurator.h"


namespace inet {

class MyHostAutoConfigurator : public HostAutoConfigurator
{
  protected:
    virtual void setupNetworkLayer() override;
};

} // namespace inet




#endif /* CUSTOMCONFIG_MYHOSTAUTOCONFIGURATOR_H_ */
