#!/bin/bash

# Determine Script Location
SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR" || exit 1

# Configure Package Settings
PACKAGE_GENERATORS=("TGZ" "ZIP")
if [ -n "$1" ]
then
    PACKAGE_GENERATORS=("$1")
fi

BUILD_TYPE="Release"
if [ -n "$2" ]
then
    BUILD_TYPE="$2"
fi

THREAD_COUNT="2"
if [ -n "$3" ]
then
    THREAD_COUNT="$3"
fi

# Build CPack Prerequisites
echo "[ERS PACKAGE HELPER] - Building Project In ${BUILD_TYPE} Mode"
bash Build.sh "$THREAD_COUNT" "$BUILD_TYPE" || exit 1

# Generate Packages
echo "[ERS PACKAGE HELPER] - Entering Build Directory"
cd ../Build || exit 1
mkdir -p Packages || exit 1

for PACKAGE_GENERATOR in "${PACKAGE_GENERATORS[@]}"
do
    echo "[ERS PACKAGE HELPER] - Generating ${PACKAGE_GENERATOR} Package"
    cpack -G "$PACKAGE_GENERATOR" -B Packages || exit 1
done

echo "[ERS PACKAGE HELPER] - Packages Written To Build/Packages"
