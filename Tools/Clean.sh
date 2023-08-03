#!/bin/bash

# Cleans the build directories
echo "[ERS BUILD SYSTEM] - Cleaning Build"

cd ..
echo "[ERS BUILD SYSTEM] - Removing Build Directory"
rm -rf Build/
echo "[ERS BUILD SYSTEM] - Cleaning CMake Cache"
rm -rf build/
echo "[ERS BUILD SYSTEM] - Deleting Artifacts"
rm -rf Binaries/

echo "[ERS BUILD SYSTEM] - Build Cleaned"
