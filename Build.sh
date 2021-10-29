mkdir -p Build
cd Build
cmake --target BrainGenix-ERS ..
make -j 24

cd ../Binaries
./BrainGenix-ERS
cd ..
