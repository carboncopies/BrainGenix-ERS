########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_STRUCT_Mesh

            # Add Source Files (.cpp)
            "ERS_STRUCT_Mesh.cpp"

            # Add Header Files (.h)
            "ERS_STRUCT_Mesh.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_STRUCT_Mesh
    yaml-cpp
    glm
    glad
    glfw
    assimp
    )

# Link Internal Libs
target_link_libraries(ERS_STRUCT_Mesh
    ERS_STRUCT_Shader
    Textures
    Vertex
    ImageLoader
    )

target_include_directories(ERS_STRUCT_Mesh PUBLIC ./)