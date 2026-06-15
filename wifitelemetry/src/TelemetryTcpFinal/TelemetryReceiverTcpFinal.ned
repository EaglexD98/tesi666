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

package wifitelemetry.TelemetryTcpFinal;
import inet.applications.contract.IApp;
//
// TODO auto-generated module
//
simple TelemetryReceiverTcpFinal like IApp
{
    parameters:
        // C++ está en el namespace simu5g, esto une el NED con el código compilado
        @class(simu5g::TelemetryReceiverTcpFinal);
        @display("i=block/sink");

        int localPort = default(1000);

        @signal[telemetryLatency](type=double);
        @signal[telemetryCo2](type=double);

        @statistic[telemetryLatency](title="Latencia de Red"; source="telemetryLatency"; record=vector,mean,max; unit=s);
        @statistic[telemetryCo2](title="Emisiones de CO2"; source="telemetryCo2"; record=vector,mean,max);

    gates:
        input socketIn @labels(TcpCommand/up);
        output socketOut @labels(TcpCommand/down);
}
