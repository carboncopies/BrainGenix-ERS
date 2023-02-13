# Set CMAKE Version, Define Project
cmake_minimum_required (VERSION 3.2)





# Set Non-User Changable Configuration Data (Used during build process )
option(USE_SUPERBUILD "Whether or not a superbuild should be invoked" ON) # You probably don't want to change this one - used internally


# Set Dirs
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")
set(BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Binaries")



# Superbuild Configuration
if (USE_SUPERBUILD)
  message("Performing Initial Superbuild To Create Third-Party Libs")
  
  project (SUPERBUILD NONE)

  # Add Superbuild Runner
  include(SuperbuildMain.cmake)
  return()
else()
  project(
    "BGImageTest"
    VERSION "0.0.1"
    LANGUAGES CXX
    )

  message("Performing Second Pass Run To Build Project")
endif()





add_subdirectory(Source)