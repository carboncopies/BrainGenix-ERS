########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(Shader

            # Add Source Files (.cpp)
            "Shader.cpp"

            # Add Header Files (.h)
            "Shader.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Shader
    glm
    glad
    glfw
    )

# Link Internal Libs
target_link_libraries(Shader
    ImageLoader
    )

target_include_directories(Shader PUBLIC ./)
target_link_libraries(${PROJECT_NAME} Shader)