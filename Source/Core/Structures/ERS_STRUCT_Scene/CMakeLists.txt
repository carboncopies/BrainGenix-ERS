########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_STRUCT_Scene

            # Add Source Files (.cpp)
            "Scene.cpp"
            "SceneSorter.cpp"

            # Add Header Files (.h)
            "Scene.h"
            "SceneSorter.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_STRUCT_Scene
    yaml-cpp
    )

# Link Internal Libs
target_link_libraries(ERS_STRUCT_Scene
    ERS_STRUCT_Model
    ERS_STRUCT_Light
    ERS_STRUCT_SceneObject
    ERS_STRUCT_SceneCamera
    ERS_STRUCT_Camera
    )

target_include_directories(ERS_STRUCT_Scene PUBLIC ./)
