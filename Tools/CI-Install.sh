# Apt Update
apt update

# Install Compiler Tools
apt install git wget cmake ninja-build g++ python3 python3-pip -y

# Backward Deps
apt install binutils-dev libunwind-dev libdwarf-dev libdw-dev -y

# Install GLFW Deps
apt install libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev -y

# Install MySQL Connector Deps
apt install libssl-dev -y

# Install Monado Deps
pip3 install numpy
apt install libusb-1.0-0-dev glslang-dev glslang-tools libeigen3-dev libudev-dev libgl1-mesa-dev -y

