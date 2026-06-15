//
// Copyright (C) 2009 Christoph Sommer <christoph.sommer@informatik.uni-erlangen.de>
//
// SPDX-License-Identifier: LGPL-3.0-or-later
//

#include "inet/networklayer/configurator/ipv4/HostAutoConfigurator.h"
#include <algorithm>
#include "inet/common/ModuleAccess.h"
#include "inet/common/lifecycle/ModuleOperations.h"
#include "inet/common/lifecycle/NodeStatus.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/networklayer/contract/ipv4/Ipv4Address.h"
#include "inet/networklayer/ipv4/Ipv4InterfaceData.h"
#include "inet/networklayer/ipv4/Ipv4Route.h"

namespace inet {

Define_Module(HostAutoConfigurator);

void HostAutoConfigurator::initialize(int stage)
{
    OperationalBase::initialize(stage);
    if (stage == INITSTAGE_LOCAL) {
        interfaceTable.reference(this, "interfaceTableModule", true);
    }
}

void HostAutoConfigurator::finish()
{
}

void HostAutoConfigurator::handleMessageWhenUp(cMessage *apMsg)
{
}

void HostAutoConfigurator::setupNetworkLayer()
{
    EV_INFO << "host auto configuration started" << std::endl;

    std::string interfaces = par("interfaces");
    Ipv4Address addressBase = Ipv4Address(par("addressBase").stringValue());
    Ipv4Address netmask = Ipv4Address(par("netmask").stringValue());
    std::string mcastGroups = par("mcastGroups").stdstringValue();

    // get our host module
    cModule *host = getContainingNode(this);

    // Calculamos la IP principal (para Cellular/5G) basada en el rango inicial de addressBase
    // Aplicamos una operación módulo para garantizar que la suma jamás desborde la máscara /24 (límite 255)
    int safeOctet = (host->getId() % 253) + 2; // Genera un sufijo seguro entre 2 y 254
    Ipv4Address myAddress = Ipv4Address(addressBase.getInt() + uint32_t(safeOctet));

    // address test
    if (!Ipv4Address::maskedAddrAreEqual(myAddress, addressBase, netmask))
        throw cRuntimeError("Generated IP address is out of specified address range");

    // get our routing table
    IIpv4RoutingTable *routingTable = L3AddressResolver().getIpv4RoutingTableOf(host);
    if (!routingTable)
        throw cRuntimeError("No routing table found");

    // look at all interface table entries
    cStringTokenizer interfaceTokenizer(interfaces.c_str());
    const char *ifname;
    uint32_t loopbackAddr = Ipv4Address::LOOPBACK_ADDRESS.getInt();

    while ((ifname = interfaceTokenizer.nextToken()) != nullptr) {
        NetworkInterface *ie = interfaceTable->findInterfaceByName(ifname);
        if (!ie)
            throw cRuntimeError("No such interface '%s'", ifname);

        auto ipv4Data = ie->getProtocolDataForUpdate<Ipv4InterfaceData>();

        // 1. Configuración Loopback (Sin cambios)
        if (ie->isLoopback()) {
            ipv4Data->setIPAddress(Ipv4Address(loopbackAddr++));
            ipv4Data->setNetmask(Ipv4Address::LOOPBACK_NETMASK);
            ipv4Data->setMetric(1);
            EV_INFO << "loopback interface " << ifname << " gets " << ipv4Data->getIPAddress() << "/" << ipv4Data->getNetmask() << std::endl;
            continue;
        }

        // --- INICIO DE LA MODIFICACIÓN Y RUTEO ---

        Ipv4Address addrToSet;
        Ipv4Address maskToSet;

        // Detectamos si es la interfaz WiFi
        if (strstr(ifname, "wlan") != nullptr) {
            // Lógica para asignar IP en la red Wi-Fi 10.0.0.x
            int uniqueOctet = host->getId() % 254 + 1;
            addrToSet = Ipv4Address(10, 0, 0, 50 + uniqueOctet);
            maskToSet = Ipv4Address("255.255.255.0");

            ipv4Data->setIPAddress(addrToSet);
            ipv4Data->setNetmask(maskToSet);

            // INYECCIÓN DE RUTA WI-FI MANUAL
            Ipv4Route *wifiRoute = new Ipv4Route();
            wifiRoute->setDestination(Ipv4Address("10.1.0.0")); // Subred del servidor
            wifiRoute->setNetmask(Ipv4Address("255.255.255.0"));
            wifiRoute->setGateway(Ipv4Address("10.0.0.1"));     // Interfaz eth0 del router
            wifiRoute->setInterface(ie);
            wifiRoute->setSource(this);
            wifiRoute->setSourceType(IRoute::MANUAL);
            routingTable->addRoute(wifiRoute);

            EV_INFO << "CUSTOM WIFI: interface " << ifname << " gets IP " << addrToSet.str() << " and route to server via 10.0.0.1" << std::endl;
        }
        else if (strstr(ifname, "cellular") != nullptr) {
            addrToSet = myAddress;
            maskToSet = netmask;
            ipv4Data->setIPAddress(addrToSet);
            ipv4Data->setNetmask(maskToSet);

            // Inyectamos la ruta hacia el servidor VoIP (10.2.0.0)
            // a través del gateway 10.5.1.1 (IP del UPF en 5G, la cual ahora pertenece a la subred de addressBase)
            Ipv4Route *voipRoute = new Ipv4Route();
            voipRoute->setDestination(Ipv4Address("10.2.0.0"));
            voipRoute->setNetmask(Ipv4Address("255.255.255.0"));
            voipRoute->setGateway(Ipv4Address("10.5.1.1"));
            voipRoute->setInterface(ie);
            voipRoute->setSource(this);
            voipRoute->setSourceType(IRoute::MANUAL);
            routingTable->addRoute(voipRoute);

            EV_INFO << "CELLULAR route to VoIP added." << std::endl;
        }
        else {
            addrToSet = Ipv4Address(myAddress.getInt() + ie->getInterfaceId());
            maskToSet = netmask;
            ipv4Data->setIPAddress(addrToSet);
            ipv4Data->setNetmask(maskToSet);
            EV_INFO << "OTHER INTERFACE: " << ifname << " gets " << addrToSet.str() << "/" << maskToSet.str() << std::endl;
        }

        // --- FIN DE LA MODIFICACIÓN Y RUTEO ---

        ie->setBroadcast(true);

        // associate interface with default multicast groups
        ipv4Data->joinMulticastGroup(Ipv4Address::ALL_HOSTS_MCAST);
        ipv4Data->joinMulticastGroup(Ipv4Address::ALL_ROUTERS_MCAST);

        // associate interface with specified multicast groups
        cStringTokenizer mcastTokenizer(mcastGroups.c_str());
        const char *mcastGroup_s;
        while ((mcastGroup_s = mcastTokenizer.nextToken()) != nullptr) {
            Ipv4Address mcastGroup(mcastGroup_s);
            ipv4Data->joinMulticastGroup(mcastGroup);
        }
    }
}

void HostAutoConfigurator::handleStartOperation(LifecycleOperation *operation)
{
    if (operation == nullptr) {
        for (int i = 0; i < interfaceTable->getNumInterfaces(); i++)
            interfaceTable->getInterface(i)->addProtocolData<Ipv4InterfaceData>();
    }
    setupNetworkLayer();
}

void HostAutoConfigurator::handleStopOperation(LifecycleOperation *operation)
{
}

void HostAutoConfigurator::handleCrashOperation(LifecycleOperation *operation)
{
}

} // namespace inet
