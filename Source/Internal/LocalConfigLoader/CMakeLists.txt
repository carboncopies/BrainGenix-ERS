########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_LocalConfigLoader

            # Add Source Files (.cpp)
            "LocalConfigLoader.cpp"

            # Add Header Files (.h)
            "LocalConfigLoader.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_LocalConfigLoader
    yaml-cpp
    ghcFilesystem::ghc_filesystem
    sago::platform_folders
    )

# Link Internal Libs
target_link_libraries(ERS_LocalConfigLoader
    ERS_GetExecutablePath
    )

target_include_directories(ERS_LocalConfigLoader PUBLIC ./)