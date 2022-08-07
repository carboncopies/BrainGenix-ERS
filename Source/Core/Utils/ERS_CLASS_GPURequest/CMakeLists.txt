########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_CLASS_GPURequest

            # Add Source Files (.cpp)
            "ERS_CLASS_GPURequest.cpp"

            # Add Header Files (.h)
            "ERS_CLASS_GPURequest.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_CLASS_GPURequest
    )

# Link Internal Libs
target_link_libraries(ERS_CLASS_GPURequest
    )

target_include_directories(ERS_CLASS_GPURequest PUBLIC ./)