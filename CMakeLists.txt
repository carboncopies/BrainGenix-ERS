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

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BIN_DIR})

foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${BIN_DIR} )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${BIN_DIR} )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${BIN_DIR} )
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )


set(CMAKE_INSTALL_PREFIX ${BIN_DIR})

function(disable_target_warnings target)
  target_compile_options(${target} PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
	    -w>
    $<$<CXX_COMPILER_ID:MSVC>:
      /w>
    )
endfunction()


# Add Threading Library
find_package(Threads REQUIRED)

# Add YAML-CPP Library (Not Header Only)
add_subdirectory("${LIB_DIR}/yaml-cpp")
disable_target_warnings(yaml-cpp)

# Link Glad Library (Not Header Only)
add_subdirectory(${LIB_DIR}/glad)
disable_target_warnings(glad)

# Link Dirent Library (Header Only)
add_subdirectory(${LIB_DIR}/dirent)

# Add GLM Library (Header Only)
add_subdirectory(${LIB_DIR}/glm)
include_directories(${LIB_DIR}/glm)

# Add DearImGUI Library (Not Header Only)
add_subdirectory(${LIB_DIR}/imgui)

# Add ImGuizmo Library (Not Header Only)
add_subdirectory(${LIB_DIR}/ImGuizmo)

# Add ImPlot Library (Not Header Only)
add_subdirectory(${LIB_DIR}/implot)

# Add ImGuiFileDialog (Not Header Only)
add_subdirectory(${LIB_DIR}/ImGuiFileDialog/ImGuiFileDialog)
disable_target_warnings(ImGuiFileDialog)

# Add Zep (Not Header Only)
add_subdirectory(${LIB_DIR}/zep)
disable_target_warnings(Zep)

# Add GLFW Library (Not Header Only)
add_subdirectory(${LIB_DIR}/glfw)
disable_target_warnings(glfw)

# Add Infoware Library (Not Header Only)
set(INFOWARE_PCI_IDS_PATH ${LIB_DIR}/pciids/pci.ids)
include_directories(${LIB_DIR}/infoware/include)
add_subdirectory(${LIB_DIR}/infoware)
disable_target_warnings(infoware)

# Add FreeImage Library (Not Header Only)
add_subdirectory(${LIB_DIR}/FreeImage/FreeImage)
disable_target_warnings(FreeImage)

# Add ASSIMP Library (Not Header Only)
add_subdirectory(${LIB_DIR}/assimp)
disable_target_warnings(assimp)

# Add Backward Library (Header Only)
add_subdirectory(${LIB_DIR}/backward)

# Add Tracy Library (Not Header Only)
add_subdirectory(${LIB_DIR}/tracy)
include_directories(${LIB_DIR}/tracy)
disable_target_warnings(TracyClient)

# Add MySQL Connector Library (Not Header Only)
if (WIN32)
    message("Database Support Disabled On Windows Due To SSL Errors, Please Use Linux/BSD Instead")
else()
  add_subdirectory(${LIB_DIR}/mysql-connector-linux)
endif()


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