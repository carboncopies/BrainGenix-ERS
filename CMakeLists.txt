# Set CMAKE Version, Define Project
cmake_minimum_required (VERSION 3.1...3.21)
project(
	"BrainGenix-ERS"
	VERSION "0.1.2"
	LANGUAGES CXX
	)

# Set Dirs
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Third-Party")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")
set(BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Binaries")
set(CMAKE_UTIL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMake/Utils")
set(CMAKE_BUILD_UTILS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMake/BuildUtils")

# Include Util CMake Scripts
include(${CMAKE_UTIL_DIR}/ColorizeMessages.cmake)
include(${CMAKE_UTIL_DIR}/SetBinaryDir.cmake)
include(${CMAKE_UTIL_DIR}/DisableTargetWarnings.cmake)


# Include Package Addition Scripts
include(${CMAKE_BUILD_UTILS_DIR}/Threads.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/YAML-CPP.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/Glad.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/GLM.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/ImGui.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/ImGuizmo.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/ImPlot.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/ImGuiFileDialog.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/Zep.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/GLFW.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/PCIIDS.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/FreeImage.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/Assimp.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/Backward.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/Tracy.cmake)








# Add Backward Library (Header Only)
add_subdirectory(${LIB_DIR}/backward)

# Add Tracy Library (Not Header Only)
add_subdirectory(${LIB_DIR}/tracy)
include_directories(${LIB_DIR}/tracy)
disable_target_warnings(TracyClient)

# Add MySQL Connector Library (Not Header Only)
include (${CMAKE_BUILD_UTILS_DIR}/MySQLConnector.cmake)

# Add Monado OpenXR Runtime
#include(${CMAKE_BUILD_UTILS_DIR}/Monado.cmake)




# Add Main.cpp
add_executable(${PROJECT_NAME} ${SRC_DIR}/Main.cpp ${LIB_DIR}/tracy/TracyClient.cpp ${BACKWARD_ENABLE})
target_link_libraries(${PROJECT_NAME}

  # Third Party Libs
  yaml-cpp
  glad
  glfw
  TracyClient

  # Internal Libs
  ConfigurationLoader
  LoggingSystem
  Renderer
  HardwareInformation


  ERS_SceneManager
  ERS_ModelLoader
  ERS_SceneLoader  
  ERS_ModelWriter
  ERS_ProjectLoader
  ERS_ProjectWriter
  ERS_InputOutputSubsystem
  ERS_FramerateManager
  ERS_ProjectManager

  ERS_STRUCT_SystemUtils
  ERS_STRUCT_ProjectUtils

  )


# ADD INTERNAL SUBDIRECTORIES
add_subdirectory(${SRC_DIR}/Core/Utils/LoggingSystem)
add_subdirectory(${SRC_DIR}/Core/Utils/ConfigurationLoader)
add_subdirectory(${SRC_DIR}/Core/Utils/FileIO)
add_subdirectory(${SRC_DIR}/Core/Utils/DatabaseInterface)
add_subdirectory(${SRC_DIR}/Core/Utils/IOManager)
add_subdirectory(${SRC_DIR}/Core/Utils/InputProcessor)
add_subdirectory(${SRC_DIR}/Core/Utils/HardwareInformation)
add_subdirectory(${SRC_DIR}/Core/Utils/ERS_InputOutputSubsystem)


add_subdirectory(${SRC_DIR}/Core/Manager/ERS_FramerateManager)
add_subdirectory(${SRC_DIR}/Core/Manager/ERS_SceneManager)
add_subdirectory(${SRC_DIR}/Core/Manager/ERS_ProjectManager)


add_subdirectory(${SRC_DIR}/Core/Editor/Utils/ERS_Editor_ThemeManager)
add_subdirectory(${SRC_DIR}/Core/Editor/Utils/ERS_Editor_FontManager)
add_subdirectory(${SRC_DIR}/Core/Editor/Utils/ERS_Editor_UserProfileManager)
add_subdirectory(${SRC_DIR}/Core/Editor/Utils/ERS_Editor_3DCursor)

add_subdirectory(${SRC_DIR}/Core/Editor/VisualEditor)
add_subdirectory(${SRC_DIR}/Core/Editor/VisualEditor/Widgets)
add_subdirectory(${SRC_DIR}/Core/Editor/VisualEditor/Windows)
add_subdirectory(${SRC_DIR}/Core/Editor/VisualEditor/MenuEntries)


add_subdirectory(${SRC_DIR}/Core/Renderer)
add_subdirectory(${SRC_DIR}/Core/Renderer/VisualRenderer)
add_subdirectory(${SRC_DIR}/Core/Renderer/VisualRenderer/Framebuffer)


add_subdirectory(${SRC_DIR}/Core/Structures/Cameras/NoClip)
add_subdirectory(${SRC_DIR}/Core/Structures/Meshes)
add_subdirectory(${SRC_DIR}/Core/Structures/Model)
add_subdirectory(${SRC_DIR}/Core/Structures/Textures)
add_subdirectory(${SRC_DIR}/Core/Structures/Vertex)
add_subdirectory(${SRC_DIR}/Core/Structures/Scene)
add_subdirectory(${SRC_DIR}/Core/Structures/Shader)
add_subdirectory(${SRC_DIR}/Core/Structures/Project)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_HardwareInfo)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_LocRotScale)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_IOData)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_SystemUtils)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_ProjectUtils)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_Project)


add_subdirectory(${SRC_DIR}/Core/Loader/TextureLoader)
add_subdirectory(${SRC_DIR}/Core/Loader/ImageLoader)
add_subdirectory(${SRC_DIR}/Core/Loader/ERS_SceneLoader)
add_subdirectory(${SRC_DIR}/Core/Loader/ShaderLoader)
add_subdirectory(${SRC_DIR}/Core/Loader/ERS_ProjectLoader)
add_subdirectory(${SRC_DIR}/Core/Loader/ERS_ModelLoader)

add_subdirectory(${SRC_DIR}/Core/Writers/ERS_SceneWriter)
add_subdirectory(${SRC_DIR}/Core/Writers/ERS_ModelWriter)
add_subdirectory(${SRC_DIR}/Core/Writers/ERS_ProjectWriter)


# COPY FILES TO BINARY DIR
file(COPY "${SRC_DIR}/Assets/" DESTINATION "${BIN_DIR}/Assets")
file(COPY "${SRC_DIR}/EditorAssets/" DESTINATION "${BIN_DIR}/EditorAssets")
file(COPY "${SRC_DIR}/EditorAssets/DefaultLayout/imgui.ini" DESTINATION "${BIN_DIR}")
file(COPY "${SRC_DIR}/Shaders/" DESTINATION "${BIN_DIR}/Shaders")

# Set Configuration Based On Platform
if (WIN32)
  configure_file("${SRC_DIR}/Config-Windows.yaml" "${BIN_DIR}/Config.yaml" COPYONLY)
else()
  configure_file("${SRC_DIR}/Config-Linux.yaml" "${BIN_DIR}/Config.yaml" COPYONLY)
endif()