########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_CompileTimeInfo

            # Add Source Files (.cpp)
            "ERS_CompileTimeInfo.cpp"

            # Add Header Files (.h)
            "ERS_CompileTimeInfo.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_CompileTimeInfo
    
    )

# Link Internal Libs
target_link_libraries(ERS_CompileTimeInfo
    
    )

target_include_directories(ERS_CompileTimeInfo PUBLIC ./)