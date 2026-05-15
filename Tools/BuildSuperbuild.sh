#!/bin/bash

set -euo pipefail


echo "[ERS SUPERBUILD HELPER] - Entering Root Repo Directory"
cd ..


BuildThreads="${1:-2}"
BuildType="${2:-Release}"

echo "[ERS SUPERBUILD HELPER] - Using ${BuildThreads} build threads"
echo "[ERS SUPERBUILD HELPER] - Configuring ${BuildType} superbuild"

cmake -S Superbuild -B Build/Superbuild -D CMAKE_BUILD_TYPE="${BuildType}"
cmake --build Build/Superbuild -j "${BuildThreads}" --target BrainGenixERSProject

echo "[ERS SUPERBUILD HELPER] - Finished Superbuild"
