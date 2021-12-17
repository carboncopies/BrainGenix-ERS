########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(GUI_Subwindow_SceneRenameModal

            # Add Source Files (.cpp)
            "GUI_Subwindow_SceneRenameModal.cpp"

            # Add Header Files (.h)
            "GUI_Subwindow_SceneRenameModal.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(GUI_Subwindow_SceneRenameModal
    glad
    glfw
    IMGUI
    ImPlot
    ImGuizmo
    )

# Link Internal Libs
target_link_libraries(GUI_Subwindow_SceneRenameModal
    LoggingSystem
    
    ERS_Editor_ThemeManager
    ERS_Editor_FontManager
    ERS_Editor_UserProfileManager

    Widgets
    3DCursor

    Window_SceneTree
    )

target_include_directories(GUI_Subwindow_SceneRenameModal PUBLIC ./)