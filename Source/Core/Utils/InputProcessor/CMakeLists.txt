########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(InputProcessor

            # Add Source Files (.cpp)
            "InputProcessor.cpp"

            # Add Header Files (.h)
            "InputProcessor.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(InputProcessor
    yaml-cpp
    glm
    glad
    glfw
    IMGUI
    )

# Link Internal Libs
target_link_libraries(InputProcessor
    ERS_STRUCT_Camera
    ERS_CLASS_LoggingSystem
    TextureLoader

    ERS_STRUCT_Model
    ERS_STRUCT_Scene
    ERS_SceneManager

    VisualEditor

    ERS_STRUCT_Shader
    ERS_ShaderLoader
    Framebuffer

    ERS_SceneLoader
    )

target_include_directories(InputProcessor PUBLIC ./)

