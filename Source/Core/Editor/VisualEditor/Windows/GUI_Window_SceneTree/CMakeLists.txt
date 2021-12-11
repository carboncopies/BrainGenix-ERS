########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(Window_SceneTree

            # Add Source Files (.cpp)

            "GUI_Widget_SceneTree.cpp"

            # Add Header Files (.h)
            "GUI_Widget_SceneTree.h"


            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Window_SceneTree
    glad
    glfw
    IMGUI
    ImPlot
    )

# Link Internal Libs
target_link_libraries(Window_SceneTree
    LoggingSystem
    
    Theme
    FontManager

    3DCursor

    Scene
    SceneManager

    )

target_include_directories(Window_SceneTree PUBLIC ./)
