#!/bin/bash


# Detect if running as root
APT_COMMAND_PREFIX=""
echo "Detecting If Script Running As root"
if [ "$EUID" -ne 0 ]; then
    echo "Detected Install Script Is Not Running As Root, Adding 'sudo' Prefix To Commands"
    APT_COMMAND_PREFIX="sudo"
else
    echo "Command Running As Root, Running Commands Without 'sudo'"
fi


# Setup, update package registry
echo "Setting Up Packages Needed For Compilation"
$APT_COMMAND_PREFIX apt update || exit 1



# Install Compiler Tools
COMPILER_DEPS="git wget cmake g++"

# vcpkg Dependencies
VCPKG_DEPS="curl zip unzip tar pkg-config autoconf flex bison"

# glfw3 Deps
GLFW_DEPS="libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev"

# GLUT Deps
GLUT_DEPS="libxi-dev libgl1-mesa-dev libglu1-mesa-dev mesa-common-dev libxrandr-dev libxxf86vm-dev"


# Install Everything
INSTALL_COMMAND="$APT_COMMAND_PREFIX apt install $VCPKG_DEPS $COMPILER_DEPS $GLFW_DEPS $GLUT_DEPS -y"
echo "Running Install Command: $INSTALL_COMMAND"
$INSTALL_COMMAND || exit 1

# Update Submodules
echo "Updating Submodules"
git submodule update --init

# Bootstrap vcpkg
echo "Setting Up vcpkg"
./../ThirdParty/vcpkg/bootstrap-vcpkg.sh
echo "Done, you can now run Build.sh"
