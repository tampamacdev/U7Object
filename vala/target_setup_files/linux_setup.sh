#!/bin/bash
# install_vala_ubuntu.sh
# Installs Vala, Meson, Ninja, and Subversion on Ubuntu, similar to the macOS brew script.

# Update package list
sudo apt update

function apt_install() {

    separator="////////////////////////////////////////////////////////////"
    printf "%s\n%s\n       sudo apt install -y %s\n%s\n%s\n" $separator $separator $1 $separator $separator 
    sudo apt install -y $1

}

function echo_version() {
    local version_output=$($1 --version)  # Capture output in a variable
    echo "${1} --version: $version_output"
}

function echo_lib_version() {
    local version_output=$(dpkg-query -f '${Version}\n' -W "$1" 2>/dev/null || echo "not installed")
    echo "library version for ${1}: $version_output"

}


# Install Subversion (svn)
apt_install "subversion"

# Install Vala (includes valac and core dependencies like glib)
apt_install "valac"

# Install Meson and Ninja (build tools)
apt_install "meson ninja-build"

# Optional: Ensure a C compiler is installed (usually present, but just in case)
apt_install "python3-pip"

echo "pip3 install --user --upgrade meson" 
pip3 install --user --upgrade meson

apt_install "libgee-0.8-dev"

# Verify installations
echo "Installed versions:"


echo_version "valac"
echo_version "meson"
echo_version "ninja"
echo_version "svn"
echo_version "libgee"

echo_lib_version "libgee-0.8-dev"