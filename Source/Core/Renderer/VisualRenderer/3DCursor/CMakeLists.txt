########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(3DCursor

            # Add Source Files (.cpp)
            "3DCursor.cpp"

            # Add Header Files (.h)
            "3DCursor.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(3DCursor
    glm
    glad
    glfw
    IMGUI
    ImGuizmo
    )

# Link Internal Libs
target_link_libraries(3DCursor
    LoggingSystem
    NoClip
    )

target_include_directories(3DCursor PUBLIC ./)