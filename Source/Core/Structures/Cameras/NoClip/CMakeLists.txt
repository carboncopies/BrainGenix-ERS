########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(NoClip 

            # Add Source Files (.cpp)
            "NoClip.cpp"

            # Add Header Files (.h)
            "NoClip.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(NoClip
    glm
    glad
    )

# Link Internal Libs
target_link_libraries(NoClip
    )

target_include_directories(NoClip PUBLIC ./)