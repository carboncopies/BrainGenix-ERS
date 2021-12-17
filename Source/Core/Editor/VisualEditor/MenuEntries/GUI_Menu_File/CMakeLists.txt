########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(Menu_File

            # Add Source Files (.cpp)
            "GUI_Menu_File.cpp"

            # Add Header Files (.h)
            "GUI_Menu_File.h"


            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Menu_File
    glad
    glfw
    IMGUI
    ImGuiFileDialog
    )

# Link Internal Libs
target_link_libraries(Menu_File
    LoggingSystem
    ERS_STRUCT_SystemUtils

    GUI_Window_ImportProgressBar

    ERS_SceneWriter
    SceneManager

    Scene
    )

target_include_directories(Menu_File PUBLIC ./)
