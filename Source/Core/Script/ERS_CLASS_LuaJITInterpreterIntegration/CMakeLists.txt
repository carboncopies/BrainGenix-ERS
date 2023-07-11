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

# Link 3rd Party Libs
target_link_libraries(ERS_CLASS_LuaJITInterpreterIntegration
    ${LUA_LIBRARIES}
    )

# Link Internal Libs
target_link_libraries(ERS_CLASS_LuaJITInterpreterIntegration
    ERS_LoggingSystem
    ERS_STRUCT_Model
    ERS_STRUCT_Light
    ERS_STRUCT_SceneCamera
    )

target_include_directories(ERS_CLASS_LuaJITInterpreterIntegration PUBLIC ./)
target_include_directories(ERS_CLASS_LuaJITInterpreterIntegration PRIVATE ${LUA_INCLUDE_DIR})