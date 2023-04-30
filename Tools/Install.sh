#!/bin/bash

# Install Compiler Tools
sudo apt install git wget cmake ninja-build g++ python3 python3-pip -y

# Backward Deps
sudo apt install binutils-dev libunwind-dev libdwarf-dev libdw-dev -y

# Install GLFW Deps
sudo apt install libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev -y