########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_STRUCT_OpenGLLogItem

            # Add Source Files (.cpp)
            "ERS_STRUCT_OpenGLLogItem.cpp"

            # Add Header Files (.h)
            "ERS_STRUCT_OpenGLLogItem.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_STRUCT_OpenGLLogItem
    )

# Link Internal Libs
target_link_libraries(ERS_STRUCT_OpenGLLogItem
    )


target_include_directories(ERS_STRUCT_OpenGLLogItem PUBLIC ./)
set_target_properties(ERS_STRUCT_OpenGLLogItem PROPERTIES LINKER_LANGUAGE CXX)