########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_ModelLoader

            # Add Source Files (.cpp)
            "ERS_ModelLoader.cpp"

            # Add Header Files (.h)
            "ERS_ModelLoader.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_ModelLoader
    yaml-cpp
    glm
    assimp
    FreeImage
    )

# Link Internal Libs
target_link_libraries(ERS_ModelLoader
    ERS_STRUCT_Mesh
    ERS_STRUCT_Model
    ERS_STRUCT_Texture
    ERS_STRUCT_Vertex
    
    ERS_STRUCT_SystemUtils
    )

target_include_directories(ERS_ModelLoader PUBLIC ./)
