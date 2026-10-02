package simu5g.nodes;

import simu5g.nodes.NrCar;
import inet.linklayer.contract.IWirelessInterface;

module NrCarCustom2 extends NrUe

{
    parameters:
        @display("i=misc/bus_vl;bgb=1133,664");
        int numWlanInterfaces = default(1);
        wlan[*].mgmt.typename = default("Ieee80211MgmtAdhoc");
        wlan[*].agent.typename = default("");
        mobility.typename = default("VeinsInetMobility");
        *.routingTableModule = default(absPath(".ipv4.routingTable"));
        ipv4.configurator.typename = "HostAutoConfigurator";
        ipv4.configurator.interfaces = "cellular wlan0 lo0";
    gates:
        input wlanRadioIn[numWlanInterfaces] @directIn;

    submodules:
        wlan[numWlanInterfaces]: <default("Ieee80211Interface")> like IWirelessInterface {
            parameters:
                @display("p=1018,585,row,100;q=queue");
        }
    connections allowunconnected:

        for i=0..numWlanInterfaces-1 {
            wlanRadioIn[i] --> wlan[i].radioIn;
            wlan[i].upperLayerOut --> nl.in++;
            wlan[i].upperLayerIn <-- nl.out++;
        }

}
