# Minimum Version Info #
cmake_minimum_required(VERSION 3.10)

# Set Project Name #
project(BrainGenix-ERS)
set(CMAKE_CXX_STANDARD 17)

# Add Library Dirs #
find_package(Vulkan REQUIRED FATAL_ERROR)

add_subdirectory(System/ExternalLibraries/yaml-cpp-yaml-cpp-0.6.3)
add_subdirectory(System/ExternalLibraries/glfw-3.3.4)




# Set Executible Output Dir #
set(SOURCE_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${SOURCE_ROOT_DIR}/System)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${SOURCE_ROOT_DIR}/System)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${SOURCE_ROOT_DIR}/System)


# Set Executible #
add_executable(ERS System/main.cpp)

target_link_libraries(ERS PUBLIC yaml-cpp)
target_link_libraries(ERS PUBLIC glfw)
#target_link_libraries(ERS ${Vulkan_LIBRARIES})

#target_include_directories(ERS PUBLIC ${Vulkan_INCLUDE_DIR})

