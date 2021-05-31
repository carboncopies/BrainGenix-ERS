# Minimum Version Info #
cmake_minimum_required(VERSION 3.10)

# Set Project Name #
project(BrainGenix-ERS)
set(CMAKE_CXX_STANDARD 14)


# Include YAML-CPP Library #
target_include_directories(yaml-cpp PUBLIC System/ExternalLibraries/yaml-cpp-yaml-cpp-0.6.3/include/yaml-cpp)


target_link_libraries(main.cpp PUBLIC yaml-cpp)




# Set Executible #
add_executable(ERS System/main.cpp)
