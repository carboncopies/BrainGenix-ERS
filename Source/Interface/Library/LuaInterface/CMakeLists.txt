########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_LuaInterface

            # Add Source Files (.cpp)
            "ERS_LuaInterface.cpp"

            # Add Header Files (.h)
            "ERS_LuaInterface.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_LuaInterface
    LuaJIT
    )

# Link Internal Libs
target_link_libraries(ERS_LuaInterface
    ERS_LoggingSystem
    )

target_include_directories(ERS_LuaInterface PUBLIC ./)