#!/bin/bash

# Enter Artifact/Binary Dir
echo "[ERS BUILD SYSTEM] - Entering Artifacts Directory"
cd ..
cd Binaries

# Detect Platform, Execute Program From That
echo "[ERS BUILD SYSTEM] - Detecting Platform"
MachineName="$(uname -s)"
case "${MachineName}" in
    Linux*)     Machine="Linux";;
    Darwin*)    Machine="Mac";;
    CYGWIN*)    Machine="Cygwin";;
    MINGW*)     Machine="MinGw";;
    *)          Machine="UNKNOWN:${MachineName}"
esac
echo "[ERS BUILD SYSTEM] - Detected Platform To Be '${Machine}'"


# Depending On Platform, Run
echo "[ERS BUILD SYSTEM] - Running Binary"
if [ ${Machine} == "Linux" ]
then
    ./BrainGenix-ERS
elif ${Machine} == "Mac"
then
    open BrainGenix-ERS.app
else
    echo "Unknown Platform, Cannot Run Executable"
fi

