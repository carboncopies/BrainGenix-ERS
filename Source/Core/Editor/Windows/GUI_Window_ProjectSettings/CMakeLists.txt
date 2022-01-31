########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################

# Create Library (Name Should Be Parent Dir Name)
add_library(Window_ProjectSettings

            # Add Source Files (.cpp)
            "GUI_Window_ProjectSettings.cpp"

            # Add Header Files (.h)
            "GUI_Window_ProjectSettings.h"


            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Window_ProjectSettings
    IMGUI
    )

# Link Internal Libs
target_link_libraries(Window_ProjectSettings

    ERS_STRUCT_SystemUtils
    ERS_STRUCT_ProjectUtils

    )

target_include_directories(Window_ProjectSettings PUBLIC ./)
