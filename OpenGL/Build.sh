#! /bin/bash

echo "Running Cmake"
cmake .

echo "Compiling..."
make -j 24

echo "Running BrainGenix-ERS"
cd Dist
./BrainGenix-ERS
