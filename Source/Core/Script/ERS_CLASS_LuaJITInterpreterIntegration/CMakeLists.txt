########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_CLASS_LuaJITInterpreterIntegration 

            # Add Source Files (.cpp)
            "ERS_CLASS_LuaJITInterpreterIntegration.cpp"
                        

            # Add Header Files (.h)
            "ERS_CLASS_LuaJITInterpreterIntegration.h"
                        
            ${BACKWARD_ENABLE}
            )

