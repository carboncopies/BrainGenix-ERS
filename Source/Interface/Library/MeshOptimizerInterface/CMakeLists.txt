########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_MeshOptimizer

            # Add Source Files (.cpp)
            "MeshOptimizer.cpp"

            # Add Header Files (.h)
            "MeshOptimizer.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_MeshOptimizer
    meshoptimizer
    )

# Link Internal Libs
target_link_libraries(ERS_MeshOptimizer
    ERS_LoggingSystem
    )

target_include_directories(ERS_MeshOptimizer PUBLIC ./)