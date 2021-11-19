# Set CMAKE Version, Define Project
cmake_minimum_required (VERSION 3.1...3.21)
project(
	"BrainGenix-ERS"
	VERSION "0.0.1"
	LANGUAGES CXX
	)

# Set Dirs
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Third-Party")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")
set(BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Binaries")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_INSTALL_PREFIX ${BIN_DIR})



# add_compile_options(-fPIC)



function(disable_target_warnings target)
  target_compile_options(${target} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
	    -w>
    $<$<CXX_COMPILER_ID:MSVC>:
      /w>
    )
endfunction()


# Add YAML-CPP Library (Not Header Only)
add_subdirectory("${LIB_DIR}/yaml-cpp")
disable_target_warnings(yaml-cpp)

# Link Glad Library (Not Header Only)
add_subdirectory(${LIB_DIR}/glad)
disable_target_warnings(glad)

# Add GLM Library (Header Only)
add_subdirectory(${LIB_DIR}/glm)

# Add GLFW Library (Not Header Only)
add_subdirectory(${LIB_DIR}/glfw)
disable_target_warnings(glfw)

# Add FreeImage Library (Not Header Only)
add_subdirectory(${LIB_DIR}/FreeImage/FreeImage)
disable_target_warnings(FreeImage)

# Add ASSIMP Library (Not Header Only)
add_subdirectory(${LIB_DIR}/assimp)
disable_target_warnings(assimp)

# Add Backward Library (Header Only)
add_subdirectory(${LIB_DIR}/backward)



# # # Add Bullet Library (Not Header Only)
# # set(BULLET_DIR "${LIB_DIR}/bullet")
# # add_subdirectory("${BULLET_DIR}")
# # include_directories("${BULLET_DIR}/src")


# # Add Meshoptimizer Library (Not Header Only)
# add_subdirectory(${LIB_DIR}/meshoptimizer)
# disable_target_warnings(meshoptimizer)

# # Add CEGUI Library (Not Header Only)
# set(CEGUI_SAMPLES_ENABLED 0)
# set(CEGUI_SAMPLES_ENABLE_WIDGET_DEMO 0)

# set(GLFW_H_PATH ${LIB_DIR}/glfw/include/GLFW/glfw3.h)
# set(LIBXML2_LIBRARY ${LIB_DIR}/libxml2)
# set(LIBXML2_INCLUDE_DIR ${LIB_DIR}/libxml2/include)
# set(SDL2IMAGE_LIB ${LIB_DIR}/SDL2_image) 
# set(SDL2IMAGE_H_PATH ${LIB_DIR}/SDL2_image/SDL_image.h)
# set(EPOXY_LIB ${LIB_DIR}/libepoxy)
# set(EPOXY_H_PATH ${LIB_DIR}/libepoxy/include)

# add_subdirectory(${LIB_DIR}/cegui)
# disable_target_warnings(CEGUIBase-0)


# # Add Libsndfile Library (Not H#include "../Loader/BGAsset/BGAssetLoader.h"
#include "../Structures/DataBuffer/DataBuffer.h"

#include "../Structures/Model/Model.h"
#include "../Structures/Cameras/NoClip/NoClip.h"
#include "../Structures/Scene/Scene.h"
#include "../Loader/Scene/SceneDecoder.h"eader Only)
# set(LIBSNDFILE_DIR "${LIB_DIR}/libsndfile")
# add_subdirectory("${LIBSNDFILE_DIR}")
# target_link_libraries("${PROJECT_NAME}" "libsndfile" "${LIBSNDFILE_DIR}")


# # Add MYSQL Library (Not Header Only)
# set(MYSQL_CONNECTOR_DIR "${LIB_DIR}/mysql-connector-cpp")
# include_directories("${MYSQL_CONNECTION_DIR}/include")
# include_directories("${MYSQL_CONNECTION_DIR}/include/cppconn")
# link_directories("${MYSQL_CONNECTION_DIR}/lib")
# add_subdirectory(${LIB_DIR}/mysql-connector-cpp)
# #disable_target_warnings(mysqlcppconn)
# target_link_libraries("${PROJECT_NAME}" curl mysqlcppconn)
# target_compile_features("${PROJECT_NAME}" PRIVATE cxx_range_for)  


# # Add CPPKafka Library (Not Header Only)
# set(CPPKAFKA_LIBRARY "${LIB_DIR}/cppkafka")
# set(CPPKAFKA_INCLUDES "${CPPKAFKA_LIBRARY}/include")
# include(FindPackageHandleStandardArgs)
# include(SelectLibraryConfigurations)

# find_path(CPPKAFKA_INCLUDES NAMES cppkafka.h HINTS ${CURRENT_INSTALLED_DIR} PATH_SUFFIXES cppkafka)

# find_library(CPPKAFKA_LIBRARY_DEBUG NAMES cppkafka PATH_SUFFIXES lib PATHS "${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}" NO_DEFAULT_PATH REQUIRED)
# find_library(CPPKAFKA_LIBRARY_RELEASE NAMES cppkafka PATH_SUFFIXES lib PATHS "${_VCPKG_INSTALLED_DIR}/${VCPKG_TARGET_TRIPLET}/debug" NO_DEFAULT_PATH REQUIRED)

# select_library_configurations(CPPKAFKA)

# target_include_directories("${PROJECT_NAME}" "${CPPKAFKA_INCLUDES}")
# target_link_libraries("${PROJECT_NAME}" "${CPPKAFKA_LIBRARY}")


# Add Main.cpp
add_executable(${PROJECT_NAME} ${SRC_DIR}/Main.cpp ${BACKWARD_ENABLE})
# target_include_directories(${PROJECT_NAME} PRIVATE Source)
# target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
# target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
target_link_libraries(${PROJECT_NAME}
  yaml-cpp
  glad
  glm
  glfw
#   #${GLFW_LIBRARIES}
  FreeImage
  assimp
#   meshoptimizer
#   backward
#   CEGUIBase-0
#   #mysqlcppconn
  )


# ADD INTERNAL SUBDIRECTORIES
add_subdirectory(${SRC_DIR}/Core/Utils/LoggingSystem)
add_subdirectory(${SRC_DIR}/Core/Utils/ConfigurationLoader)

add_subdirectory(${SRC_DIR}/Core/Renderer)
add_subdirectory(${SRC_DIR}/Core/Renderer/VisualRenderer)

add_subdirectory(${SRC_DIR}/Core/Loader)

add_subdirectory(${SRC_DIR}/Core/Structures/AssetLoaderQueue)
add_subdirectory(${SRC_DIR}/Core/Structures/Cameras/NoClip)
add_subdirectory(${SRC_DIR}/Core/Structures/DataBuffer)
add_subdirectory(${SRC_DIR}/Core/Structures/Meshes)
add_subdirectory(${SRC_DIR}/Core/Structures/Model)
add_subdirectory(${SRC_DIR}/Core/Structures/Textures)
add_subdirectory(${SRC_DIR}/Core/Structures/Scene)
add_subdirectory(${SRC_DIR}/Core/Structures/Vertex)

add_subdirectory(${SRC_DIR}/Core/Loader/BGAsset)
add_subdirectory(${SRC_DIR}/Core/Loader/Configuration)
add_subdirectory(${SRC_DIR}/Core/Loader/Image)
add_subdirectory(${SRC_DIR}/Core/Loader/ModelLoader)
add_subdirectory(${SRC_DIR}/Core/Loader/SceneLoader)


# COPY FILES TO BINARY DIR
file(COPY "${SRC_DIR}/Config.yaml" DESTINATION "${BIN_DIR}")
file(COPY "${SRC_DIR}/Shaders/" DESTINATION "${BIN_DIR}/Shaders")
file(COPY "${SRC_DIR}/Assets/" DESTINATION "${BIN_DIR}/Assets")