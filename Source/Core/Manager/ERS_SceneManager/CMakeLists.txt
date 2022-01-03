########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_SceneManager

            # Add Source Files (.cpp)
            "ERS_SceneManager.cpp"

            # Add Header Files (.h)
            "ERS_SceneManager.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_SceneManager
    yaml-cpp
    )

# Link Internal Libs
target_link_libraries(ERS_SceneManager
    Scene
    LoggingSystem
    ERS_STRUCT_LocRotScale
    
    )

target_include_directories(ERS_SceneManager PUBLIC ./)