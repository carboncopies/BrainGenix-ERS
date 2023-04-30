########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_SceneLoader

            # Add Source Files (.cpp)
            "SceneLoader.cpp"
            "YAMLHelpers.cpp"
            "SceneDecoderManager.cpp"
            "SceneDecoderV1.cpp"
            "SceneDecoderV2.cpp"
            "SceneDecoderV3.cpp"
            "SceneDecoderV4.cpp"
            "SceneDecoderV5.cpp"
            "SceneDecoderV6.cpp"

            # Add Header Files (.h)
            "SceneLoader.h"
            "YAMLHelpers.h"
            "SceneDecoderManager.h"
            "SceneDecoderV1.h"
            "SceneDecoderV2.h"
            "SceneDecoderV3.h"
            "SceneDecoderV4.h"
            "SceneDecoderV5.h"
            "SceneDecoderV6.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_SceneLoader
    yaml-cpp
    )

# Link Internal Libs
target_link_libraries(ERS_SceneLoader

    ERS_ModelLoader

    ERS_LoggingSystem

    ERS_STRUCT_Model
    ERS_STRUCT_Scene
    ERS_STRUCT_Mesh
    ERS_STRUCT_Texture
    ERS_STRUCT_Shader
    ERS_STRUCT_Light
    ERS_STRUCT_SceneCamera

    )

target_include_directories(ERS_SceneLoader PUBLIC ./)

