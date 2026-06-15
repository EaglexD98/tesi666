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

import inet.applications.contract.IApp;
import inet.mobility.contract.IMobility;
import inet.networklayer.common.InterfaceTable;
import inet.networklayer.contract.IRoutingTable;
import inet.networklayer.contract.INetworkLayer;
import inet.networklayer.configurator.ipv4.HostAutoConfigurator;
import inet.transportlayer.tcp.Tcp;
import inet.transportlayer.udp.Udp;
import inet.transportlayer.contract.ISctp;
import inet.transportlayer.contract.ITcp;
import inet.transportlayer.contract.IUdp;
import inet.common.MessageDispatcher;
import inet.common.packet.recorder.PcapRecorder;
import inet.linklayer.contract.IEthernetInterface;
import inet.linklayer.contract.ILoopbackInterface;
import inet.linklayer.ethernet.contract.IEthernetLayer;
import inet.node.inet.AdhocHost;
import simu5g.nodes.LteUe;
import simu5g.nodes.NrUe;
import simu5g.corenetwork.statsCollector.UeStatsCollector;
import simu5g.stack.ICellularNic;
import simu5g.corenetwork.statsCollector.NrUeStatsCollector;
import simu5g.nodes.LteUe;
import org.car2x.veins.base.modules.*;

//
// Wireless-enabled Host
//
module NrCarCustomresp extends AdhocHost
{
    parameters:
        @networkNode();
        @display("i=device/cellphone");
        @figure[applicationLayer](type=rectangle; pos=250,6; size=600,130; lineColor=#808080; cornerRadius=5; fillColor=#ffff00; fillOpacity=0.1);
        @figure[applicationLayer.title](type=text; pos=845,11; anchor=ne; text="application layer");
        @figure[transportLayer](type=rectangle; pos=250,156; size=600,130; fillColor=#ff0000; lineColor=#808080; cornerRadius=5; fillOpacity=0.1);
        @figure[transportLayer.title](type=text; pos=845,161; anchor=ne; text="transport layer");
        @figure[networkLayer](type=rectangle; pos=250,306; size=600,130; fillColor=#00ff00; lineColor=#808080; cornerRadius=5; fillOpacity=0.1);
        @figure[networkLayer.title](type=text; pos=845,311; anchor=ne; text="network layer");
        @figure[linkLayer](type=rectangle; pos=250,456; size=600,130; fillColor=#0000ff; lineColor=#808080; cornerRadius=5; fillOpacity=0.1);
        @figure[linkLayer.title](type=text; pos=845,461; anchor=ne; text="link layer");
        @figure[submodules];



		//# Apps
        bool hasRniSupport = default(false);
        cellularNic.mac.collectorModule = hasRniSupport ? "^.^.ueCollector" : "";
        cellularNic.phy.hasCollector = hasRniSupport;
        cellularNic.typename = default("NrNicUe");
        int nrMasterId @mutable = default(0);
        int nrMacNodeId @mutable = default(0); // TODO: this is not a real parameter
        int nrMacCellId @mutable = default(0); // TODO: this is not a real parameter
        cellularNic.nrMac.collectorModule = hasRniSupport ? "^.^.nrUeCollector" : "";
        cellularNic.nrPhy.hasCollector = hasRniSupport;

        @display("i=device/car");

        //# Mobility
        mobility.typename = default("VeinsInetMobility");

        //# Network Layer specs
        *.routingTableModule = default(absPath(".ipv4.routingTable"));

        ipv4.configurator.typename = "HostAutoConfigurator";
        ipv4.configurator.interfaces = "cellular lo0";


    gates:
        input LTEradioIn @directIn;     // connection to master
		input nrRadioIn @directIn;     // connection to master
    submodules:
        cellularNic: <default("LteNicUe")> like ICellularNic {
            nodeType = parent.nodeType;
            @display("p=106,973");
        }
        //# UeStatsCollector - for MEC
        ueCollector: UeStatsCollector if hasRniSupport {
            @display("p=126,588;is=s");
        }

        encap: <default("EthernetEncapsulation")> like IEthernetLayer if typename != "" {
            parameters:
                registerProtocol = true;
                @display("p=674,500");
        }
                //# UeStatsCollector - for MEC
        nrUeCollector: NrUeStatsCollector if hasRniSupport {
            @display("p=127,506;is=s");
        }
    connections allowunconnected:


	     //#
        //# Internal Tcp/Udp applications connections with transport layer
        //#

        for i=0..numApps-1 {
            app[i].socketOut --> at.in++;
            app[i].socketIn <-- at.out++;
        }

        at.out++ --> udp.appIn if hasUdp;
        at.in++ <-- udp.appOut if hasUdp;

        at.out++ --> tcp.appIn if hasTcp;
        at.in++ <-- tcp.appOut if hasTcp;

        at.out++ --> sctp.appIn if hasSctp;
        at.in++ <-- sctp.appOut if hasSctp;

        //#
		//# Internal transport layer connections to network layer
		//#

        udp.ipOut --> tn.in++ if hasUdp;
        udp.ipIn <-- tn.out++ if hasUdp;

        tcp.ipOut --> tn.in++ if hasTcp;
        tcp.ipIn <-- tn.out++ if hasTcp;

        sctp.ipOut --> tn.in++ if hasSctp;
        tn.out++ --> sctp.ipIn if hasSctp;

        ipv4.ifIn <-- nl.out++ if hasIpv4;
        ipv4.ifOut --> nl.in++ if hasIpv4;

        ipv4.transportIn <-- tn.out++ if hasIpv4;
        ipv4.transportOut --> tn.in++ if hasIpv4;

        ipv6.ifIn <-- nl.out++ if hasIpv6;
        ipv6.ifOut --> nl.in++ if hasIpv6;

        ipv6.transportIn <-- tn.out++ if hasIpv6;
        ipv6.transportOut --> tn.in++ if hasIpv6;

        tn.out++ --> nl.in++;
        tn.in++ <-- nl.out++;

        //#
        //# Internal link layer connections to network layer
        //#

        cellularNic.upperLayerOut --> nl.in++;
        cellularNic.upperLayerIn <-- nl.out++;

        for i=0..numEthInterfaces-1 {
            encap.lowerLayerOut --> eth[i].upperLayerIn;
            encap.lowerLayerIn <-- eth[i].upperLayerOut;
        }
        encap.upperLayerOut --> nl.in++ if numEthInterfaces != 0;
        encap.upperLayerIn <-- nl.out++ if numEthInterfaces != 0;

        for i=0..numLoInterfaces-1 {
            nl.out++ --> lo[i].upperLayerIn;
            lo[i].upperLayerOut --> nl.in++;
        }

        //#
        //# Connections between LTE/NR NIC and the radio medium
        //#
        cellularNic.radioIn <-- LTEradioIn;
        cellularNic.nrRadioIn <-- nrRadioIn;
}
