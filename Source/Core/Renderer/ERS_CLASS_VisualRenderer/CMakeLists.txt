########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_CLASS_VisualRenderer

            # Add Source Files (.cpp)
            "ERS_CLASS_VisualRenderer.cpp"
            "ERS_CLASS_LightIconRenderer.cpp"
            "ERS_CLASS_Grid.cpp"
            "ERS_CLASS_Framebuffer.cpp"

            # Add Header Files (.h)
            "ERS_CLASS_VisualRenderer.h"
            "ERS_CLASS_LightIconRenderer.h"
            "ERS_CLASS_Grid.h"
            "ERS_CLASS_Framebuffer.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_CLASS_VisualRenderer
    yaml-cpp
    glm
    glad
    glfw
    IMGUI
    )

# Link Internal Libs
target_link_libraries(ERS_CLASS_VisualRenderer
    ERS_STRUCT_Camera
    ERS_CLASS_InputProcessor
    ERS_CLASS_LoggingSystem

    ERS_SceneManager
    ERS_ShaderLoader
    ERS_SceneLoader

    ERS_Editor_3DCursor


    ERS_STRUCT_LocRotScale
    ERS_STRUCT_SystemUtils
    ERS_STRUCT_Viewport
    ERS_STRUCT_Shader
    ERS_STRUCT_Model
    ERS_STRUCT_Scene
    ERS_STRUCT_OpenGLDefaults

    )

target_include_directories(ERS_CLASS_VisualRenderer PUBLIC ./)

