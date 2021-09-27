# Install script for directory: /home/tliao/Documents/BrainGenix-ERS/third-party/bgfx/External

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bx/cmake_install.cmake")
  include("/home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bimg/cmake_install.cmake")
  include("/home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/bgfx/cmake_install.cmake")
  include("/home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/meshoptimizer/cmake_install.cmake")
  include("/home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/fcpp/cmake_install.cmake")
  include("/home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glsl-optimizer/cmake_install.cmake")
  include("/home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/glslang/cmake_install.cmake")
  include("/home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/spirv-headers/cmake_install.cmake")
  include("/home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/spirv-cross/cmake_install.cmake")
  include("/home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/spirv-tools/cmake_install.cmake")
  include("/home/tliao/Documents/BrainGenix-ERS/Build/third-party/bgfx/External/webgpu/cmake_install.cmake")

endif()

