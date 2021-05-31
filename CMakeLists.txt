# Minimum Version Info #
cmake_minimum_required(VERSION 3.10)

# Set Project Name #
project(BrainGenix-ERS)
set(CMAKE_CXX_STANDARD 14)


include(ExternalProject)

ExternalProject_Add(
	yaml_cpp_project
	SOURCE_DIR "${CMAKE_SOURCE_DIR}/third-party/yaml-cpp/"
	INSTALL_DIR "${CMAKE_BINARY_DIR}/prefix"
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

add_library(yaml-cpp UNKNOWN IMPORTED)
set_target_properties(gmock PROPERTIES
	IMPORTED_LOCATION ${PROJECT_BINARY_DIR}/prefix/lib/${CMAKE_STATIC_LIBRARY_PREFIX}yaml-cpp${CMAKE_STATIC_LIBRARY_SUFFIX}
)

include_directories(SYSTEM "${PROJECT_BINARY_DIR}/prefix/include")

add_dependencies(playground yaml_cpp_project) 

target_link_libraries(playground
   yaml-cpp
)



# Set Executible #
add_executable(ERS System/main.cpp)
target_link_libraries(yaml_cpp "/usr/local/lib")
