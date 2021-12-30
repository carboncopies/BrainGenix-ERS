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
    )

# Link Internal Libs
target_link_libraries(ERS_SceneLoader
    LoggingSystem
    Model
    ERS_ModelLoader
    Scene
    Meshes
    Textures
    Shader
    )

target_include_directories(ERS_SceneLoader PUBLIC ./)

