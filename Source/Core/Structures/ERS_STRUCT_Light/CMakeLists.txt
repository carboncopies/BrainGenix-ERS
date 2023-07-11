########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_STRUCT_Light

            # Add Source Files (.cpp)
            "SpotLight.cpp"
            "PointLight.cpp"
            "DirectionalLight.cpp"

            # Add Header Files (.h)
            "SpotLight.h"
            "PointLight.h"
            "DirectionalLight.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_STRUCT_Light
    glm
    )

# Link Internal Libs
target_link_libraries(ERS_STRUCT_Light
    ERS_STRUCT_DepthMap
    )

target_include_directories(ERS_STRUCT_Light PUBLIC ./)