# Modified Framework Files

This folder contains a reduced Graphify scope for the OMNeT++ project.

It includes:
- Custom project files from src/, simulations/, and veins_inet/.
- Only modified files detected in INET and Simu5G.
- No full external framework copy.

## Modified Simu5G files
- simu5G/.settings/language.settings.xml
- simu5G/simulations/lte/cars/Highway.ned
- simu5G/simulations/nr/cars/Highway.ned
- simu5G/src/simu5g/nodes/LteUe.ned
- simu5G/src/simu5g/nodes/NrCarCustom2.ned
- simu5G/src/simu5g/nodes/NrCarCustom.ned
- simu5G/src/simu5g/nodes/NrCarCustomresp.ned

## Modified INET files
- inet/.settings/language.settings.xml
- inet/src/inet/networklayer/configurator/ipv4/HostAutoConfigurator.cc
- inet/src/inet/networklayer/configurator/ipv4/HostAutoConfigurator.h
- inet/src/inet/networklayer/configurator/ipv4/MyHostAutoConfigurator.cc
- inet/src/inet/networklayer/configurator/ipv4/MyHostAutoConfigurator.h
- inet/src/inet/networklayer/configurator/ipv4/MyHostAutoConfigurator.ned
