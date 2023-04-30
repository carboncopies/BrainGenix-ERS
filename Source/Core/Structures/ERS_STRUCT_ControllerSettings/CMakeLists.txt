########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_STRUCT_ControllerSettings 

            # Add Source Files (.cpp)
            "ControllerSettings.cpp"

            # Add Header Files (.h)
            "ControllerSettings.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_STRUCT_ControllerSettings
    )

# Link Internal Libs
target_link_libraries(ERS_STRUCT_ControllerSettings
    )

target_include_directories(ERS_STRUCT_ControllerSettings PUBLIC ./)
set_target_properties(ERS_STRUCT_ControllerSettings PROPERTIES LINKER_LANGUAGE CXX)