# Cleans the build directories while keeping existing assets
echo "Cleaning Build (Keeping Assets)"

cd ..
rm -rf Build/
rm -rf build/
cd Binaries
rm -rf !(Assets/)

echo "Build Cleaned"
