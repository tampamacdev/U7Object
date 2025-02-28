#!/bin/bash

# Exit on any error
set -e

# Function to detect OS
detect_os() {
    if [[ "$OSTYPE" == "darwin"* ]]; then
        echo "macOS"
    elif [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" || "$OSTYPE" == "win32" ]]; then
        echo "Windows"
    elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
        echo "Linux"
    else
        echo "Unknown OS: $OSTYPE"
        exit 1
    fi
}

# Main setup function
setup_deps() {
    OS=$(detect_os)
    echo "Detected OS: $OS"

    if [ "$OS" == "macOS" ]; then
        # Check if Homebrew is installed, install if not
        if ! command -v brew >/dev/null 2>&1; then
            echo "Installing Homebrew..."
            /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
        else
            echo "Homebrew already installed."
        fi

        echo "Installing dependencies with Homebrew..."
        brew install cmake
        brew install glib
        brew install json-glib
        brew install openssl@3

        echo "Checking glib-2.0 flags (for reference)..."
        pkg-config --cflags glib-2.0
        pkg-config --libs glib-2.0

    elif [ "$OS" == "Windows" ]; then
        # Ensure Git Bash is running (OSTYPE should be msys)
        if [ "$OSTYPE" != "msys" ]; then
            echo "This script must run in Git Bash on Windows."
            exit 1
        fi

        # Check if vcpkg directory exists, clone if not
        VCPKG_DIR="C:/Dev/vcpkg"
        if [ ! -d "$VCPKG_DIR" ]; then
            echo "Cloning vcpkg to $VCPKG_DIR..."
            git clone https://github.com/microsoft/vcpkg.git "$VCPKG_DIR"
        else
            echo "vcpkg already cloned at $VCPKG_DIR."
        fi

        echo "Bootstrapping vcpkg..."
        cd "$VCPKG_DIR"
        ./bootstrap-vcpkg.bat

        echo "Installing dependencies with vcpkg..."
        ./vcpkg install glib:x64-windows
        ./vcpkg install json-glib:x64-windows
        ./vcpkg install openssl:x64-windows

        # Note: Add vcpkg to PATH manually if needed
        echo "To use vcpkg with CMake, add '-DCMAKE_TOOLCHAIN_FILE=$VCPKG_DIR/scripts/buildsystems/vcpkg.cmake' to your cmake command."

    elif [ "$OS" == "Linux" ]; then
        echo "Updating package lists..."
        sudo apt-get update

        echo "Installing dependencies with apt..."
        sudo apt-get install -y cmake
        sudo apt-get install -y libglib2.0-dev
        sudo apt-get install -y libjson-glib-dev
        sudo apt-get install -y libssl-dev
    fi

    echo "Dependency setup complete for $OS!"
}

# Run the setup
setup_deps