########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_3DCursor

            # Add Source Files (.cpp)
            "3DCursor.cpp"

            # Add Header Files (.h)
            "3DCursor.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_3DCursor
    glm
    glad
    glfw
    IMGUI
    ImGuizmo
    )

# Link Internal Libs
target_link_libraries(ERS_3DCursor
    LoggingSystem
    NoClip
    ERS_STRUCT_LocRotScale
    )

target_include_directories(ERS_3DCursor PUBLIC ./)