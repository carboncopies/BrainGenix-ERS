# Set CMAKE Version, Define Project
cmake_minimum_required (VERSION 3.1...3.21)

option(BUILD_IOSYSTEM_TESTS "Enable or disable building tests for the project" ON)

# Create project
project(
    "IOSystem"
    VERSION "0.0.1"
    LANGUAGES CXX
)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



# Include Util CMake Scripts
include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/Utils/ColorizeMessages.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/Utils/SetBinaryDir.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/Utils/DisableTargetWarnings.cmake)

# Add IOSystem Library Target
set(LIBRARY_SOURCE_FILES 
  ${CMAKE_CURRENT_SOURCE_DIR}/Source/IOSystem.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/Source/IOSystem.h
)
add_library(${PROJECT_NAME} ${LIBRARY_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Source)