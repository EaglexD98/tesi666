//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
//

package wifitelemetry.simulations;
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

network M4miglia
{
    parameters:
        double playgroundSizeX @unit(m);
        double playgroundSizeY @unit(m);
        double playgroundSizeZ @unit(m);
        bool useOsg = default(false);
        @display("bgb=8840,6943");
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
            @display("p=108,953");
        }
        // RSU ahora es AccessPoint (Puente L2: WiFi <-> Ethernet)
        rsu1: AccessPoint {
            parameters:
                //numEthInterfaces = 1;
                @display("i=device/accesspoint;p=2900,3010.70");
        }
        rsu2: AccessPoint {
            parameters:
                //numEthInterfaces = 1;
                @display("i=device/accesspoint;p=3705.40, 3283.02");
        }

        rsu3: AccessPoint {
            parameters:
                //numEthInterfaces = 1;
                @display("i=device/accesspoint;p=3982,6149");
        }

        rsu4: AccessPoint {
            parameters:
                //numEthInterfaces = 1;
                @display("i=device/accesspoint;p=4352,4764");
        }

        rsu5: AccessPoint {
            parameters:
                //numEthInterfaces = 1;
                @display("i=device/accesspoint;p=4168,3047");
        }

        rsu6: AccessPoint {
            parameters:
                //numEthInterfaces = 1;
                @display("i=device/accesspoint;p=4218.59, 4124.64");
        }


        router: Router {
            parameters:
                @display("p=1097,153");
        }
        server: AdhocHost {
            @display("p=2117,157;i=device/server");
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
            @display("p=1097,737;i=device/switch");
        }

    connections allowunconnected:
        // Conectamos RSUs al Switch central
        rsu1.ethg++ <--> Eth10G <--> switch.ethg++;
        rsu2.ethg++ <--> Eth10G <--> switch.ethg++;
        rsu3.ethg++ <--> Eth10G <--> switch.ethg++;
        rsu4.ethg++ <--> Eth10G <--> switch.ethg++;
        rsu5.ethg++ <--> Eth10G <--> switch.ethg++;
        rsu6.ethg++ <--> Eth10G <--> switch.ethg++;
        // Conexión del Switch al Router
        switch.ethg++ <--> Eth10G <--> router.ethg++;
        // Conexión del Router al Servidor
        router.ethg++ <--> Eth10G <--> server.ethg++;

}
