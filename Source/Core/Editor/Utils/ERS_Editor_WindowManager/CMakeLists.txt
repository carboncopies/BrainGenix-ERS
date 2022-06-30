########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_Editor_WindowManager

            # Add Source Files (.cpp)
            "ERS_Editor_WindowManager.cpp"

            # Add Header Files (.h)
            "ERS_Editor_WindowManager.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_Editor_WindowManager
    )

# Link Internal Libs
target_link_libraries(ERS_Editor_WindowManager
    ERS_CLASS_LoggingSystem
    
    )

target_include_directories(ERS_Editor_WindowManager PUBLIC ./)