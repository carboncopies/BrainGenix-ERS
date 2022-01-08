########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################

# Create Library (Name Should Be Parent Dir Name)
add_library(Window_About

            # Add Source Files (.cpp)
            "GUI_Window_About.cpp"

            # Add Header Files (.h)
            "GUI_Window_About.h"


            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Window_About
    glad
    glfw
    IMGUI
    )

# Link Internal Libs
target_link_libraries(Window_About
    ERS_STRUCT_SystemUtils
    )

target_include_directories(Window_About PUBLIC ./)
