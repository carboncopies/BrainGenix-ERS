########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_STRUCT_EditorCamera 

            # Add Source Files (.cpp)
            "ERS_STRUCT_EditorCamera.cpp"

            # Add Header Files (.h)
            "ERS_STRUCT_EditorCamera.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_STRUCT_EditorCamera
    glm
    glad
    )

# Link Internal Libs
target_link_libraries(ERS_STRUCT_EditorCamera
    ERS_STRUCT_Camera
    )

target_include_directories(ERS_STRUCT_EditorCamera PUBLIC ./)