/*
 * MyHostAutoConfigurator.cc
 *
 *  Created on: Dec 10, 2025
 *      Author: eagle
 */

/*
 * MyHostAutoConfigurator.cc
 */

#include "MyHostAutoConfigurator.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/networklayer/contract/ipv4/Ipv4Address.h"
#include "inet/networklayer/ipv4/Ipv4InterfaceData.h"

namespace inet {

Define_Module(MyHostAutoConfigurator);

void MyHostAutoConfigurator::setupNetworkLayer()
{
    EV_INFO << "MyHostAutoConfigurator started on host "
            << getContainingNode(this)->getFullPath() << endl;

    // Parámetros
    Ipv4Address addressBase = Ipv4Address(par("addressBase").stringValue());
    Ipv4Address netmask     = Ipv4Address(par("netmask").stringValue());
    std::string mcastGroups = par("mcastGroups").stdstringValue();

    // Nodo que contiene este configurador
    cModule *host = getContainingNode(this);

    // Igual que HostAutoConfigurator original: offset con el ID del módulo
    Ipv4Address myAddress(addressBase.getInt() + (uint32_t)host->getId());

    // Comprobar que cae dentro de la red
    if (!Ipv4Address::maskedAddrAreEqual(myAddress, addressBase, netmask))
        throw cRuntimeError("Generated IP address is out of specified address range");

    // Asegurarse de que la interfaceTable está disponible
    if (interfaceTable == nullptr)
        interfaceTable.reference(this, "interfaceTableModule", true);

    uint32_t loopbackAddr = Ipv4Address::LOOPBACK_ADDRESS.getInt();

    // Recorremos TODAS las interfaces del nodo
    for (int i = 0; i < interfaceTable->getNumInterfaces(); ++i) {
        NetworkInterface *ie = interfaceTable->getInterface(i);
        auto ipv4Data = ie->getProtocolDataForUpdate<Ipv4InterfaceData>();

        // Loopback: igual que el original
        if (ie->isLoopback()) {
            if (ipv4Data->getIPAddress().isUnspecified()) {
                ipv4Data->setIPAddress(Ipv4Address(loopbackAddr++));
                ipv4Data->setNetmask(Ipv4Address::LOOPBACK_NETMASK);
                ipv4Data->setMetric(1);
                EV_INFO << "loopback interface " << ie->getInterfaceName()
                        << " gets " << ipv4Data->getIPAddress() << "/"
                        << ipv4Data->getNetmask() << endl;
            }
            continue;
        }

        // Si YA tiene IP (por ejemplo, asignada por Ipv4NetworkConfigurator / 5G),
        // NO la tocamos.
        if (!ipv4Data->getIPAddress().isUnspecified()) {
            EV_INFO << "interface " << ie->getInterfaceName()
                    << " already has IP " << ipv4Data->getIPAddress()
                    << " -- leaving as is" << endl;
            continue;
        }

        // Opcional: si no quieres tocar la interfaz celular, descomenta esto:
        // if (!strcmp(ie->getInterfaceName(), "cellular"))
        //     continue;

        // Asignar IP a interfaces sin dirección (típicamente wlan[0])
        ipv4Data->setIPAddress(myAddress);
        ipv4Data->setNetmask(netmask);
        ie->setBroadcast(true);

        EV_INFO << "interface " << ie->getInterfaceName()
                << " gets " << ipv4Data->getIPAddress() << "/"
                << ipv4Data->getNetmask() << endl;

        // Grupos multicast por defecto
        ipv4Data->joinMulticastGroup(Ipv4Address::ALL_HOSTS_MCAST);
        ipv4Data->joinMulticastGroup(Ipv4Address::ALL_ROUTERS_MCAST);

        // Grupos multicast adicionales
        cStringTokenizer tok(mcastGroups.c_str());
        const char *mgroup;
        while ((mgroup = tok.nextToken()) != nullptr) {
            Ipv4Address mcastGroup(mgroup);
            ipv4Data->joinMulticastGroup(mcastGroup);
        }
    }
}

} // namespace inet


