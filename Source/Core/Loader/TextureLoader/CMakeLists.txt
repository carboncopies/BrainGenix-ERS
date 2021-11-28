########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(TextureLoader 

            # Add Source Files (.cpp)
            "TextureLoader.cpp"

            # Add Header Files (.h)
            "TextureLoader.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(TextureLoader
    glad
    glfw
    )

# Link Internal Libs
target_link_libraries(TextureLoader
    LoggingSystem
    ImageLoader
    Textures
    )

target_include_directories(TextureLoader PUBLIC ./)
