package wifitelemetry.simulations;

@license(LGPL);

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.networklayer.ipv4.RoutingTableRecorder;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;
import inet.node.ethernet.Eth10G; // Import necesario para cables
import inet.common.misc.ThruputMeteringChannel;
// Necesario para tu canal custom

import inet.visualizer.common.IntegratedVisualizer;
import inet.environment.common.PhysicalEnvironment;
import org.car2x.veins.visualizer.roads.RoadsCanvasVisualizer;
import org.car2x.veins.visualizer.roads.RoadsOsgVisualizer;
import org.car2x.veins.subprojects.veins_inet.VeinsInetManager;
import org.car2x.veins.subprojects.veins_inet.VeinsInetCar;
import inet.physicallayer.wireless.ieee80211.packetlevel.Ieee80211DimensionalRadioMedium;
import inet.physicallayer.wireless.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;
import inet.node.inet.AdhocHost;
import inet.node.wireless.AccessPoint;
import inet.node.ethernet.EthernetSwitch;

network scenario12345
{
    parameters:
        double playgroundSizeX @unit(m);
        double playgroundSizeY @unit(m);
        double playgroundSizeZ @unit(m);
        bool useOsg = default(false);
        @display("bgb=1633,636");
    types:
        channel Eth10G extends ThruputMeteringChannel
        {
            datarate = 10Gbps;
            delay = 0.1us;
        }
    submodules:
        routingRecorder: RoutingTableRecorder {
            @display("p=73,246;is=s");
        }
        configurator: Ipv4NetworkConfigurator {
            @display("p=75,328;is=s");
        }
        veinsManager: VeinsInetManager {
            @display("p=82,416;is=s");
        }
        radioMedium: Ieee80211ScalarRadioMedium {
            @display("p=69,155");
        }

        node[0]: VeinsInetCar {
            @display("p=155,53");
        }
        // RSU ahora es AccessPoint (Puente L2: WiFi <-> Ethernet)
        rsu_1: AccessPoint {
            parameters:
                //numEthInterfaces = 1;
                @display("i=device/accesspoint;p=534.969,26.6");
        }
        rsu2: AccessPoint {
            parameters:
                //numEthInterfaces = 1;
                @display("i=device/accesspoint;p=1034.98,26.6");
        }

        rsu3: AccessPoint {
            parameters:
                //numEthInterfaces = 1;
                @display("i=device/accesspoint;p=1423.4,334.999");
        }

        rsu4: AccessPoint {
            parameters:
                //numEthInterfaces = 1;
                @display("i=device/accesspoint;p=315,523.4");
        }

        router: Router {
            parameters:
                @display("p=511,260");
        }
        server: AdhocHost {
            @display("p=675,259;i=device/server");
        }
        // --- VISUALIZADORES ---
        visualizer: IntegratedVisualizer {
            @display("p=72,505");
        }
        physicalEnvironment: PhysicalEnvironment {
            @display("p=68,609");
        }
        roadsCanvasVisualizer: RoadsCanvasVisualizer {
            @display("p=155,604");
        }
        roadsOsgVisualizer: RoadsOsgVisualizer if useOsg {
            @display("p=258,609");
        }

        // EL NUEVO SWITCH CENTRAL
        switch: EthernetSwitch {
            @display("p=460,120;i=device/switch");
        }

    connections allowunconnected:
        // Conectamos AMBOS RSUs (nombres explícitos) al Switch central
        rsu_1.ethg++ <--> Eth10G <--> switch.ethg++;
        rsu2.ethg++ <--> Eth10G <--> switch.ethg++;
        rsu3.ethg++ <--> Eth10G <--> switch.ethg++;
        rsu4.ethg++ <--> Eth10G <--> switch.ethg++;
        // Conexión del Switch al Router
        switch.ethg++ <--> Eth10G <--> router.ethg++;
        // Conexión del Router al Servidor
        router.ethg++ <--> Eth10G <--> server.ethg++;
}
