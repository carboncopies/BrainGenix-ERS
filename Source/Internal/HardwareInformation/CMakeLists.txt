########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_HardwareInformation

            # Add Source Files (.cpp)
            "HardwareInformation.cpp"

            # Add Header Files (.h)
            "HardwareInformation.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_HardwareInformation
    infoware
    ThreadNamingUtils
    ${CMAKE_THREAD_LIBS_INIT}
    )

# Link Internal Libs
target_link_libraries(ERS_HardwareInformation

    bg-common-logger

    ERS_STRUCT_HardwareInfo

    )

target_include_directories(ERS_HardwareInformation PUBLIC ./)
