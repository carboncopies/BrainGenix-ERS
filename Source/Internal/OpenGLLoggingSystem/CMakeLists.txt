########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_OpenGLLoggingSystem

            # Add Source Files (.cpp)
            "OpenGLLoggingSystem.cpp"
            "MessageCallbackUserParam.cpp"
            "OpenGLLogItem.cpp"

            # Add Header Files (.h)
            "OpenGLLoggingSystem.h"
            "MessageCallbackUserParam.h"
            "OpenGLLogItem.h"

            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_OpenGLLoggingSystem
    yaml-cpp
    glad
    )

# Link Internal Libs
target_link_libraries(ERS_OpenGLLoggingSystem
    bg-common-logger
    )

target_include_directories(ERS_OpenGLLoggingSystem PUBLIC ./)
