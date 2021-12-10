########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(SceneWriter

            # Add Source Files (.cpp)
            "SceneWriter.cpp"

            # Add Header Files (.h)
            "SceneWriter.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(SceneWriter
    )

# Link Internal Libs
target_link_libraries(SceneWriter
    LoggingSystem
    Model
    ModelLoader
    Scene
    Meshes
    Textures
    Shader
    )

target_include_directories(SceneWriter PUBLIC ./)

