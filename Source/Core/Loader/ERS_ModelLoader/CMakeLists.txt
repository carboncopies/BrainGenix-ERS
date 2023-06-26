########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_ModelLoader

            # Add Source Files (.cpp)
            "ModelLoader.cpp"
            "AssetStreamingManager.cpp"
            "AsyncTextureUpdater.cpp"
            "AssetStreamingSystemResourceMonitor.cpp"
            "Legacy_PreprocessTextureInfo.cpp"
            "ModelMetadataDecoderV0.0.0.cpp"
            "ModelMetadataDecoderV0.0.1.cpp"
            "ModelMetadataDecoderV0.0.2.cpp"
            "ModelMetadataDecoderManager.cpp"

            # Add Header Files (.h)
            "ModelLoader.h"
            "AssetStreamingManager.h"
            "AsyncTextureUpdater.h"
            "AssetStreamingSystemResourceMonitor.h"
            "Legacy_PreprocessTextureInfo.h"
            "ModelMetadataDecoderV0.0.0.h"
            "ModelMetadataDecoderV0.0.1.h"
            "ModelMetadataDecoderV0.0.2.h"
            "ModelMetadataDecoderManager.h"


            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_ModelLoader
    yaml-cpp
    glm
    assimp::assimp
    freeimage::FreeImage
    ThreadNamingUtils
    )

# Link Internal Libs
target_link_libraries(ERS_ModelLoader
    ERS_STRUCT_Mesh
    ERS_STRUCT_Model
    ERS_STRUCT_Texture
    ERS_STRUCT_TextureLevel
    ERS_STRUCT_Vertex
    ERS_STRUCT_Scene

    ERS_STRUCT_SystemUtils
    ERS_STRUCT_Scene
    ERS_STRUCT_Camera
    ERS_STRUCT_HardwareInfo
    )

target_include_directories(ERS_ModelLoader PUBLIC ./)
