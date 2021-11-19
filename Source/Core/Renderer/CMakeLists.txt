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
target_link_libraries(Renderer
    yaml-cpp
    glm
    glad
    glfw
    )
target_include_directories(Renderer PUBLIC ./)
target_link_libraries(${PROJECT_NAME} Renderer)
