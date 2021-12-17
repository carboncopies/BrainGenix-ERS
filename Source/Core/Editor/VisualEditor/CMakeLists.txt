########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(VisualEditor

            # Add Source Files (.cpp)
            "GUI.cpp"

            # Add Header Files (.h)
            "GUI.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(VisualEditor
    glad
    glfw
    IMGUI
    ImPlot
    ImGuizmo
    )

# Link Internal Libs
target_link_libraries(VisualEditor
    LoggingSystem
    ERS_STRUCT_SystemUtils
    
    Theme
    FontManager
    UserProfile
    3DCursor

    Widgets

    Window_SceneTree

    Menu_File

    )

target_include_directories(VisualEditor PUBLIC ./)