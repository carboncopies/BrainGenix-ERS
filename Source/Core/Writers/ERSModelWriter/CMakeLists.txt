########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERSModelWriter

            # Add Source Files (.cpp)
            "ERSModelWriter.cpp"

            # Add Header Files (.h)
            "ERSModelWriter.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERSModelWriter
    )

# Link Internal Libs
target_link_libraries(ERSModelWriter
    LoggingSystem
    Model
    ModelLoader
    Scene
    Meshes
    Textures
    Shader
    )

target_include_directories(ERSModelWriter PUBLIC ./)

