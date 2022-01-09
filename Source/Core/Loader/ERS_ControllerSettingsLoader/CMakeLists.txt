########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_ControllerSettings

            # Add Source Files (.cpp)
            "ERS_ControllerSettings.cpp"

            # Add Header Files (.h)
            "ERS_ControllerSettings.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_ControllerSettings
    yaml-cpp
    )

# Link Internal Libs
target_link_libraries(ERS_ControllerSettings
    ERS_STRUCT_SystemUtils
    ERS_STRUCT_ControllerSettings
    )


target_include_directories(ERS_ControllerSettings PUBLIC ./)
