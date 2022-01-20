########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_AssetIndexLoader

            # Add Source Files (.cpp)
            "ERS_CLASS_AssetIndexLoader.cpp"

            # Add Header Files (.h)
            "ERS_CLASS_AssetIndexLoader.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_AssetIndexLoader
    yaml-cpp
    )

# Link Internal Libs
target_link_libraries(ERS_AssetIndexLoader
    LoggerClass
    ERS_STRUCT_IOData
    )


target_include_directories(ERS_AssetIndexLoader PUBLIC ./)
