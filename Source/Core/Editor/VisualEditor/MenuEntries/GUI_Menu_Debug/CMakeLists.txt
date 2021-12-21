########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(Menu_Window

            # Add Source Files (.cpp)

            "GUI_Menu_Window.cpp"

            # Add Header Files (.h)
            "GUI_Menu_Window.h"


            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Menu_Window
    glad
    glfw
    IMGUI
    )

# Link Internal Libs
target_link_libraries(Menu_Window
    ERS_STRUCT_SystemUtils

    Widgets
    Window_SceneTree
    Window_SystemLog
    
    )

target_include_directories(Menu_Window PUBLIC ./)
