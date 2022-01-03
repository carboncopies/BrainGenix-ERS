########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ProjectLoader

            # Add Source Files (.cpp)
            "ProjectLoader.cpp"

            # Add Header Files (.h)
            "ProjectLoader.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ProjectLoader
    yaml-cpp
    )

# Link Internal Libs
target_link_libraries(ProjectLoader
    ERS_STRUCTURE_IOData
    ERS_STRUCTURE_InputOutputSystem
    )


target_include_directories(ProjectLoader PUBLIC ./)
