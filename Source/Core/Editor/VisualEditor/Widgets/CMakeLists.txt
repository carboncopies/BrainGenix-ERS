########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(Widgets

            # Add Source Files (.cpp)
            "GUI_Widget_FramerateCounter.cpp"
            "GUI_Widget_FramerateHistogram.cpp"
            "GUI_Widget_FramerateGraph.cpp"
            "GUI_Widget_FrameratePlot.cpp"
            "GUI_Widget_RenderingSettings.cpp"

            # Add Header Files (.h)
            "GUI_Widget_FramerateCounter.h"
            "GUI_Widget_FramerateHistogram.h"
            "GUI_Widget_FramerateGraph.h"
            "GUI_Widget_FrameratePlot.h"
            "GUI_Widget_RenderingSettings.h"


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
    LoggingSystem
    
    Theme
    FontManager
    )

target_include_directories(Widgets PUBLIC ./)

# FIXME: ADD README EXPLAINING TEMPLATES, WHAT STANDARD TO USE, ETC!