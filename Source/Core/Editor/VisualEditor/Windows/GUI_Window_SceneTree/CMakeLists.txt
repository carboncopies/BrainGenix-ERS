########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################

# Add Dependencies
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Popups)


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

    GUI_Subwindow_SceneRenameModal
    GUI_Subwindow_ModelRenameModal

    GUI_Windowutil_DuplicateScene

    )

target_include_directories(Window_SceneTree PUBLIC ./)
