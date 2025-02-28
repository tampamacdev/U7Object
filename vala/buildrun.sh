#!/bin/bash
set -e

# Check for --reconfigure argument
if [ "$1" = "--reconfigure" ]; then

    if [ -f "header_gen/u7_bridge.h" ]; then
        rm "header_gen/u7_bridge.h"
    fi

    cp u7_bridge.h header_gen/u7_bridge.h

    echo "Reconfigure requested, deleting build directory..."

    if [ -d "build" ]; then
        rm -rf build
    fi


    if [ -f "u7_api.h" ]; then
        rm u7_api.h
    fi

    cd header_gen

    if [ -d "build" ]; then 
        rm -fr build
    fi 

    meson setup build
    cd build
    ninja

    cd ../..

    echo "finished building u7_api.h header"
    echo $PWD

    cp header_gen/build/u7_api.h .
    ls -las header_gen/build/u7_api.h 
    ls -las u7_api.h 

fi

if [ ! -f "u7_api.h" ]; then 
    echo "missing u7_api.h run buildrun.sh again with --reconfigure options"

    exit 1
fi

if [ ! -d "build" ]; then
    MESON="meson"
    echo "Default Meson: $MESON ($($MESON --version))"

    echo "Build directory not found, running meson setup..."
    if [ "$(uname -s)" = "Linux" ] || [ "$(uname -s)" = "Darwin" ]; then
        if [ -x "$HOME/.local/bin/meson" ]; then
            MESON="$HOME/.local/bin/meson"
            echo "Using pip3-installed Meson: $MESON ($($MESON --version))"
        fi
    fi
    $MESON setup build -Dtrack_object_alloc=false -Dinclude_c_bridge_code=true || { echo "Meson setup failed"; exit 1; }
fi




cd build

meson configure -Dinclude_c_bridge_code=true

value=$(meson configure < /dev/null | grep "include_c_bridge_code" | awk '{print $4}')
echo "include_c_bridge_code is set to: <$value>"

ninja
./websocket_endpoint