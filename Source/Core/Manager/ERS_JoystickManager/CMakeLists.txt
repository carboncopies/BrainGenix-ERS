########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_JoystickManager

            # Add Source Files (.cpp)
            "ERS_JoystickManager.cpp"

            # Add Header Files (.h)
            "ERS_JoystickManager.h"

            ${BACKWARD_ENABLE}
)

set_property(TARGET ERS_JoystickManager PROPERTY CXX_STANDARD 17)

# Link 3rd Party Libs
target_link_libraries(ERS_JoystickManager
    glad
    glfw
    )

# Link Internal Libs
target_link_libraries(ERS_JoystickManager

    ERS_STRUCT_SystemUtils

    )

target_include_directories(ERS_JoystickManager PUBLIC ./)

