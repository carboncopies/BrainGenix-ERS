########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################



# Specify CPP Files In Source (Name Should Start With Parent Dir Name)
set(VisualRenderer_Sources
    "Callbacks.cpp"
    "ShaderManager.cpp"
    "WindowInputProcessor.cpp"
)

# Specify Header Files In Source (Name Should Start With Parent Dir Name)
set(VisualRenderer_Headers
    "Callbacks.h"
    "ShaderManager.h"
    "WindowInputProcessor.h"
)


# Create Library (Name Should Be Parent Dir Name)
add_library(VisualRenderer ${LoggingSystem_Sources} ${LoggingSystem_Headers} ${BACKWARD_ENABLE})
target_link_libraries(VisualRenderer 
    yaml-cpp
    glm
    glad
    glfw
    )
target_include_directories(VisualRenderer PUBLIC ./)
target_link_libraries(${PROJECT_NAME} VisualRenderer)

