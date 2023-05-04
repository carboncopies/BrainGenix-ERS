########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_GetExecutablePath

            # Add Source Files (.cpp)
            "GetExecutablePath.cpp"

            # Add Header Files (.h)
            "GetExecutablePath.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_GetExecutablePath
    WhereAmI
    )

# Link Internal Libs
target_link_libraries(ERS_GetExecutablePath
    )

target_include_directories(ERS_GetExecutablePath PUBLIC ./)