########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(SceneManager

            # Add Source Files (.cpp)
            "SceneManager.cpp"

            # Add Header Files (.h)
            "SceneManager.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(SceneManager
    yaml-cpp
    )

# Link Internal Libs
target_link_libraries(SceneManager
    Scene
    LoggingSystem
    ERS_STRUCT_LocRotScale
    
    )

target_include_directories(SceneManager PUBLIC ./)