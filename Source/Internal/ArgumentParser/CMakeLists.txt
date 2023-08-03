########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_ArgumentParser

            # Add Source Files (.cpp)
            "ArgumentParser.cpp"

            # Add Header Files (.h)
            "ArgumentParser.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_ArgumentParser
    bg-common-logger
    )

# Link Internal Libs
target_link_libraries(ERS_ArgumentParser
    )

target_include_directories(ERS_ArgumentParser PUBLIC ./)