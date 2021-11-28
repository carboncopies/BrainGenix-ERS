########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(Meshes

            # Add Source Files (.cpp)
            "Mesh.cpp"

            # Add Header Files (.h)
            "Mesh.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Meshes
    yaml-cpp
    glm
    glad
    glfw
    assimp
    )

# Link Internal Libs
target_link_libraries(Meshes
    Shader
    Textures
    Vertex
    ImageLoader
    )

target_include_directories(Meshes PUBLIC ./)