########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_Editor_ImportAsset

            # Add Source Files (.cpp)
            "ERS_Editor_ImportAsset.cpp"

            # Add Header Files (.h)
            "ERS_Editor_ImportAsset.h"
            
            ${BACKWARD_ENABLE}
            )
set_property(TARGET ERS_Editor_ImportAsset PROPERTY CXX_STANDARD 17)
            
# Link 3rd Party Libs
target_link_libraries(ERS_Editor_ImportAsset
    yaml-cpp
    IMGUI
    )

# Link Internal Libs
target_link_libraries(ERS_Editor_ImportAsset
    LoggingSystem
    )

target_include_directories(ERS_Editor_ImportAsset PUBLIC ./)