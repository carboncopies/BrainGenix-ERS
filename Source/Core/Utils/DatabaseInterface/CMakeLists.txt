########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(DatabaseInterface

            # Add Source Files (.cpp)
            "DatabaseInterface.cpp"

            # Add Header Files (.h)
            "DatabaseInterface.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(DatabaseInterface

    )

# Link Internal Libs
target_link_libraries(DatabaseInterface

    LoggingSystem

    )

target_include_directories(DatabaseInterface PUBLIC ./)