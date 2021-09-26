 
## CMAKE MIN VERSION ##
cmake_minimum_required(VERSION 3.1...3.21)

## SET PROJECT PROPERTIES ##
project(
    "BrainGenix-ERS"
    VERSION "0.0.1"
    LANGUAGES CXX
    )


## SET VARAIBLES ##
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Libraries")
set(BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Dist")

set(SOURCES "${SRC_DIR}/Main.cpp")


## CREATE MAIN EXECUTABLE ##
add_executable(${PROJECT_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
configure_file("${SRC_DIR}/Config.yaml" "${BIN_DIR}/Config.yaml" COPYONLY)
file(COPY "${SRC_DIR}/Shaders" DESTINATION "${BIN_DIR}")
file(COPY "${SRC_DIR}/Assets" DESTINATION "${BIN_DIR}")


target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)




## LINK YAML-CPP ##
set(YAML_CPP_VERSION "yaml-cpp")
add_subdirectory("${LIB_DIR}/${YAML_CPP_VERSION}")
target_link_libraries("${PROJECT_NAME}" "${YAML_CPP_VERSION}")

## Link GLFW ##
set(GLFW_DIR "${LIB_DIR}/glfw")
add_subdirectory("${GLFW_DIR}")
target_link_libraries(${PROJECT_NAME} "glfw" "${GLFW_LIBRARIES}")

## LINK GLM ##
set(GLM_DIR "${LIB_DIR}/glm")
add_subdirectory("${GLM_DIR}")
target_link_libraries(${PROJECT_NAME} "glm" "${GLM_LIBRARIES}")

## LINK STB ##
set(STB_DIR "${LIB_DIR}/stb")
include_directories(${STB_DIR})

## LINK ASSIMP ##
set(ASSIMP_DIR "${LIB_DIR}/assimp")
add_subdirectory("${ASSIMP_DIR}")
target_link_libraries(${PROJECT_NAME} "assimp" "${ASSIMP_LIBRARIES}")

## LINK IMGUI ##
set(IMGUI_DIR "${LIB_DIR}/imgui")
include_directories(${IMGUI_DIR})


