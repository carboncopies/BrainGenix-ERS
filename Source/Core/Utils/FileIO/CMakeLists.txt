########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(FileIO

            # Add Source Files (.cpp)
            "FileIO.cpp"

            # Add Header Files (.h)
            "FileIO.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(FileIO

    )

# Link Internal Libs
target_link_libraries(FileIO

    LoggingSystem

    )

target_include_directories(FileIO PUBLIC ./)