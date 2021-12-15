########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ModelWriter

            # Add Source Files (.cpp)
            "ModelWriter.cpp"

            # Add Header Files (.h)
            "ModelWriter.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ModelWriter
    )

# Link Internal Libs
target_link_libraries(ModelWriter
    LoggingSystem
    Model
    ModelLoader
    Scene
    Meshes
    Textures
    Shader
    )

target_include_directories(ModelWriter PUBLIC ./)

