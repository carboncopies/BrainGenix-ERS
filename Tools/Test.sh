
cd ..
mkdir Build
cd Build

# Configure the build
cmake .. -G Ninja -D CMAKE_BUILD_TYPE=RelWithDebInfo

# Actually build the binaries
cmake --build . -j 128 --target BrainGenix-ERS --verbose
