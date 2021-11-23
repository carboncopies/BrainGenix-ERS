########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(SceneLoader

            # Add Source Files (.cpp)
            "SceneLoader.cpp"

            # Add Header Files (.h)
            "SceneLoader.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(SceneLoader
    )

# Link Internal Libs
target_link_libraries(SceneLoader
    LoggingSystem
    Model
    ModelLoader
    Shader
    )

target_include_directories(SceneLoader PUBLIC ./)
target_link_libraries(${PROJECT_NAME} SceneLoader)

