########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(learnopengl
            # Add Source Files (.cpp)
            "camera.h"
            "model.h"
            "shader.h"

            ${BACKWARD_ENABLE}
)

set_property(TARGET learnopengl PROPERTY LANGUAGES CXX)

# Link 3rd Party Libs
target_link_libraries(learnopengl

    glad
    glfw

    )

# Link Internal Libs
target_link_libraries(learnopengl

    )

target_include_directories(learnopengl PUBLIC ./)

