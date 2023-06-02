FROM debian:10
ARG DEBIAN_FRONTEND=noninteractive
ENV TZ=Etc/UTC
RUN apt update && apt install git wget cmake ninja-build g++ python3 python3-pip binutils-dev libunwind-dev libdwarf-dev libdw-dev libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libssl-dev libusb-1.0-0-dev libeigen3-dev libudev-dev libgl1-mesa-dev -y
