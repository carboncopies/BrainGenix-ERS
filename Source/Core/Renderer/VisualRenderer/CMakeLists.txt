########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(VisualRenderer

            # Add Source Files (.cpp)
            "ShaderManager.cpp"
            "WindowInputProcessor.cpp"
            "VisualRenderer.cpp"
            "InputProcessor.cpp"

            # Add Header Files (.h)
            "ShaderManager.h"
            "WindowInputProcessor.h"
            "VisualRenderer.h"
            "InputProcessor.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(VisualRenderer
    yaml-cpp
    glm
    glad
    glfw
    IMGUI
    )

# Link Internal Libs
target_link_libraries(VisualRenderer
    NoClip
    LoggingSystem
    ImageLoader
    TextureLoader
    ModelLoader

    Model
    Scene
    SceneLoader
    SceneManager

    VisualEditor
    )

target_include_directories(VisualRenderer PUBLIC ./)
target_link_libraries(${PROJECT_NAME} VisualRenderer)

