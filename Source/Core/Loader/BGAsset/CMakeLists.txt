########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(BGAsset

            # Add Source Files (.cpp)
            "BGAssetManager.cpp"

            # Add Header Files (.h)
            "BGAssetManager.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(BGAsset
    yaml-cpp
    glm
    glad
    glfw
    assimp
    )

# Link Internal Libs
target_link_libraries(BGAsset
    LoggingSystem
    Scene
    DataBuffer

    )

target_include_directories(BGAsset PUBLIC ./)
target_link_libraries(${PROJECT_NAME} BGAsset)