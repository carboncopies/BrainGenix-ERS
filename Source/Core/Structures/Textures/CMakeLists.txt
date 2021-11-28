########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(Textures

            # Add Source Files (.cpp)

            # Add Header Files (.h)
            "2DTexture.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Textures
    yaml-cpp
    glm
    glad
    glfw
    assimp
    FreeImage
    )

# Link Internal Libs
target_link_libraries(Textures
    )

target_include_directories(Textures PUBLIC ./)