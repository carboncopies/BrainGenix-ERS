# Install Compiler Tools
sudo apt install git wget cmake ninja-build g++ python3 python3-pip -y

# Backward Deps
sudo apt install binutils-dev libunwind-dev libdwarf-dev libdw-dev -y

# Install GLFW Deps
sudo apt install libx11-dev libxrandr-dev ibxinerama-dev libxcursor-dev libxi-dev -y

# Install MySQL Connector Deps
sudo apt install libssl-dev -y

# Install Monado Deps
pip3 install numpy
sudo apt install libusb-1.0-0-dev glslang-dev glslang-tools libeigen3-dev libudev-dev libgl1-mesa-dev libusb-1.0 -y
#sudo apt install glslang-dev glslang-tools -y