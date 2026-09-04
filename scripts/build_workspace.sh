#!/usr/bin/env bash
set -euo pipefail

mode=${1:-release}
[[ "$mode" == release || "$mode" == debug ]] || {
    echo "Usage: $0 [release|debug]" >&2
    exit 2
}

root=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
jobs=${BUILD_JOBS:-$(nproc)}

export INET_ROOT="$root/inet"
export PATH="$root/inet/bin:$root/veins/bin:$root/veins_inet/bin:$root/simu5G/bin:$PATH"

command -v opp_makemake >/dev/null || {
    echo "ERROR: activate OMNeT++ 6.2.0 first: source ~/omnetpp-6.2.0/setenv" >&2
    exit 1
}
command -v sumo >/dev/null || {
    echo "ERROR: SUMO is not available in PATH." >&2
    exit 1
}

build_make_project() {
    local project=$1
    echo "==> Building $project ($mode, jobs=$jobs)"
    cd "$root/$project"
    make makefiles
    make -j "$jobs" MODE="$mode"
}

build_make_project inet

echo "==> Configuring and building Veins"
cd "$root/veins"
./configure
make -j "$jobs" MODE="$mode"

echo "==> Configuring and building Veins_INET"
cd "$root/veins_inet"
./configure --with-veins="$root/veins" --with-inet="$root/inet"
make -j "$jobs" MODE="$mode"

build_make_project simu5G
echo "==> Building wifi5g-modulecreation ($mode, jobs=$jobs)"
cd "$root/wifi5g-modulecreation/src"
opp_makemake -f --deep \
    -KINET_PROJ=../../inet \
    -KSIMU5G_PROJ=../../simu5G \
    -KVEINS_PROJ=../../veins \
    -KVEINS_INET_PROJ=../../veins_inet \
    -DINET_IMPORT -DVEINS_IMPORT \
    '-I$(INET_PROJ)/src' '-I$(SIMU5G_PROJ)/src' \
    '-I$(VEINS_PROJ)/src' -I. '-I$(VEINS_INET_PROJ)/src' \
    '-L$(INET_PROJ)/src' '-L$(SIMU5G_PROJ)/src' \
    '-L$(VEINS_PROJ)/src' '-lINET$(D)' '-lsimu5g$(D)' '-lveins$(D)'
make -j "$jobs" MODE="$mode"

echo "Workspace build completed successfully."
