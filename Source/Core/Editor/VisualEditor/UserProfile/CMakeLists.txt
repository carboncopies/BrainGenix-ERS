########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(UserProfile

            # Add Source Files (.cpp)
            "UserProfile.cpp"

            # Add Header Files (.h)
            "UserProfile.h"
            
            ${BACKWARD_ENABLE}
            )
set_property(TARGET UserProfile PROPERTY CXX_STANDARD 17)
            
# Link 3rd Party Libs
target_link_libraries(UserProfile
    yaml-cpp
    IMGUI
    )

# Link Internal Libs
target_link_libraries(UserProfile
    LoggingSystem
    )

target_include_directories(UserProfile PUBLIC ./)