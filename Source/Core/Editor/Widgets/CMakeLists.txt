########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(Widgets

            # Add Source Files (.cpp)
            "GUI_Widget_FramerateCounter.cpp"
            "GUI_Widget_FramerateHistogram.cpp"
            "GUI_Widget_FrameratePlot.cpp"

            # Add Header Files (.h)
            "GUI_Widget_FramerateCounter.h"
            "GUI_Widget_FramerateHistogram.h"
            "GUI_Widget_FrameratePlot.h"


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

target_include_directories(Widgets PUBLIC ./)

# FIXME: ADD README EXPLAINING TEMPLATES, WHAT STANDARD TO USE, ETC!