########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(VisualRenderer

            # Add Source Files (.cpp)
            "VisualRenderer.cpp"

            # Add Header Files (.h)
            "VisualRenderer.h"

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
    InputProcessor
    LoggingSystem
    ImageLoader
    TextureLoader
    ModelLoader

    Model
    Scene
    SceneLoader
    SceneManager

    VisualEditor

    Shader
    ShaderLoader
    Framebuffer
    )

target_include_directories(VisualRenderer PUBLIC ./)

