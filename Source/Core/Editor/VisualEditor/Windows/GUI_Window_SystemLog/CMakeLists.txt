########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################

# Create Library (Name Should Be Parent Dir Name)
add_library(Window_SystemLog

            # Add Source Files (.cpp)
            "GUI_Window_SystemLog.cpp"

            # Add Header Files (.h)
            "GUI_Window_SystemLog.h"


            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Window_SystemLog
    glad
    glfw
    IMGUI
    )

# Link Internal Libs
target_link_libraries(Window_SystemLog
    ERS_STRUCT_SystemUtils
    )

target_include_directories(Window_SystemLog PUBLIC ./)
