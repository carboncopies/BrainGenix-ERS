# Get Into Root Repo Dir
echo "Entering Root Repo Directory"
cd ..

echo "Checking If Binary Exists"
if [ -f "Binaries/BrainGenix-ERS"]
then
    echo "Removing Last Executable"
    rm Binaries/BrainGenix-ERS
else
    echo "No Binaries To Clean"
fi


echo "Checking If Build Directory Already Exists"
if [ -d "Build/CMakeFiles" ]
then 
    echo "Build Directory Already Exists, Skipping Generation"
    cd Build
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
cmake --build . --target BrainGenix-ERS -j


# Run Program
echo "Running Program"
cd ../Binaries
./BrainGenix-ERS
cd ..
