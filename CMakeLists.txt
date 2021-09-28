# Set CMAKE Version, Define Project
cmake_minimum_required (VERSION 3.16.3)
project ("BrainGenix-ERS")


# Set Dirs
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Third-Party")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")


# Link BGFX

add_subdirectory("third-party/bgfx.cmake")


add_executable("test" "src/Main.cpp")

target_link_libraries("test",
	bgfx
	bimg
	bx
)

