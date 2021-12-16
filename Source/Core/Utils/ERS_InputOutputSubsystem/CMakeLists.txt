########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_InputOutputSubsystem

            # Add Source Files (.cpp)
            "ERS_InputOutputSubsystem.cpp"

            # Add Header Files (.h)
            "ERS_InputOutputSubsystem.h"

            ${BACKWARD_ENABLE}
)

set_property(TARGET ERS_InputOutputSubsystem PROPERTY CXX_STANDARD 17)

# Link 3rd Party Libs
target_link_libraries(ERS_InputOutputSubsystem
    yaml-cpp
    )

# Link Internal Libs
target_link_libraries(ERS_InputOutputSubsystem

    ERS_STRUCT_IOData

    LoggingSystem
    )

target_include_directories(ERS_InputOutputSubsystem PUBLIC ./)

