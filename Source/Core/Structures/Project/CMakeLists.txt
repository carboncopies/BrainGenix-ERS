########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(Project

            # Add Source Files (.cpp)

            # Add Header Files (.h)
            "Project.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Project
    )

# Link Internal Libs
target_link_libraries(Project
    )


target_include_directories(Project PUBLIC ./)
