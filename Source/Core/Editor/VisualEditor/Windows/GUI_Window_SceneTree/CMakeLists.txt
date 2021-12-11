########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(Window_SceneTree

            # Add Source Files (.cpp)

            "GUI_Window_SceneTree.cpp"

            # Add Header Files (.h)
            "GUI_Window_SceneTree.h"


            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Window_SceneTree
    glad
    glfw
    IMGUI
    )

# Link Internal Libs
target_link_libraries(Window_SceneTree
    LoggingSystem
    
    Scene
    SceneManager

    )

target_include_directories(Window_SceneTree PUBLIC ./)
