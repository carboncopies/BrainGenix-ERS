# Cleans the build directories
echo "[BG BUILD SYSTEM] - Cleaning Build"

cd ..
echo "[BG BUILD SYSTEM] - Removing Build Directory"
rm -rf Build/
echo "[BG BUILD SYSTEM] - Cleaning CMake Cache"
rm -rf build/
echo "[BG BUILD SYSTEM] - Deleting Artifacts"
rm -rf Binaries/

echo "[BG BUILD SYSTEM] - Build Cleaned"
