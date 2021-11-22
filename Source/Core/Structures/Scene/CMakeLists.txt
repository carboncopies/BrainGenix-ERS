########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(Scene

            # Add Source Files (.cpp)
            #"Scene.cpp"

            # Add Header Files (.h)
            "Scene.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Scene
    yaml-cpp
    )

# Link Internal Libs
target_link_libraries(Scene
    )

target_include_directories(Scene PUBLIC ./)
target_link_libraries(${PROJECT_NAME} Scene)