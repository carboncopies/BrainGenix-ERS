########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(GUI_Windowutil_DeleteScene

            # Add Source Files (.cpp)
            "GUI_Windowutil_DeleteScene.cpp"

            # Add Header Files (.h)
            "GUI_Windowutil_DeleteScene.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(GUI_Windowutil_DeleteScene
    )

# Link Internal Libs
target_link_libraries(GUI_Windowutil_DeleteScene
    SceneManager
    Scene
    )

target_include_directories(GUI_Windowutil_DeleteScene PUBLIC ./)