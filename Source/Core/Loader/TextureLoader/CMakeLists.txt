########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(TextureLoader 

            # Add Source Files (.cpp)
            "RendererManager.cpp"

            # Add Header Files (.h)
            "RendererManager.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(TextureLoader
    yaml-cpp
    glm
    glad
    glfw
    )

# Link Internal Libs
target_link_libraries(TextureLoader
    LoggingSystem
    VisualRenderer
    )

target_include_directories(TextureLoader PUBLIC ./)
target_link_libraries(${PROJECT_NAME} TextureLoader)
