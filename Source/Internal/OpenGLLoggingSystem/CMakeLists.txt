########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_OpenGLLoggingSystem

            # Add Source Files (.cpp)
            "ERS_OpenGLLoggingSystem.cpp"
            "ERS_MessageCallbackUserParam.cpp"
            "ERS_OpenGLLogItem.cpp"

            # Add Header Files (.h)
            "ERS_OpenGLLoggingSystem.h"
            "ERS_MessageCallbackUserParam.h"
            "ERS_OpenGLLogItem.h"

            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_OpenGLLoggingSystem
    yaml-cpp
    glad
    )

# Link Internal Libs
target_link_libraries(ERS_OpenGLLoggingSystem
    ERS_LoggingSystem
    )

if (WIN32) 
    ERSBuildLogger(${BoldGreen} "Build Warnings Not Enabled")
else ()
    target_compile_options(ERS_OpenGLLoggingSystem PUBLIC -Wall -Wextra -Wpedantic)
    target_compile_options(ERS_OpenGLLoggingSystem PUBLIC -Werror=uninitialized)
endif()

target_include_directories(ERS_OpenGLLoggingSystem PUBLIC ./)

