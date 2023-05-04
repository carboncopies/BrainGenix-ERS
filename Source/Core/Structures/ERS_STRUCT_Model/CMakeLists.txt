########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_STRUCT_Model 

            # Add Source Files (.cpp)
            "Model.cpp"

            # Add Header Files (.h)
            "Model.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_STRUCT_Model
    yaml-cpp
    glm
    glad
    glfw
    assimp::assimp
    )

# Link Internal Libs
target_link_libraries(ERS_STRUCT_Model
    ERS_STRUCT_Shader
    ERS_STRUCT_Mesh
    ERS_STRUCT_Texture
    ERS_STRUCT_OpenGLDefaults
    )

target_include_directories(ERS_STRUCT_Model PUBLIC ./)