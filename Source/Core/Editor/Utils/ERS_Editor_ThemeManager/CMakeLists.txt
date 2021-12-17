########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(Theme

            # Add Source Files (.cpp)
            "Theme.cpp"

            # Add Header Files (.h)
            "Theme.h"
            
            ${BACKWARD_ENABLE}
            )
set_property(TARGET Theme PROPERTY CXX_STANDARD 17)
            
# Link 3rd Party Libs
target_link_libraries(Theme
    yaml-cpp
    IMGUI
    )

# Link Internal Libs
target_link_libraries(Theme
    LoggingSystem
    )

target_include_directories(Theme PUBLIC ./)