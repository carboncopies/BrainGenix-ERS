########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(VisualEditor

            # Add Source Files (.cpp)
            "Grid.cpp"

            # Add Header Files (.h)
            "Grid.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(VisualEditor
    yaml-cpp
    glm
    glad
    glfw
    FreeImage
    )

# Link Internal Libs
target_link_libraries(VisualEditor
    NoClip
    LoggingSystem
    )

target_include_directories(VisualEditor PUBLIC ./)
target_link_libraries(${PROJECT_NAME} VisualEditor)