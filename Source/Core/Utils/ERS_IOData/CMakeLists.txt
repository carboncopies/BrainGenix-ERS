########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_IOData

            # Add Source Files (.cpp)
            "ERS_IOData.cpp"

            # Add Header Files (.h)
            "ERS_IOData.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_IOData
    )

# Link Internal Libs
target_link_libraries(ERS_IOData
    )

target_include_directories(ERS_IOData PUBLIC ./)