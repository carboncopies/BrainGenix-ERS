########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(IOManager

            # Add Source Files (.cpp)
            "IOManager.cpp"

            # Add Header Files (.h)
            "IOManager.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(IOManager
    glad
    glfw
    IMGUI
    )

# Link Internal Libs
target_link_libraries(IOManager
    LoggingSystem
    )

target_include_directories(IOManager PUBLIC ./)