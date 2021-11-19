########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################



# Specify CPP Files In Source (Name Should Start With Parent Dir Name)
set(Renderer_Sources
    "RendererManager.cpp"
)

# Specify Header Files In Source (Name Should Start With Parent Dir Name)
set(Renderer_Headers
    "RendererManager.h"
)


# Create Library (Name Should Be Parent Dir Name)
add_library(Renderer SHARED ${LoggingSystem_Sources} ${LoggingSystem_Headers})
target_link_libraries(Renderer
    yaml-cpp
    glm
    glad
    glfw
    )
target_include_directories(Renderer PUBLIC ./)
target_link_libraries(${PROJECT_NAME} Renderer)
