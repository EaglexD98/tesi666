package wifi_5g.simulations;

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
import inet.physicallayer.wireless.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;
import simu5g.world.radio.LteChannelControl;
import simu5g.common.carrierAggregation.CarrierAggregation;
import simu5g.common.binder.Binder;
import simu5g.nodes.Upf;
import simu5g.nodes.gNodeB;
import simu5g.nodes.NrCarCustom2;
import inet.node.wireless.AccessPoint;
import inet.node.ethernet.EthernetSwitch;

network Scenariov6g
{
    parameters:
        double playgroundSizeX @unit(m);
        double playgroundSizeY @unit(m);
        double playgroundSizeZ @unit(m);
        bool useOsg = default(false);
        @display("bgb=1520,600");

    types:
        channel Eth10G extends inet.common.misc.ThruputMeteringChannel
        {
            datarate = 10Gbps;
            delay = 0.1us;
        }

    submodules:
        routingRecorder: RoutingTableRecorder {
            @display("p=60,325;is=s");
        }
        configurator: Ipv4NetworkConfigurator {
            @display("p=62,357;is=s");
        }
        veinsManager: VeinsInetManager {
            @display("p=63,425;is=s");
        }
        radioMedium: Ieee80211ScalarRadioMedium {
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

        // Core 5G
        upf: Upf {
            @display("p=460,350");
        }
        gNodeB1: gNodeB {
            @display("p=180,350;is=vl");
        }

        // Core de Enrutamiento e Infraestructura
        router: Router {
            @display("p=560,250;i=device/smallrouter");
        }
		server: StandardHost {
            parameters:
                numEthInterfaces = 2; // <--- ESTO ES LA CLAVE: 2 cables físicos
            @display("p=750,250;is=n;i=device/server");
        }
        switch: EthernetSwitch {
            @display("p=400,100;i=device/switch");
        }

        // El vehículo híbrido
        car[0]: NrCarCustom2 {
            @display("p=924,195;i=device/smallcar");
        }

        // RSU como Access Point (Puente Capa 2)
        rsu1: AccessPoint {
            @display("p=150,90;i=device/accesspoint");
        }

        visualizer: IntegratedVisualizer {
            @display("p=1380,190");
        }
        physicalEnvironment: PhysicalEnvironment {
            @display("p=1360,90");
        }
        roadsCanvasVisualizer: RoadsCanvasVisualizer {
            @display("p=1390,370");
        }
        roadsOsgVisualizer: RoadsOsgVisualizer if useOsg {
            @display("p=1410,520");
        }

connections allowunconnected:
        // Wi-Fi
        rsu1.ethg++ <--> Eth10G <--> switch.ethg++;
        switch.ethg++ <--> Eth10G <--> router.ethg++;

        // 5G
		upf.pppg++ <--> Eth10G <--> gNodeB1.ppp;
        upf.filterGate <--> Eth10G <--> router.pppg++;

        // Servidor conectado DOS VECES al Router
        router.ethg++ <--> Eth10G <--> server.ethg++; // Link 1 (Wi-Fi/UDP)
        router.ethg++ <--> Eth10G <--> server.ethg++; // Link 2 (5G/VoIP)
}
