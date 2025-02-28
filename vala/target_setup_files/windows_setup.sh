#!/bin/bash
# install_vala_windows.sh
# Installs Vala, Meson, Ninja, and dependencies for a Vala project on Windows via MSYS2 MinGW64.

echo "Starting MSYS2 Vala setup for Windows..."

# Update MSYS2 package database and core system
pacman -Syu --noconfirm

# Install core development tools
pacman -S --noconfirm mingw-w64-x86_64-gcc       # C compiler (GCC)
pacman -S --noconfirm mingw-w64-x86_64-pkg-config # For dependency resolution
pacman -S --noconfirm mingw-w64-x86_64-make      # Make (optional, for some builds)
# Install Vala compiler
pacman -S --noconfirm mingw-w64-x86_64-vala      # valac

# Install GLib and GObject (required by your meson.build)
pacman -S --noconfirm mingw-w64-x86_64-glib2     # GLib and GObject
pacman -S --noconfirm mingw-w64-x86_64-json-glib-1.0
pacman -S --noconfirm mingw-w64-x86_64-libgee

# Install Meson and Ninja (build system)
pacman -S --noconfirm mingw-w64-x86_64-meson
pacman -S --noconfirm mingw-w64-x86_64-ninja
pacman -S --noconfirm mingw-w64-x86_64-cmake
# Install vi
pacman -S --noconfirm vim

# Install Subversion (optional, matching your Ubuntu/macOS scripts)
# pacman -S --noconfirm mingw-w64-x86_64-subversion

# Verify installations
echo "Installed versions:"
valac --version || echo "valac not found"
meson --version || echo "meson not found"
ninja --version || echo "ninja not found"
svn --version || echo "svn not found"
pkg-config --modversion glib-2.0 || echo "glib-2.0 not found"
pkg-config --modversion gobject-2.0 || echo "gobject-2.0 not found"
pkg-config --modversion json-glib-1.0 || echo "json-glib-1.0 not found"

echo "Setup complete! Use the MinGW64 shell (mingw64.exe) to build your project."

