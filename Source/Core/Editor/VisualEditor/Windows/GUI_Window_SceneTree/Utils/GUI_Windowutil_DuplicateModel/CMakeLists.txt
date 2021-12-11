########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(GUI_Windowutil_DuplicateModel

            # Add Source Files (.cpp)
            "GUI_Windowutil_DuplicateModel.cpp"

            # Add Header Files (.h)
            "GUI_Windowutil_DuplicateModel.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(GUI_Windowutil_DuplicateModel
    )

# Link Internal Libs
target_link_libraries(GUI_Windowutil_DuplicateModel
    SceneManager
    Model
    )

target_include_directories(GUI_Windowutil_DuplicateModel PUBLIC ./)