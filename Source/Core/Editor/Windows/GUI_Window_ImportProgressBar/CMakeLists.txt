########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################

# Create Library (Name Should Be Parent Dir Name)
add_library(Window_ImportProgressBar

            # Add Source Files (.cpp)
            "GUI_Window_ImportProgressBar.cpp"

            # Add Header Files (.h)
            "GUI_Window_ImportProgressBar.h"


            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Window_ImportProgressBar
    glad
    glfw
    IMGUI
    )

# Link Internal Libs
target_link_libraries(Window_ImportProgressBar
    ERS_STRUCT_SystemUtils
    )

target_include_directories(Window_ImportProgressBar PUBLIC ./)
