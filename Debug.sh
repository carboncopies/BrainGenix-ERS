mkdir -p Build
cd Build
cmake ..
make -j 24

cd ../Binaries
valgrind ./BrainGenix-ERS
cd ..
