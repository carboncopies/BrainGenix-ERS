########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_CLASS_ArgumentParser

            # Add Source Files (.cpp)
            "ERS_CLASS_ArgumentParser.cpp"

            # Add Header Files (.h)
            "ERS_CLASS_ArgumentParser.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_CLASS_ArgumentParser PRIVATE
    ERS_CLASS_LoggingSystem
    )

# Link Internal Libs
target_link_libraries(ERS_CLASS_ArgumentParser PRIVATE
    )

target_include_directories(ERS_CLASS_ArgumentParser PUBLIC ./)