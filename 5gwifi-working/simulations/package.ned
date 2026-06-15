package _5gwifi.simulations;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.networklayer.ipv4.RoutingTableRecorder;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;
import inet.node.ethernet.Eth10G;

import inet.visualizer.common.IntegratedVisualizer;
import inet.environment.common.PhysicalEnvironment;
import org.car2x.veins.visualizer.roads.RoadsCanvasVisualizer;
import org.car2x.veins.visualizer.roads.RoadsOsgVisualizer;
import org.car2x.veins.subprojects.veins_inet.VeinsInetManager;
import org.car2x.veins.subprojects.veins_inet.VeinsInetCar;

import inet.physicallayer.wireless.ieee80211.packetlevel.Ieee80211DimensionalRadioMedium;

import simu5g.world.radio.LteChannelControl;
import simu5g.common.carrierAggregation.CarrierAggregation;
import simu5g.common.binder.Binder;
import simu5g.nodes.Upf;
import simu5g.nodes.gNodeB;
import simu5g.nodes.NrCar;

network scenariowork
{
    parameters:
        double playgroundSizeX @unit(m);
        double playgroundSizeY @unit(m);
        double playgroundSizeZ @unit(m);
        bool useOsg = default(false);
        @display("bgb=1147,506");

    submodules:
        routingRecorder: RoutingTableRecorder {
            @display("p=60,325;is=s");
        }
        configurator: Ipv4NetworkConfigurator {
            @display("p=62,357;is=s");
            config = xmldoc("demo.xml");
        }


        veinsManager: VeinsInetManager {
            @display("p=63,425;is=s");
        }


        radioMedium: Ieee80211DimensionalRadioMedium {
            @display("p=50,200");
        }


        channelControl: LteChannelControl {
            @display("p=56,277;is=s");
        }
        binder: Binder {
            @display("p=61,390;is=s");
        }
        carrierAggregation: CarrierAggregation {
            @display("p=63,461;is=s");
        }

        upf: Upf {
            @display("p=460,250");
        }
        router: Router {
            @display("p=560,250;i=device/smallrouter");
        }
        server: StandardHost {
            @display("p=670,250;is=n;i=device/server");
        }

        gNodeB1: gNodeB {
            @display("p=180,250;is=vl");
        }

        car[0]: NrCar {
            @display("p=924,195;i=device/smallcar");
        }

        node[0]: VeinsInetCar {
            @display("p=400,350");
        }

        rsu[1]: VeinsInetCar {
            @display("p=331,107;i=device/antennatower;is=vs");
        }

        visualizer: IntegratedVisualizer {
            @display("p=260,80");
        }
        physicalEnvironment: PhysicalEnvironment {
            @display("p=420,80");
        }
        roadsCanvasVisualizer: RoadsCanvasVisualizer {
            @display("p=580,80");
        }
        roadsOsgVisualizer: RoadsOsgVisualizer if useOsg {
            @display("p=740,80");
        }

    connections allowunconnected:
        server.pppg++ <--> Eth10G <--> router.pppg++;
        router.pppg++ <--> Eth10G <--> upf.filterGate;
        upf.pppg++    <--> Eth10G <--> gNodeB1.ppp;
}
