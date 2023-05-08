########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_CLASS_VisualRenderer

            # Add Source Files (.cpp)
            "VisualRenderer.cpp"
            "IconRenderer.cpp"
            "Grid.cpp"
            "InputProcessor.cpp"
            "MeshRenderer.cpp"
            "DepthMaps.cpp"
            "ShadowMaps.cpp"
            "ViewportOverlay.cpp"
            "ViewportMenu.cpp"
            "BoundingBoxRenderer.cpp"
            "FindShaderByName.cpp"
            "CheckForMeshTransparency.cpp"
            "MeshTransparencySort.cpp"
            "DrawMesh.cpp"
            "DrawMeshNoTextures.cpp"
            "ResetMeshTexture.cpp"
            "ConvertRotationToFrontVector.cpp"
            "MeshTransparencySortNoTextures.cpp"
            "SetShaderUniformData.cpp"

            

            # Add Header Files (.h)
            "VisualRenderer.h"
            "IconRenderer.h"
            "Grid.h"
            "InputProcessor.h"
            "MeshRenderer.h"
            "DepthMaps.h"
            "ShadowMaps.h"
            "ViewportOverlay.h"
            "ViewportMenu.h"
            "BoundingBoxRenderer.h"
            "FindShaderByName.h"
            "CheckForMeshTransparency.h"
            "MeshTransparencySort.h"
            "DrawMesh.h"
            "DrawMeshNoTextures.h"
            "ResetMeshTexture.h"
            "ConvertRotationToFrontVector.h"
            "MeshTransparencySortNoTextures.h"
            "SetShaderUniformData.h"




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
    ERS_STRUCT_SceneCamera
    
    ERS_LoggingSystem

    ERS_SceneManager
    ERS_ShaderLoader
    ERS_SceneLoader

    ERS_Editor_3DCursor

    ERS_STRUCT_LocRotScale
    ERS_STRUCT_SystemUtils
    ERS_STRUCT_Viewport
    ERS_STRUCT_Shader
    ERS_STRUCT_Model
    ERS_STRUCT_DepthMap
    ERS_STRUCT_Scene
    ERS_STRUCT_ProjectUtils
    ERS_STRUCT_OpenGLDefaults
    ERS_STRUCT_RendererSettings
    ERS_STRUCT_ShaderUniformData

    )

target_include_directories(ERS_CLASS_VisualRenderer PUBLIC ./)

