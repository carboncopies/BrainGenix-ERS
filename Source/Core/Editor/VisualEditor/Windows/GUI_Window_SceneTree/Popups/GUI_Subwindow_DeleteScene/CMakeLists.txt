########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(GUI_Subwindow_DeleteScene

            # Add Source Files (.cpp)
            "GUI_Subwindow_DeleteScene.cpp"

            # Add Header Files (.h)
            "GUI_Subwindow_DeleteScene.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(GUI_Subwindow_DeleteScene
    )

# Link Internal Libs
target_link_libraries(GUI_Subwindow_DeleteScene
    SceneManager
    Scene
    )

target_include_directories(GUI_Subwindow_DeleteScene PUBLIC ./)