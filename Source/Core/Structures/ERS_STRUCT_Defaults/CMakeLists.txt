########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_STRUCT_Defaults 

            # Add Header Files (.h)
            "ERS_STRUCT_Defaults.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_STRUCT_Defaults
    )

# Link Internal Libs
target_link_libraries(ERS_STRUCT_Defaults
    )

target_include_directories(ERS_STRUCT_Defaults PUBLIC ./)