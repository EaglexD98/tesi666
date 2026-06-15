package wifitelemetry.TelemetryUdpFinal;

import inet.applications.contract.IApp;

simple TelemetryReceiverUdpFinal like IApp
{
    parameters:
        @class(simu5g::TelemetryReceiverUdpFinal);
        int localPort = default(1000);
        @display("i=block/app");

        @signal[telemetryLatency](type=double);
        @signal[telemetryCo2](type=double);

        @statistic[telemetryLatency](title="Latencia de Red"; source="telemetryLatency"; record=vector,mean,max; unit=s);
        @statistic[telemetryCo2](title="Emisiones de CO2"; source="telemetryCo2"; record=vector,mean,max);

    gates:
        input socketIn @labels(UdpControlInfo/up);
        output socketOut @labels(UdpControlInfo/down);
}