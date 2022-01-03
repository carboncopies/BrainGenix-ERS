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

    Model
    Scene
    ERS_SceneManager

    VisualEditor

    Shader
    ShaderLoader
    Framebuffer

    ERS_Editor_3DCursor
    ERS_SceneLoader

    ERS_STRUCT_LocRotScale
    ERS_STRUCT_SystemUtils
    )

target_include_directories(VisualRenderer PUBLIC ./)

