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
if [[ "$SCRIPT_PATH" != "${SCRIPT_DIR}/run_second_endpoint.sh" ]]; then
    echo "Error: The path of the running script does not match its expected location."
    exit 1
fi

echo $SCRIPT_PATH

./endpoint