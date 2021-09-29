# Set CMAKE Version, Define Project
cmake_minimum_required (VERSION 3.16.3)
project ("BrainGenix-ERS")

# Set Dirs
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Third-Party")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")




# Link BGFX
set(BGFX_CMAKE_DIR "${LIB_DIR}/bgfx.cmake")
add_subdirectory("${BGFX_CMAKE_DIR}")

# Link GLFW
set(GLFW_DIR "${LIB_DIR}/glfw")
add_subdirectory("${GLFW_DIR}")




# Add Main.cpp
add_executable("${PROJECT_NAME}" "${SRC_DIR}/Main.cpp")

target_link_libraries("${PROJECT_NAME}" bgfx)
target_link_libraries("${PROJECT_NAME}" bx)

