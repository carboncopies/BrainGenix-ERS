########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(Model 

            # Add Source Files (.cpp)
            "Scene.cpp"

            # Add Header Files (.h)
            "Scene.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Model
    yaml-cpp
    )

# Link Internal Libs
target_link_libraries(Model
    )

target_include_directories(Model PUBLIC ./)
target_link_libraries(${PROJECT_NAME} Model)