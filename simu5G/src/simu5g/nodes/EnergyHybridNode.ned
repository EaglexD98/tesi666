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

package simu5g.nodes;

import simu5g.nodes.NrCarCustom2;
import simu5g.NrEventEnergyConsumer.NrEventEnergyConsumer;
import inet.power.storage.SimpleCcBattery;
import inet.power.storage.WifiBattery;
import inet.common.lifecycle.NodeStatus;

//
// Energy-enabled hybrid vehicle node.
//
// Inherits BOTH wireless interfaces from NrCarCustom2 (5G cellularNic + INET
// wlan[*]) and adds two independent batteries plus the 5G event-based consumer:
//   * energyStorage5g  + energyConsumer5g : 5G energy (consumer records totals)
//   * energyStorageWifi (WifiBattery)     : WiFi energy storage; the WiFi radio
//     consumer is attached at wlan[*].radio.energyConsumer via omnetpp.ini.
//
// The working hybrid communication logic is unchanged; energy modules are
// purely additive.
//
module EnergyHybridNode extends NrCarCustom2
{
    @display("bgb=1274,657");
    submodules:
        // Node lifecycle status, required by the Cc batteries to operate.
        status: NodeStatus {
            @display("p=126,98;i=block/control");
        }

        // 5G battery (plain; the 5G consumer records its own energy scalars).
        energyStorage5g: SimpleCcBattery {
            @display("p=1165,257;i=misc/battery");
        }

        // 5G event-based consumer (scoped to cellularNic via omnetpp.ini).
        energyConsumer5g: NrEventEnergyConsumer {
            @display("p=1165,58;i=block/plug");
        }

        // WiFi battery (records consumption scalars in finish()); the state-based
        // radio consumer that drains it lives inside wlan[*].radio.energyConsumer.
        energyStorageWifi: WifiBattery {
            @display("p=1166,147;i=misc/battery");
        }
}
