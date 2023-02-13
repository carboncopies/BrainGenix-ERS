# Set CMAKE Version, Define Project
cmake_minimum_required (VERSION 3.1...3.21)


# Set Configuration Options
option(ENABLE_BACKWARD "Build ERS With Backward to provide some stack trace information or not" ON)


# Set Non-User Changable Configuration Data (Used during build process )
option (USE_SUPERBUILD "Whether or not a superbuild should be invoked" ON) # You probably don't want to change this one - used internally


# Set Dirs
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Third-Party")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")
set(BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Binaries")
set(CMAKE_UTIL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMake/Utils")
set(CMAKE_BUILD_UTILS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMake/BuildUtils")
set(CMAKE_FIND_UTILS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMake/FindUtils")
set(CMAKE_SCRIPTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMake/Scripts")
set(CMAKE_UTILS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
set(CMAKE_ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/EditorAssets")
set(PROJECT_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_CXX_VISIBILITY_PRESET hidden)



# Superbuild Configuration
if (USE_SUPERBUILD)

  project (SUPERBUILD NONE)

  # Add Superbuild Runner
  include(${CMAKE_UTILS_DIR}/SuperBuildMaster.cmake)
  return()
else()
  include(${CMAKE_UTILS_DIR}/SuperBuilds/ERS.cmake)
endif()