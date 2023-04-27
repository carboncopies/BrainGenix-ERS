# Set CMAKE Version, Define Project
cmake_minimum_required (VERSION 3.1...3.21)


# Set Configuration Options
option(ENABLE_BACKWARD "Build ERS With Backward to provide some stack trace information or not" ON)


# Set Non-User Changable Configuration Data (Used during build process )
option (USE_SUPERBUILD "Whether or not a superbuild should be invoked" ON) # You probably don't want to change this one - used internally


# Set Dirs
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")
set(BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Binaries")
set(CMAKE_UTIL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMake/Utils")
set(CMAKE_BUILD_UTILS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMake/BuildUtils")
set(CMAKE_FIND_UTILS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMake/FindUtils")
set(CMAKE_SCRIPTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMake/Scripts")
set(CMAKE_UTILS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/CMake")
set(CMAKE_ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/EditorAssets")
set(PROJECT_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_CXX_VISIBILITY_PRESET hidden)








# Superbuild Configuration
if (USE_SUPERBUILD)

  project (SUPERBUILD NONE)

  # Add Superbuild Runner
  include(${CMAKE_UTILS_DIR}/SuperBuildMaster.cmake)
  return()
else()

  project(
      "BrainGenix-ERS"
      VERSION "0.4.0"
      LANGUAGES CXX
  )

endif()



set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Superbuild Configuration
message(STATUS "Superbuild Configuration:")

include(${CMAKE_UTILS_DIR}/SuperBuilds/Assimp.cmake)
include(${CMAKE_UTILS_DIR}/SuperBuilds/ThreadNamingUtils.cmake)
include(${CMAKE_UTILS_DIR}/SuperBuilds/OZZAnimation.cmake)
include(${CMAKE_UTILS_DIR}/SuperBuilds/MeshOptimizer.cmake)
include(${CMAKE_UTILS_DIR}/SuperBuilds/FreeImage.cmake)
include(${CMAKE_UTILS_DIR}/SuperBuilds/YAMLCPP.cmake)
include(${CMAKE_UTILS_DIR}/SuperBuilds/Lucifer.cmake)
include(${CMAKE_UTILS_DIR}/SuperBuilds/LuaJIT.cmake)







# Include Util CMake Scripts
include(${CMAKE_UTIL_DIR}/ColorizeMessages.cmake)
include(${CMAKE_UTIL_DIR}/SetBinaryDir.cmake)
include(${CMAKE_UTIL_DIR}/DisableTargetWarnings.cmake)

# Run Configuration Tools
include(${CMAKE_SCRIPTS_DIR}/VersioningSystem/VersioningSystem.cmake)
include(${CMAKE_SCRIPTS_DIR}/CompilePlatformInfo/CompilePlatformInfo.cmake)
include(${CMAKE_SCRIPTS_DIR}/CompileTimeStamp/CompileTimeStamp.cmake)


# Include Package Addition Scripts
# include(${CMAKE_BUILD_UTILS_DIR}/Lucifer.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/Backward.cmake)
#include(${CMAKE_BUILD_UTILS_DIR}/Python.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/Threads.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/Glad.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/GLM.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/ImGui.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/ImGuizmo.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/ImPlot.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/ImGuiFileDialog.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/ImGuiColorTextEdit.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/GLFW.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/PCIIDS.cmake)
#include(${CMAKE_BUILD_UTILS_DIR}/PyBind11.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/Filesystem.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/WhereAmI.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/PlatformFolders.cmake)



# Add LIBRARY INTERFACE SUBDIRECTORIES
ERSBuildLogger(${Green} "Configuring Library Interfaces")

add_subdirectory(${SRC_DIR}/Interface/Library/MeshOptimizerInterface)
message(STATUS "Configured MeshOptimizer Interface")
add_subdirectory(${SRC_DIR}/Interface/Library/LuaInterface)
message(STATUS "Configured Lua Interface")

ERSBuildLogger(${BoldGreen} "Finished Configuring Library Interfaces")


# ADD STRUCT INTERFACE SUBDIRECTORIES
ERSBuildLogger(${Green} "Configuring Structure Interfaces")

ERSBuildLogger(${BoldGreen} "Finished Configuring Structure Interfaces")


# ADD INTERNAL SUBDIRECTORIES
ERSBuildLogger(${Green} "Configuring Internal Libraries")

add_subdirectory(${SRC_DIR}/Internal/LoggingSystem)
message(STATUS "Configured Internal Library 'LoggingSystem'")
add_subdirectory(${SRC_DIR}/Internal/OpenGLLoggingSystem)
message(STATUS "Configured Internal Library 'OpenGLLoggingSystem'")
add_subdirectory(${SRC_DIR}/Internal/ArgumentParser)
message(STATUS "Configured Internal Library 'ArgumentParser'")
add_subdirectory(${SRC_DIR}/Internal/GPURequest)
message(STATUS "Configured Internal Library 'GPURequest'")
add_subdirectory(${SRC_DIR}/Internal/HardwareInformation)
message(STATUS "Configured Internal Library 'HardwareInformation'")
add_subdirectory(${SRC_DIR}/Internal/InputOutputSubsystem)
message(STATUS "Configured Internal Library 'InputOutputSubsystem'")
add_subdirectory(${SRC_DIR}/Internal/ExternalModelLoader)
message(STATUS "Configured Internal Library 'ExternalModelLoader'")
add_subdirectory(${SRC_DIR}/Internal/ModelImporter)
message(STATUS "Configured Internal Library 'ModelImporter'")
add_subdirectory(${SRC_DIR}/Internal/LocalConfigLoader)
message(STATUS "Configured Internal Library 'LocalConfigLoader'")
add_subdirectory(${SRC_DIR}/Internal/GetExecutablePath)
message(STATUS "Configured Internal Library 'GetExecutablePath'")


ERSBuildLogger(${BoldGreen} "Finished Configuring Internal Libraries")


# ADD CORE SUBDIRECTORIES
ERSBuildLogger(${Green} "Configuring Core Subsystems")
add_subdirectory(${SRC_DIR}/Core/Manager/ERS_FramerateManager)
add_subdirectory(${SRC_DIR}/Core/Manager/ERS_SceneManager)
add_subdirectory(${SRC_DIR}/Core/Manager/ERS_ProjectManager)
add_subdirectory(${SRC_DIR}/Core/Manager/ERS_ControllerManager)

add_subdirectory(${SRC_DIR}/Core/Editor/)
add_subdirectory(${SRC_DIR}/Core/Editor/Utils/ERS_Editor_ThemeManager)
add_subdirectory(${SRC_DIR}/Core/Editor/Utils/ERS_Editor_FontManager)
add_subdirectory(${SRC_DIR}/Core/Editor/Utils/ERS_Editor_UserProfileManager)
add_subdirectory(${SRC_DIR}/Core/Editor/Utils/ERS_Editor_LayoutManager)
add_subdirectory(${SRC_DIR}/Core/Editor/Utils/ERS_Editor_3DCursor)
add_subdirectory(${SRC_DIR}/Core/Editor/Utils/ERS_Editor_WindowManager)
add_subdirectory(${SRC_DIR}/Core/Editor/Windows)
add_subdirectory(${SRC_DIR}/Core/Editor/Menus)

add_subdirectory(${SRC_DIR}/Core/Renderer/ERS_CLASS_RendererManager)
add_subdirectory(${SRC_DIR}/Core/Renderer/ERS_CLASS_VisualRenderer)

add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_Camera)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_SceneCamera)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_HumanInputDeviceUtils)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_Mesh)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_Model)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_Texture)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_TextureLevel)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_Vertex)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_Scene)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_Shader)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_HardwareInfo)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_LocRotScale)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_IOData)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_SystemUtils)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_ProjectUtils)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_Project)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_ControllerSettings)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_ModelWriterData)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_ShaderProgramAssetIDs)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_Viewport)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_Light)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_OpenGLDefaults)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_SceneObject)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_Script)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_DepthMap)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_RendererSettings)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_ShaderUniformData)
add_subdirectory(${SRC_DIR}/Core/Structures/ERS_STRUCT_ModelImportOptions)

#add_subdirectory(${SRC_DIR}/Core/Script/ERS_CLASS_PythonInterpreterIntegration)

add_subdirectory(${SRC_DIR}/Core/Loader/ERS_SceneLoader)
add_subdirectory(${SRC_DIR}/Core/Loader/ERS_ShaderLoader)
add_subdirectory(${SRC_DIR}/Core/Loader/ERS_ProjectLoader)
add_subdirectory(${SRC_DIR}/Core/Loader/ERS_ModelLoader)
add_subdirectory(${SRC_DIR}/Core/Loader/ERS_ControllerSettingsLoader)

add_subdirectory(${SRC_DIR}/Core/Writers/ERS_SceneWriter)
add_subdirectory(${SRC_DIR}/Core/Writers/ERS_ModelWriter)
add_subdirectory(${SRC_DIR}/Core/Writers/ERS_ProjectWriter)
ERSBuildLogger(${BoldGreen} "Finished Configuring Core Subsystems")


# Configure Sources
set(MAIN_SOURCES
    ${SRC_DIR}/Main.cpp
    ${SRC_DIR}/Main.h
    ${BACKWARD_ENABLE}
)


# Create Main Executable
if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    ERSBuildLogger(${Blue} "Detected Platform To Be Darwin, Building Bundle")
    include(${CMAKE_SCRIPTS_DIR}/DarwinBundle/DarwinBundle.cmake)
else()
    ERSBuildLogger(${Blue} "Platform Not Darwin, Building Regular Binary")
    include(${CMAKE_SCRIPTS_DIR}/LinuxBundle/LinuxBundle.cmake)
endif()

target_link_libraries(${PROJECT_NAME}

    # Third Party Libs
    glad
    glfw
    ozz_animation # Temp

    # Temporary -- DELETE THESE WHEN NOT TESTING HERE ANYMORE --
    ERS_LuaInterface

    # Internal Libs
    ERS_GPURequest
    ERS_LoggingSystem
    ERS_ModelImporter
    ERS_LocalConfigLoader

    ERS_GetExecutablePath

    ERS_HardwareInformation
   # ERS_CLASS_PythonInterpreterIntegration
    ERS_ArgumentParser

    ERS_SceneManager
    ERS_ModelLoader
    ERS_SceneLoader  
    ERS_ModelWriter
    ERS_ProjectLoader
    ERS_ProjectWriter
    ERS_InputOutputSubsystem
    ERS_FramerateManager
    ERS_ProjectManager
    ERS_ControllerInputManager

    ERS_STRUCT_HumanInputDeviceUtils
    ERS_STRUCT_SystemUtils
    ERS_STRUCT_ProjectUtils
    ERS_STRUCT_RendererSettings

    Renderer
)
target_include_directories(${PROJECT_NAME} PRIVATE ${SRC_DIR})

# Run Configuration On EditorAssetBundle
include(${CMAKE_SCRIPTS_DIR}/EditorAssetsBundle/EditorAssetsBundle.cmake)


