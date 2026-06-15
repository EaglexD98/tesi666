package wifitelemetry.TelemetryUdpFinal;

import inet.applications.contract.IApp;

simple TelemetrySenderUdpFinal like IApp
{
    parameters:
        @class(simu5g::TelemetrySenderUdpFinal);
        int localPort = default(-1);
        int connectPort = default(1000);
        string connectAddress;

        volatile double startTime @unit(s) = default(5s);
        volatile double sampleInterval @unit(s) = default(1s);
        volatile double burstInterval @unit(s) = default(5s);
        volatile double helloInterval @unit(s) = default(0.5s);
        volatile double conditionCheckInterval @unit(s) = default(0.1s);
        volatile double reconnectInterval @unit(s) = default(1s);

        string routeStops = default("");
        string validStops = default("");

        @display("i=block/app");
    gates:
        input socketIn @labels(UdpControlInfo/up);
        output socketOut @labels(UdpControlInfo/down);
}