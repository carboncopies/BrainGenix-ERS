########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(GUI_Subwindow_ModelRenameModal

            # Add Source Files (.cpp)
            "GUI_Subwindow_ModelRenameModal.cpp"

            # Add Header Files (.h)
            "GUI_Subwindow_ModelRenameModal.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(GUI_Subwindow_ModelRenameModal
    glad
    glfw
    IMGUI
    )

# Link Internal Libs
target_link_libraries(GUI_Subwindow_ModelRenameModal
    ERS_SceneManager
    )

target_include_directories(GUI_Subwindow_ModelRenameModal PUBLIC ./)