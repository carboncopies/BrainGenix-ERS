########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(Widgets

            # Add Source Files (.hpp)
            "GUI_Widget_FramerateCounter.hpp"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Widgets
    glad
    glfw
    IMGUI
    )

# Link Internal Libs
target_link_libraries(Widgets
    LoggingSystem
    
    Theme
    FontManager
    )

target_include_directories(Widgets PUBLIC ./)