# Minimum Version Info #
cmake_minimum_required(VERSION 3.10)

# Set Project Name #
project(BrainGenix-ERS)

# Set Build Dir #
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY Dist/build)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY Dist/build)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY Dist/bin)

# Include Binary Directory #
include_directories(ERS)

# Set Executible #
add_executable(ERS System/main.cpp)
