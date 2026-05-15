########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_STRUCT_AudioSource

            # Add Source Files (.cpp)
            "AudioSource.cpp"

            # Add Header Files (.h)
            "AudioSource.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_STRUCT_AudioSource
    glm
    )

# Link Internal Libs
target_link_libraries(ERS_STRUCT_AudioSource
    )

target_include_directories(ERS_STRUCT_AudioSource PUBLIC ./)
