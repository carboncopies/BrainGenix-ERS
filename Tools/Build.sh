# Exit Tools Dir
echo "Exiting Tools Dir"
cd ..

# Create Build Dir
#echo "Creating Build Directory"
#mkdir -p Build

# Enter Build Dir
echo "Entering Build Directory"
cd Build

# Make Only BrainGenix-ERS
#echo "Running Cmake"
#cmake ..

# Build
echo "Building BrainGenix-ERS"
cmake --build . --target BrainGenix-ERS -- -j 24



# Run Program
echo "Running Program"
cd ../Binaries
./BrainGenix-ERS
cd ..
