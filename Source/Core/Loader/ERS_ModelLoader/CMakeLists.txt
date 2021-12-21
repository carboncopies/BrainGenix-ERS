########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ModelLoader

            # Add Source Files (.cpp)
            "ModelLoader.cpp"

            # Add Header Files (.h)
            "ModelLoader.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ModelLoader
    yaml-cpp
    glm
    glad
    glfw
    assimp
    FreeImage
    )

# Link Internal Libs
target_link_libraries(ModelLoader
    Meshes
    Model
    Textures
    TextureLoader
    )


target_include_directories(ModelLoader PUBLIC ./)
