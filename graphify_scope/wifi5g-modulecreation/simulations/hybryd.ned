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

package wifi_5g.simulations;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.networklayer.ipv4.RoutingTableRecorder;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;
import inet.node.ethernet.Eth10G;
import inet.common.misc.ThruputMeteringChannel;
import inet.visualizer.common.IntegratedVisualizer;
import inet.environment.common.PhysicalEnvironment;
import inet.physicallayer.wireless.ieee80211.packetlevel.Ieee80211ScalarRadioMedium;
import inet.node.wireless.AccessPoint;
import inet.node.ethernet.EthernetSwitch;

import org.car2x.veins.visualizer.roads.RoadsCanvasVisualizer;
import org.car2x.veins.visualizer.roads.RoadsOsgVisualizer;
import org.car2x.veins.subprojects.veins_inet.VeinsInetManager;

import simu5g.world.radio.LteChannelControl;
import simu5g.common.carrierAggregation.CarrierAggregation;
import simu5g.common.binder.Binder;
import simu5g.nodes.Upf;
import simu5g.nodes.gNodeB;
import simu5g.nodes.NrCarCustom2;

network Hybryd
{
    parameters:
        double playgroundSizeX @unit(m);
        double playgroundSizeY @unit(m);
        double playgroundSizeZ @unit(m);
        bool useOsg = default(false);
        @display("bgb=20000,20000");

    types:
        channel Eth10G extends ThruputMeteringChannel
        {
            datarate = 10Gbps;
            delay = 0.1us;
        }

    submodules:
        // ====================================================================
        // 1. MÓDULOS GLOBALES Y DE ENTORNO (Comunes, Veins y 5G)
        // ====================================================================
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
        channelControl: LteChannelControl {
            @display("p=50,25;is=s");
        }
        binder: Binder {
            @display("p=150,25;is=s");
        }
        carrierAggregation: CarrierAggregation {
            @display("p=250,25;is=s");
        }

        // ====================================================================
        // 2. NÚCLEO DE LA RED (Core Network)
        // ====================================================================
        server: StandardHost {
            @display("p=5420,260;is=n;i=device/server");
        }
        router: Router {
            @display("p=3820,230;i=device/router");
        }
        switch: EthernetSwitch {
            @display("p=1450,210;i=device/switch");
        }
        upf: Upf {
            @display("p=4820,960");
        }

        // ====================================================================
        // 3. INFRAESTRUCTURA WI-FI (RSUs - Posiciones Intocables)
        // ====================================================================
        rsu1: AccessPoint {
            @display("i=device/accesspoint;p=2900,3010.70");
        }
        rsu2: AccessPoint {
            @display("i=device/accesspoint;p=3705.40,3283.02");
        }
        rsu3: AccessPoint {
            @display("i=device/accesspoint;p=3982,6149");
        }
        rsu4: AccessPoint {
            @display("i=device/accesspoint;p=4352,4764");
        }
        rsu5: AccessPoint {
            @display("i=device/accesspoint;p=4168,3047");
        }
        rsu6: AccessPoint {
            @display("i=device/accesspoint;p=4218.59,4124.64");
        }

        // ====================================================================
        // 4. INFRAESTRUCTURA 5G NR (gNodeBs - Posiciones Intocables)
        // ====================================================================
        gNodeB1: gNodeB {
            @display("p=2900,3000;is=vl");
        }
        gNodeB2: gNodeB {
            @display("p=2904,1747;is=vl");
        }
        gNodeB3: gNodeB {
            @display("p=4062,3335;is=vl");
        }
        gNodeB4: gNodeB {
            @display("p=4430,4580;is=vl");
        }
        gNodeB5: gNodeB {
            @display("p=2580,4337;is=vl");
        }
        gNodeB6: gNodeB {
            @display("p=4000,6050;is=vl");
        }
        gNodeB7: gNodeB {
            @display("p=2400,6370;is=vl");
        }
        gNodeB8: gNodeB {
            @display("p=1600,5230;is=vl");
        }

        // ====================================================================
        // 5. VEHÍCULOS (Declaración base)
        // ====================================================================
        car[0]: NrCarCustom2 {
            @display("p=430,2860;i=device/smallcar");
        }

    connections allowunconnected:
        // ====================================================================
        // A. CONEXIONES DEL ROUTER CENTRAL (ORDEN CRÍTICO PARA LAS IPs)
        // ====================================================================

        // 1. Router (eth0) <--> Switch (eth0) [Tráfico Wi-Fi]
        router.ethg++ <--> Eth10G <--> switch.ethg++;

        // 2. Router (eth1) <--> Server (eth0) [Enlace directo Servidor - Wi-Fi]
        router.ethg++ <--> Eth10G <--> server.ethg++;

        // 3. Router (eth2) <--> Server (eth1) [Enlace directo Servidor - 5G]
        router.ethg++ <--> Eth10G <--> server.ethg++;

        // 4. Router (ppp0) <--> UPF (filterGate) [Tráfico Celular Core]
        router.pppg++ <--> Eth10G <--> upf.filterGate;

        // ====================================================================
        // B. CONEXIONES DE INFRAESTRUCTURA WI-FI (Capa 2)
        // ====================================================================
        rsu1.ethg++ <--> Eth10G <--> switch.ethg++;
        rsu2.ethg++ <--> Eth10G <--> switch.ethg++;
        rsu3.ethg++ <--> Eth10G <--> switch.ethg++;
        rsu4.ethg++ <--> Eth10G <--> switch.ethg++;
        rsu5.ethg++ <--> Eth10G <--> switch.ethg++;
        rsu6.ethg++ <--> Eth10G <--> switch.ethg++;

        // ====================================================================
        // C. CONEXIONES DEL CORE 5G AL RADIO ACCESO (Backhaul)
        // ====================================================================
        upf.pppg++ <--> Eth10G <--> gNodeB1.ppp;
        upf.pppg++ <--> Eth10G <--> gNodeB2.ppp;
        upf.pppg++ <--> Eth10G <--> gNodeB3.ppp;
        upf.pppg++ <--> Eth10G <--> gNodeB4.ppp;
        upf.pppg++ <--> Eth10G <--> gNodeB5.ppp;
        upf.pppg++ <--> Eth10G <--> gNodeB6.ppp;
        upf.pppg++ <--> Eth10G <--> gNodeB7.ppp;
        upf.pppg++ <--> Eth10G <--> gNodeB8.ppp;

        // ====================================================================
        // D. CONEXIONES X2 ENTRE gNodeBs (Topología Escalera / Handover)
        // ====================================================================

        // 1. Columna Izquierda (Bajada Vertical)
        gNodeB2.x2++ <--> Eth10G <--> gNodeB1.x2++;
        gNodeB1.x2++ <--> Eth10G <--> gNodeB5.x2++;
        gNodeB5.x2++ <--> Eth10G <--> gNodeB8.x2++;

        // 2. Columna Derecha (Bajada Autopista)
        gNodeB3.x2++ <--> Eth10G <--> gNodeB4.x2++;
        gNodeB4.x2++ <--> Eth10G <--> gNodeB6.x2++;
        gNodeB6.x2++ <--> Eth10G <--> gNodeB7.x2++;

        // 3. Puentes Horizontales (Cruces para estabilidad de Handover)
        gNodeB2.x2++ <--> Eth10G <--> gNodeB3.x2++; // Puente Norte
        gNodeB4.x2++ <--> Eth10G <--> gNodeB5.x2++; // Puente Central
        gNodeB7.x2++ <--> Eth10G <--> gNodeB8.x2++; // Puente Sur
        gNodeB1.x2++ <--> Eth10G <--> gNodeB3.x2++; // Cierre extra
}
