########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################

# Create Library (Name Should Be Parent Dir Name)
add_library(Window_ControllerSettings

            # Add Source Files (.cpp)
            "GUI_Window_ControllerSettings.cpp"

            # Add Header Files (.h)
            "GUI_Window_ControllerSettings.h"


            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Window_ControllerSettings
    glad
    glfw
    IMGUI
    )

# Link Internal Libs
target_link_libraries(Window_ControllerSettings
    ERS_STRUCT_SystemUtils
    ERS_STRUCT_ProjectUtils
    ERS_STRUCT_HumanInputDeviceUtils
    )

target_include_directories(Window_ControllerSettings PUBLIC ./)
