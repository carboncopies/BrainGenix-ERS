#!/bin/bash

mkdir -p Source/Shaders/SPIR-V
mkdir -p Source/Shaders/SPIR-V/Vertex
mkdir -p Source/Shaders/SPIR-V/Fragment

./Build-Tools/shaderc/bin/glslc Source/Shaders/Source/Vertex/main.vert -o Source/Shaders/SPIR-V/Vertex/main.spv
./Build-Tools/shaderc/bin/glslc Source/Shaders/Source/Fragment/main.frag -o Source/Shaders/SPIR-V/Fragment/main.spv
