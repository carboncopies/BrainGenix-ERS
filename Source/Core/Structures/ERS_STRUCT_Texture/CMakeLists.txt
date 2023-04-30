########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_STRUCT_Texture

            # Add Source Files (.cpp)
            "Texture.cpp"

            # Add Header Files (.h)
            "Texture.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_STRUCT_Texture
    yaml-cpp
    glm
    glad
    glfw
    assimp::assimp
    FreeImage
    )

# Link Internal Libs
target_link_libraries(ERS_STRUCT_Texture
    ERS_STRUCT_TextureLevel
    )

target_include_directories(ERS_STRUCT_Texture PUBLIC ./)