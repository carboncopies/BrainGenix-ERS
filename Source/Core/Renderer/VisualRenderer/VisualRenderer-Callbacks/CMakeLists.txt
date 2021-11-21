########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(VisualRenderer-Callbacks

            # AddbSource Files (.cpp)
            "Callbacks.cpp"

            # Add Header Files (.h)
            "Callbacks.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(VisualRenderer-Callbacks
    glad
    glfw
    )

# Link Internal Libs
target_link_libraries(VisualRenderer-Callbacks
    NoClip
    )

target_include_directories(VisualRenderer-Callbacks PUBLIC ./)
target_link_libraries(${PROJECT_NAME} VisualRenderer-Callbacks)