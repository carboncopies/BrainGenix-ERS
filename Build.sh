#!bin/bash

# Create Build Dir #
mkdir Dist

# Make Config Data #
echo "Generating Build Files"
cmake CMakeLists.txt -B Dist/

# Compile #
echo "Compiling Binary"
cd Dist
make

# Done #
echo "Done"

