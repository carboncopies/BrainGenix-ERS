########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(GUI_Windowutil_DuplicateScene

            # Add Source Files (.cpp)
            "GUI_Windowutil_DuplicateScene.cpp"

            # Add Header Files (.h)
            "GUI_Windowutil_DuplicateScene.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(GUI_Windowutil_DuplicateScene
    )

# Link Internal Libs
target_link_libraries(GUI_Windowutil_DuplicateScene
    SceneManager
    )

target_include_directories(GUI_Windowutil_DuplicateScene PUBLIC ./)