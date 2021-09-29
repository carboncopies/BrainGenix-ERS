# Set CMAKE Version, Define Project
cmake_minimum_required (VERSION 3.16.3)
project ("BrainGenix-ERS")

# Set Dirs
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Third-Party")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")
set(BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Binaries")

# Add Main.cpp
set(SOURCES "${SRC_DIR}/Main.cpp")
add_executable("${PROJECT_NAME}" "${SOURCES}")

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
#file(COPY "${SRC_DIR}/Assets" DESTINATION "${BIN_DIR}")

target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)


# Add YAML-CPP Library
set(YAML_CPP_DIR "${LIB_DIR}/yaml-cpp")
add_subdirectory("${YAML_CPP_DIR}")
target_link_libraries("${PROJECT_NAME}" "${YAML_CPP_LIBRARIES}")

# Add BGFX Library
set(BGFX_CMAKE_DIR "${LIB_DIR}/bgfx.cmake")
add_subdirectory("${BGFX_CMAKE_DIR}")
target_link_libraries("${PROJECT_NAME}" "bgfx")
target_link_libraries("${PROJECT_NAME}" "bx")

# Add GLFW Library
set(GLFW_DIR "${LIB_DIR}/glfw")
add_subdirectory("${GLFW_DIR}")
target_link_libraries("${PROJECT_NAME}" "glfw" "${GLFW_LIBRARIES}")