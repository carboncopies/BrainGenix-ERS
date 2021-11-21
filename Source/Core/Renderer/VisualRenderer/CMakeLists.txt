########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(VisualRenderer

            # Add Source Files (.cpp)
            "ShaderManager.cpp"
            "WindowInputProcessor.cpp"
            "Callbacks.cpp"

            # Add Header Files (.h)
            "ShaderManager.h"
            "WindowInputProcessor.h"
            "Callbacks.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(VisualRenderer
    yaml-cpp
    glm
    glad
    glfw
    )

# Link Internal Libs
target_link_libraries(VisualRenderer
    NoClip
    LoggingSystem
    Image
    )

target_include_directories(VisualRenderer PUBLIC ./)
target_link_libraries(${PROJECT_NAME} VisualRenderer)

