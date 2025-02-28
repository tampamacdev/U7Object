#!/bin/bash

# Check if C_CORE_PATH is set
if [ -z "$C_CORE_PATH" ]; then
    echo "Error: C_CORE_PATH environment variable is not set."
    echo "Please set it with: export C_CORE_PATH=/path/to/c-core"
    exit 1
fi

# Verify C_CORE_PATH exists
if [ ! -d "$C_CORE_PATH" ]; then
    echo "Error: Directory $C_CORE_PATH does not exist."
    exit 1
fi

# Change to C_CORE_PATH
cd "$C_CORE_PATH" || {
    echo "Error: Could not change to $C_CORE_PATH"
    exit 1
}

# Create include/pubnub directory
mkdir -p include/pubnub || {
    echo "Error: Could not create include/pubnub directory"
    exit 1
}

# Copy core headers
if [ -d "core" ]; then
    cp core/*.h include/pubnub/ 2>/dev/null || {
        echo "Warning: No headers found in core/, or copy failed"
    }
else
    echo "Warning: core/ directory not found"
fi

# Copy lib headers (optional, may not exist)
if [ -d "lib" ]; then
    cp lib/*.h include/pubnub/ 2>/dev/null || {
        echo "Warning: No headers found in lib/, or copy failed"
    }
else
    echo "Warning: lib/ directory not found"
fi

# Detect OS and copy platform-specific headers
OS_TYPE=$(uname -s)
case "$OS_TYPE" in
    Linux|Darwin) # POSIX (Linux, macOS)
        echo "Detected POSIX OS ($OS_TYPE)"
        if [ -d "posix" ]; then
            cp posix/*.h include/pubnub/ 2>/dev/null || {
                echo "Warning: No headers found in posix/, or copy failed"
            }
            # Check for pubnub_config.h in posix/
            if [ -f "posix/pubnub_config.h" ]; then
                cp posix/pubnub_config.h include/pubnub/
                echo "Copied pubnub_config.h from posix/"
            elif [ -f "core/pubnub_generate_config.h" ]; then
                cp core/pubnub_generate_config.h include/pubnub/pubnub_config.h
                echo "Generated pubnub_config.h from core/pubnub_generate_config.h"
            else
                echo "Warning: pubnub_config.h not found in posix/ or core/"
            fi
        else
            echo "Warning: posix/ directory not found"
        fi
        ;;
    MINGW*|MSYS*|CYGWIN*) # Windows
        echo "Detected Windows OS ($OS_TYPE)"
        if [ -d "windows" ]; then
            cp windows/*.h include/pubnub/ 2>/dev/null || {
                echo "Warning: No headers found in windows/, or copy failed"
            }
            # Check for pubnub_config.h in windows/
            if [ -f "windows/pubnub_config.h" ]; then
                cp windows/pubnub_config.h include/pubnub/
                echo "Copied pubnub_config.h from windows/"
            elif [ -f "core/pubnub_generate_config.h" ]; then
                cp core/pubnub_generate_config.h include/pubnub/pubnub_config.h
                echo "Generated pubnub_config.h from core/pubnub_generate_config.h"
            else
                echo "Warning: pubnub_config.h not found in windows/ or core/"
            fi
        else
            echo "Warning: windows/ directory not found"
        fi
        ;;
    *)
        echo "Error: Unsupported OS type: $OS_TYPE"
        echo "This script supports Linux, macOS (POSIX), and Windows (MINGW/MSYS/CYGWIN)"
        exit 1
        ;;
esac

echo "PubNub include folder generated at $C_CORE_PATH/include/pubnub/"
ls -l "$C_CORE_PATH/include/pubnub/"