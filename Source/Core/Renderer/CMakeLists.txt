########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(Renderer 

            # Add Source Files (.cpp)
            "RendererManager.cpp"

            # Add Header Files (.h)
            "RendererManager.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Renderer
    yaml-cpp
    glm
    glad
    glfw
    )

# Link Internal Libs
target_link_libraries(Renderer
    LoggingSystem
    VisualRenderer
    BGAssetManager
    DataBuffer
    Model
    NoClip
    Scene
    SceneDecoder
    )

target_include_directories(Renderer PUBLIC ./)
target_link_libraries(${PROJECT_NAME} Renderer)
