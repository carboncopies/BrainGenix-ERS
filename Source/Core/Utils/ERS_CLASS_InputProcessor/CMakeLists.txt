########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_CLASS_InputProcessor

            # Add Source Files (.cpp)
            "ERS_CLASS_InputProcessor.cpp"

            # Add Header Files (.h)
            "ERS_CLASS_InputProcessor.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_CLASS_InputProcessor
    yaml-cpp
    glm
    glad
    glfw
    IMGUI
    )

# Link Internal Libs
target_link_libraries(ERS_CLASS_InputProcessor
    ERS_STRUCT_Camera
    ERS_CLASS_LoggingSystem

    ERS_STRUCT_Model
    ERS_STRUCT_Scene
    ERS_SceneManager

    VisualEditor

    ERS_STRUCT_Shader
    ERS_ShaderLoader
    ERS_CLASS_Framebuffer

    ERS_SceneLoader
    )

target_include_directories(ERS_CLASS_InputProcessor PUBLIC ./)

