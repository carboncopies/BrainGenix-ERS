########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_InputOutputSubsystem

            # Add Source Files (.cpp)
            "InputOutputSubsystem.cpp"
            "AssetIndexInputOutputManager.cpp"
            "CompareAssetIndexDelta.cpp"

            # Add Header Files (.h)
            "InputOutputSubsystem.h"
            "AssetIndexInputOutputManager.h"
            "CompareAssetIndexDelta.h"

            ${BACKWARD_ENABLE}
)

set_property(TARGET ERS_InputOutputSubsystem PROPERTY CXX_STANDARD 17)

# Link 3rd Party Libs
target_link_libraries(ERS_InputOutputSubsystem
    yaml-cpp
    ghcFilesystem::ghc_filesystem
    )

# Link Internal Libs
target_link_libraries(ERS_InputOutputSubsystem
    bg-common-logger
    ERS_STRUCT_IOData
    )

target_include_directories(ERS_InputOutputSubsystem PUBLIC ./)

