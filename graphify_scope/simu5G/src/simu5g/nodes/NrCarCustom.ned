//
//                  Simu5G
//
// Authors: Giovanni Nardini, Giovanni Stea, Antonio Virdis (University of Pisa)
//
// This file is part of a software released under the license included in file
// "license.pdf". Please read LICENSE and README files before using it.
// The above files and the present reference are part of the software itself,
// and cannot be removed from it.
//

package simu5g.nodes;

import inet.networklayer.configurator.ipv4.HostAutoConfigurator;
import inet.node.inet.WirelessHost;
import simu5g.stack.ICellularNic;
import simu5g.corenetwork.statsCollector.UeStatsCollector;
import org.car2x.veins.modules.nic.Nic80211p;

//import org.car2x.veins.subprojects.veins_inet.VeinsInetMobility;

//
// Wireless-enabled Host
//
module NrCarCustom extends WirelessHost
{
    parameters:
        numWlanInterfaces = default(1);
        @display("i=device/cellphone");


        bool enableLTE = default(false);
        bool enableDSRC = default(false);
        mobility.typename = default("StationaryMobility");
        string nodeType = "UE";  // DO NOT CHANGE
        int masterId @mutable;
        int macNodeId @mutable = default(0); // TODO: this is not a real parameter
        int macCellId @mutable = default(0); // TODO: this is not a real parameter
        string nicType = default("LteNicUe");

        //# Network Layer specs
        //        bool hasIpv4 = default(true);
        //        bool hasIpv6 = default(false);
        *.interfaceTableModule = default(absPath(".interfaceTable"));
        *.routingTableModule = default("^.ipv4.routingTable");

        //# External Ethernet interfaces
        //        int numEthInterfaces = default(0);
        string extHostAddress = default("");

        //# Loopback interfaces
//        int numLoInterfaces = default(1);

        //# Num of PcapRecorders
//        int numPcapRecorders = default(0); // no of PcapRecorders

        bool hasRNISupport = default(false);

        string applType = default(""); //type of the application layer
//        string nicType = default("Nic80211p"); // type of network interface card
        string veinsmobilityType = default("org.car2x.veins.modules.mobility.traci.TraCIMobility"); //type of the mobility module
    gates:
        input cellularRadioIn @directIn;     // connection to master
        input veinsradioIn @optional @directIn; // gate for sendDirect

    submodules:
        veinsApp: <applType> like org.car2x.veins.base.modules.IBaseApplLayer if enableDSRC {
            parameters:
                @display("i=block/app,p,1131.258,79.03;p=1131.258,79.03");
        }
        cellularNic: <nicType> like ICellularNic if enableLTE {
            nodeType = parent.nodeType;
            @display("p=570,987.6923");
        }
        nic: <default("Nic80211p")> like org.car2x.veins.modules.nic.INic80211p if enableDSRC {
            parameters:
                @display("p=1133.516,986.74603");
        }
        veinsmobility: <default("")> like org.car2x.veins.base.modules.IMobility if typename != "" {
            parameters:
                @display("p=124.19,824.17004;i=block/cogwheel;is=s");
        }
        ueCollector: UeStatsCollector if hasRNISupport {
            @display("p=124.61539,723.07697;is=s");
        }

    connections allowunconnected:
//        cellularNic.upperLayerOut --> li.in++;
//        cellularNic.upperLayerIn <-- li.out++;

        cellularNic.upperLayerOut --> nl.in++ if exists(cellularNic);
        cellularNic.upperLayerIn <-- nl.out++ if exists(cellularNic);
        cellularNic.radioIn <-- cellularRadioIn if exists(cellularNic);

        nic.upperLayerOut --> veinsApp.lowerLayerIn if exists(nic);
        nic.upperLayerIn <-- veinsApp.lowerLayerOut if exists(nic);
        nic.upperControlOut --> veinsApp.lowerControlIn if exists(nic);
        nic.upperControlIn <-- veinsApp.lowerControlOut if exists(nic);

        veinsradioIn --> nic.radioIn if exists(nic);
}
