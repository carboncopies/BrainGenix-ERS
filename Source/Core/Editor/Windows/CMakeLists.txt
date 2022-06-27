#######################################################################
# Use This CMakeLists.txt To Add Your Source Windows Subfolder Cmakes #
#######################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_GUI_Windows

            # Add Source Files (.cpp)
            "GUI_Widget_FramerateCounter.cpp"
            "GUI_Widget_FramerateHistogram.cpp"
            "GUI_Widget_FrameLatencyGraph.cpp"
            "GUI_Widget_FramerateGraph.cpp"
            "GUI_Widget_FrameratePlot.cpp"
            "GUI_Widget_RenderingSettings.cpp"
            "GUI_Widget_ObjectProperties.cpp"
            "GUI_Widget_RAMGraph.cpp"

            # Add Header Files (.h)
            "GUI_Widget_FramerateCounter.h"
            "GUI_Widget_FramerateHistogram.h"
            "GUI_Widget_FrameLatencyGraph.h"
            "GUI_Widget_FramerateGraph.h"
            "GUI_Widget_FrameratePlot.h"
            "GUI_Widget_RenderingSettings.h"
            "GUI_Widget_ObjectProperties.h"
            "GUI_Widget_RAMGraph.h"


            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Widgets
    glad
    glfw
    IMGUI
    ImPlot
    )

# Link Internal Libs
target_link_libraries(Widgets
    ERS_CLASS_LoggingSystem
    
    ERS_Editor_ThemeManager
    ERS_Editor_FontManager
    ERS_Editor_3DCursor

    ERS_STRUCT_SystemUtils
    ERS_STRUCT_HardwareInfo
    ERS_STRUCT_Scene
    ERS_STRUCT_ProjectUtils
    ERS_STRUCT_RendererSettings


    ERS_SceneManager

    )

target_include_directories(ERS_GUI_Windows PUBLIC ./)

# FIXME: ADD README EXPLAINING TEMPLATES, WHAT STANDARD TO USE, ETC!




# Add Window Subdirs
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GUI_Window_ProjectSettings)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GUI_Window_SceneTree)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GUI_Window_ThemeSelector)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GUI_Window_ImportProgressBar)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GUI_Window_About)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GUI_Window_SystemLog)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GUI_Window_AssetExplorer)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GUI_Window_ControllerSettings)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GUI_Window_TestEditor)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GUI_Window_ShaderEditor)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/GUI_Window_ScriptEditor)