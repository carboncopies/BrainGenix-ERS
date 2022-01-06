# Get Into Root Repo Dir
echo "Entering Root Repo Directory"
cd ..

echo "Checking If Build Directory Already Exists"
if [ -d "Build" ]
then 
    echo "Build Directory Already Exists, Skipping Generation"
else 
    # Create Build Dir
    echo "Creating Build Directory"
    mkdir -p Build

    # Enter Build Dir
    echo "Entering Build Directory"
    cd Build

    # Make Only BrainGenix-ERS
    echo "Configuring Build Files"
    cmake ..
fi

# Build Files
echo "Building, Please Wait. This may take some time"
echo "Detecting Number Of CPU Cores..."
NumCPUCores= nproc --all
echo "Detected $NumCPUCores Cores, Building"
cmake --build . --target BrainGenix-ERS -j $NumCPUCores


# Run Program
echo "Running Program"
cd ../Binaries
./BrainGenix-ERS
cd ..
