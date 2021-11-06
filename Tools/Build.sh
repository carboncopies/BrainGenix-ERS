# Create Build Dir
mkdir -p Build

# Enter Build Dir
cd ../Build

# Make Only BrainGenix-ERS
cmake ..
cmake --build . --target BrainGenix-ERS -- -j 24

# Run Program
cd ../Binaries
./BrainGenix-ERS
cd ..
