########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_GPURequest

            # Add Source Files (.cpp)
            "GPURequest.cpp"

            # Add Header Files (.h)
            "GPURequest.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_GPURequest
    )

# Link Internal Libs
target_link_libraries(ERS_GPURequest
    ERS_STRUCT_HardwareInfo
    bg-common-logger
    )


target_include_directories(ERS_GPURequest PUBLIC ./)
