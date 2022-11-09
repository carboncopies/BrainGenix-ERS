# Firstly, Create And Enter The Build Directory
echo "[ERS BUILD HELPER] - Entering Root Repository Directory"
cd ..


# Configure Build Type
BuildType="Debug"
if (($# >= 2))
then
    BuildType=$2
    echo "[ERS BUILD HELPER] - Building in user-specified $BuildType mode."
else
    echo "[ERS BUILD HELPER] - Did not get specified build configuration, building in $BuildType mode."
fi

# Delete Binary If Exists
echo "[ERS BUILD HELPER] - Checking If Binary Exists"
if [ -f "Binaries/BrainGenix-ERS" ]
then
    echo "[ERS BUILD HELPER] - Removing Last Executable"
    rm Binaries/BrainGenix-ERS
else
    echo "[ERS BUILD HELPER] - No Binaries To Clean"
fi




# Check If Build Folder And Tools Need To Be Downloaded
if [ -d "Build" ]
then

    # Skip Creation, Just Enter Build Directory
    echo "[ERS BUILD HELPER] - Build Directory Already Exists, Skipping Generation"
    cd Build

    # Now, Set The Path For The CMake Executable
    echo "[ERS BUILD HELPER] - Setting CMake Executable Environment Variable"
    CurrentRepoPath=$(pwd)
    echo "[ERS BUILD HELPER] - Detected The Current Build Directory To Be '$CurrentRepoPath'"
    CMakeBinaryPath="$CurrentRepoPath/CMakeBinaries/CMake.app/Contents/bin"
    echo "[ERS BUILD HELPER] - Setting CMake Path To '$CMakeBinaryPath'"
    export PATH=$PATH:"$CMakeBinaryPath"

else

    # Create And Enter Build Directory
    echo "[ERS BUILD HELPER} - Build Directory Does Not Exist, Creating"
    mkdir Build/
    cd Build/

    # Now, Get the CMake Binaries Tar File From Rel Page
    echo "[Build Helper] - Downloading CMake Binaries From Release Page"
    curl --location --remote-header-name --remote-name https://github.com/Kitware/CMake/releases/download/v3.24.3/cmake-3.24.3-macos10.10-universal.tar.gz

    # Extract The Binaries Tar, Rename
    echo "[ERS BUILD HELPER] - Done, Extracting Binaries From Tar File"
    tar -xzf cmake-3.24.3-macos10.10-universal.tar.gz
    mv cmake-3.24.3-macos10.10-universal CMakeBinaries

    # Now, Set The Path For The CMake Executable
    echo "[ERS BUILD HELPER] - Setting CMake Executable Environment Variable"
    CurrentRepoPath=$(pwd)
    echo "[ERS BUILD HELPER] - Detected The Current Build Directory To Be '$CurrentRepoPath'"
    CMakeBinaryPath="$CurrentRepoPath/CMakeBinaries/CMake.app/Contents/bin"
    echo "[ERS BUILD HELPER] - Setting CMake Path To '$CMakeBinaryPath'"
    export PATH=$PATH:"$CMakeBinaryPath"

    # Make Only BrainGenix-ERS
    echo "[ERS BUILD HELPER] - Configuring Build Files"
    cmake .. -D CMAKE_BUILD_TYPE=$BuildType

    # Set Config Var
    echo "[ERS BUILD HELPER] - Saving Build Type Configuration Of $BuildType"
    echo "$BuildType" > "BuildType"

fi




# Build Files
echo "[ERS BUILD HELPER] - Building, Please Wait. This may take some time"
cmake --build . --target BrainGenix-ERS --parallel $1


# Run Program
cd ../Binaries
echo "[ERS BUILD HELPER] - Checking If Binary Exists"
# if [ -f "BrainGenix-ERS.app" ]
# then
echo "[ERS BUILD HELPER] - Running Program"
open BrainGenix-ERS.app
# else
#     echo "[ERS BUILD HELPER] - Build Failed! Exiting"
# fi
cd ..
