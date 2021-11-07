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

# Enable Debugging
#set (CMAKE_BUILD_TYPE RelWithDebInfo)

# Add Main.cpp
set(SOURCES "${SRC_DIR}/Main.cpp")
add_executable("${PROJECT_NAME}" "${SOURCES}")

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
file(COPY "${SRC_DIR}/Config.yaml" DESTINATION "${BIN_DIR}")
file(COPY "${SRC_DIR}/Shaders/" DESTINATION "${BIN_DIR}/Shaders")
file(COPY "${SRC_DIR}/Assets/" DESTINATION "${BIN_DIR}/Assets")

target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)


# Add YAML-CPP Library
set(YAML_CPP_DIR "yaml-cpp")
add_subdirectory("${LIB_DIR}/${YAML_CPP_DIR}")
target_link_libraries("${PROJECT_NAME}" "${YAML_CPP_DIR}")

# Add RapidJSON
set(RAPID_JSON_DIR "rapidjson")
include_directories("${LIB_DIR}/${RAPID_JSON_DIR}/include/rapidjson")

# # Link Glad Library
set(GLAD_DIR "glad")
include_directories("${LIB_DIR}/${GLAD_DIR}/src")
include_directories("${LIB_DIR}/${GLAD_DIR}/include")

# Add STB Image Library
include_directories("${LIB_DIR}/stb")

# Add GLM Library
set(GLM_DIR "glm")
add_subdirectory("${LIB_DIR}/${GLM_DIR}")

# Add GLFW Library
set(GLFW_DIR "${LIB_DIR}/glfw")
add_subdirectory("${GLFW_DIR}")
target_link_libraries("${PROJECT_NAME}" "glfw" "${GLFW_LIBRARIES}")

# Add FreeImage Library
set(FREEIMAGE_DIR "${LIB_DIR}/FreeImage/FreeImage")
add_subdirectory("${FREEIMAGE_DIR}")
target_link_libraries("${PROJECT_NAME}" "FreeImage" "${FREEIMAGE_LIBRARIES}")

# Add ASSIMP Library
set(ASSIMP_DIR "${LIB_DIR}/assimp")
add_subdirectory("${ASSIMP_DIR}")
target_link_libraries("${PROJECT_NAME}" "assimp" "${ASSIMP_LIBRARIES}")

# # Add Bullet Library
# set(BULLET_DIR "${LIB_DIR}/bullet")
# add_subdirectory("${BULLET_DIR}")
# include_directories("${BULLET_DIR}/src")

# Add Meshoptimizer Library
set(MESHOPTIMIZER_DIR "${LIB_DIR}/meshoptimizer")
add_subdirectory("${MESHOPTIMIZER_DIR}")
target_link_libraries("${PROJECT_NAME}" "meshoptimizer" "${MESHOPTIMIZER_DIR}")

# # Add CEGUI Library
# set(CEGUI_DIR "${LIB_DIR}/cegui")
# add_subdirectory("${CEGUI_DIR}")
# target_link_libraries("${PROJECT_NAME}" "cegui" "${CEGUI_DIR}")

# # Add Libsndfile Library
# set(LIBSNDFILE_DIR "${LIB_DIR}/libsndfile")
# add_subdirectory("${LIBSNDFILE_DIR}")
# target_link_libraries("${PROJECT_NAME}" "libsndfile" "${LIBSNDFILE_DIR}")


# Add MYSQL Library
# set(MYSQL_CONNECTOR_DIR "${LIB_DIR}/mysql-connector-cpp")
# # include_directories("${MYSQL_CONNECTION_DIR}/include")
# # include_directories("${MYSQL_CONNECTION_DIR}/include/cppconn")
# # link_directories("${MYSQL_CONNECTION_DIR}/lib")
# add_subdirectory("${MYSQL_CONNECTOR_DIR}")
# target_link_libraries("${PROJECT_NAME}" curl mysqlcppconn)
# target_compile_features("${PROJECT_NAME}" PRIVATE cxx_range_for)  


# # Add CPPKafka Library
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


