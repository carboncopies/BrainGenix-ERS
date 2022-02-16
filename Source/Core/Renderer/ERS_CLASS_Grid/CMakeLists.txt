########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_CLASS_Grid

            # Add Source Files (.cpp)
            "ERS_CLASS_Grid.cpp"

            # Add Header Files (.h)
            "ERS_CLASS_Grid.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_CLASS_Grid
    glm
    glad
    glfw
    )

# Link Internal Libs
target_link_libraries(ERS_CLASS_Grid
    ERS_STRUCT_SystemUtils
    ERS_STRUCT_Shader
    )

target_include_directories(ERS_CLASS_Grid PUBLIC ./)
