########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_IOTypeIdentiifer

            # Add Source Files (.cpp)
            "ERS_CLASS_IOTypeIdentifier.cpp"

            # Add Header Files (.h)
            "ERS_CLASS_IOTypeIdentifier.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(IOTypeIdentifier
    yaml-cpp
    )

# Link Internal Libs
target_link_libraries(IOTypeIdentifier

    LoggingSystem

    )

target_include_directories(IOTypeIdentifier PUBLIC ./)