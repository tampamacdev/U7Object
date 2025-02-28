#!/bin/bash

# Full path to the executing script
SCRIPT_PATH=$(readlink -f "$0")
# Directory where the script resides
SCRIPT_DIR=$(dirname "$SCRIPT_PATH")

# Check if the current directory is the build directory
EXPECTED_BUILD_DIR="${SCRIPT_DIR}/build"

if [[ "$PWD" != "$EXPECTED_BUILD_DIR" ]]; then
    echo "Error: You must run this script from the build directory."
    exit 1
fi

# Ensure that $0 matches the expected script path in the parent directory of build
if [[ "$SCRIPT_PATH" != "${SCRIPT_DIR}/buildrun.sh" ]]; then
    echo "Error: The path of the running script does not match its expected location."
    exit 1
fi

BUILD_ENV_DIR=".websocketendpoint"

echo BUILD_ENV_DIR $BUILD_ENV_DIR


if [ ! -d "$HOME/$BUILD_ENV_DIR" ]; then
    echo "making dev environment settings directory at ~/$BUILD_ENV_DIR"
    mkdir $HOME/$BUILD_ENV_DIR
fi

if [ ! -f "$HOME/$BUILD_ENV_DIR/websocketendpoint_config.sh" ]; then

    echo "ATTENTION!!"
    echo "copying template websocketendpoint_config.sh file to ~/$BUILD_ENV_DIR/websocketendpoint_config.sh, default endpoint ports are being assigned with this file. Press any key to continue."
    
    read name

    cp ../websocketendpoint_config.sh $HOME/$BUILD_ENV_DIR/websocketendpoint_config.sh
fi

source $HOME/$BUILD_ENV_DIR/websocketendpoint_config.sh
cat $HOME/$BUILD_ENV_DIR/websocketendpoint_config.sh
# Run make and check the status
if make; then
    echo "Build succeeded."

    echo PWD $PWD

    rm endpoint2
    cp endpoint endpoint2

    if [[ -f endpoint ]]; then
        echo "Running the executable."
        ./endpoint -prefix endpoint1
    else
        echo "Error: Executable not found."
    fi
else
    echo "Build failed."
    exit 1
fi