########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_SceneLoader

            # Add Source Files (.cpp)
            "ERS_SceneLoader.cpp"

            # Add Header Files (.h)
            "ERS_SceneLoader.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_SceneLoader
    yaml-cpp
    )

# Link Internal Libs
target_link_libraries(ERS_SceneLoader

    ERS_ModelLoader

    ERS_CLASS_LoggingSystem

    ERS_STRUCT_Model
    ERS_STRUCT_Scene
    ERS_STRUCT_Mesh
    ERS_STRUCT_Texture
    ERS_STRUCT_Shader
    ERS_STRUCT_Light

    )

target_include_directories(ERS_SceneLoader PUBLIC ./)

