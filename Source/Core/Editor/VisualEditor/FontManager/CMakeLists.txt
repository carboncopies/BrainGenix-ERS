########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(FontManager

            # Add Source Files (.cpp)
            "FontManager.cpp"

            # Add Header Files (.h)
            "FontManager.h"
            
            ${BACKWARD_ENABLE}
            )
set_property(TARGET FontManager PROPERTY CXX_STANDARD 17)
            
# Link 3rd Party Libs
target_link_libraries(FontManager
    yaml-cpp
    IMGUI
    )

# Link Internal Libs
target_link_libraries(FontManager
    LoggingSystem
    )

target_include_directories(FontManager PUBLIC ./)