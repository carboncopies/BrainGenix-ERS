# Set CMAKE Version, Define Project
cmake_minimum_required (VERSION 3.1...3.21)


# Set Configuration Options
option(ENABLE_BACKWARD "Build ERS With Backward to provide some stack trace information or not" ON)


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



# Setup vcpkg script with CMake (note: should be placed before project() call)
set(CMAKE_TOOLCHAIN_FILE ${LIB_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")


project(
    "BrainGenix-ERS"
    VERSION "0.4.0"
    LANGUAGES CXX
)



set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add Libraries
message(STATUS "Finding yaml-cpp Package")
find_package(yaml-cpp CONFIG REQUIRED)

message(STATUS "Finding assimp Package")
find_package(assimp CONFIG REQUIRED)

message(STATUS "Finding freeimage Package")
find_package(freeimage CONFIG REQUIRED)

message(STATUS "Finding lua Package")
find_package(Lua REQUIRED)

message(STATUS "Finding meshoptimizer Package")
find_package(meshoptimizer CONFIG REQUIRED)

message(STATUS "Finding glfw3 Package")
find_package(glfw3 CONFIG REQUIRED)

message(STATUS "Finding platform-folders Package")
find_package(platform_folders CONFIG REQUIRED)

message(STATUS "Finding ghc-filesystem Package")
find_package(ghc_filesystem CONFIG REQUIRED)

message(STATUS "Finding infoware Package")
find_package(infoware CONFIG REQUIRED)


message(STATUS "Finding bg-ers-iosubsystem Package")
find_package(bg-ers-iosubsystem CONFIG REQUIRED)


# Include Util CMake Scripts
include(${CMAKE_UTIL_DIR}/ColorizeMessages.cmake)
include(${CMAKE_UTIL_DIR}/SetBinaryDir.cmake)
include(${CMAKE_UTIL_DIR}/DisableTargetWarnings.cmake)

# Run Configuration Tools
include(${CMAKE_SCRIPTS_DIR}/VersioningSystem/VersioningSystem.cmake)
include(${CMAKE_SCRIPTS_DIR}/CompilePlatformInfo/CompilePlatformInfo.cmake)
include(${CMAKE_SCRIPTS_DIR}/CompileTimeStamp/CompileTimeStamp.cmake)


# Include Package Addition Scripts
include(${CMAKE_BUILD_UTILS_DIR}/Backward.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/Threads.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/Glad.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/GLM.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/ImGui.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/ImGuizmo.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/ImPlot.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/ImGuiFileDialog.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/ImGuiColorTextEdit.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/WhereAmI.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/ThreadNamingUtils.cmake)
include(${CMAKE_BUILD_UTILS_DIR}/Lucifer.cmake)



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

add_subdirectory(${SRC_DIR}/Core/Script/ERS_CLASS_LuaJITInterpreterIntegration)


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

add_executable("ERS" ${MAIN_SOURCES})
set(EXECUTABLE_TYPE "Binary")
target_link_libraries("ERS"

    # Third Party Libs
    glad
    glfw


    # Internal Libs
    ERS_GPURequest
    ERS_LoggingSystem
    ERS_ModelImporter
    ERS_LocalConfigLoader

    ERS_GetExecutablePath
    ERS_CLASS_LuaJITInterpreterIntegration
    ERS_HardwareInformation
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
target_include_directories("ERS" PRIVATE ${SRC_DIR})

# Run Configuration On EditorAssetBundle
include(${CMAKE_SCRIPTS_DIR}/EditorAssetsBundle/EditorAssetsBundle.cmake)
