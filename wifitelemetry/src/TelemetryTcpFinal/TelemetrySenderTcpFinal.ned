// Reemplaza TODO el contenido de tu TelemetrySenderTcpFinal.ned con esto:
package wifitelemetry.TelemetryTcpFinal;

import inet.applications.contract.IApp;

simple TelemetrySenderTcpFinal like IApp
{
    parameters:
        // C++ está en el namespace simu5g
        @class(simu5g::TelemetrySenderTcpFinal);
        @display("i=block/source");

        int localPort = default(-1);
        string connectAddress;
        int connectPort = default(1000);

        volatile double startTime @unit(s) = default(1s);
        volatile double sampleInterval @unit(s) = default(0.1s);
        volatile double batchInterval @unit(s) = default(1s);
        volatile double helloInterval @unit(s) = default(0.5s);
        volatile double conditionCheckInterval @unit(s) = default(0.1s);
        volatile double reconnectInterval @unit(s) = default(1s);

        string routeStops = default("");
        string validStops = default(""); // Usamos validStops de la nueva lógica

    gates:
        input socketIn @labels(TcpCommand/up);
        output socketOut @labels(TcpCommand/down);
}