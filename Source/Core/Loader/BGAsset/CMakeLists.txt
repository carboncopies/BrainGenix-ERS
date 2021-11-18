########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################



# Specify CPP Files In Source (Name Should Start With Parent Dir Name)
set(BGAsset_Sources
    "BGAssetManager.cpp"
)

# Specify Header Files In Source (Name Should Start With Parent Dir Name)
set(BGAsset_Headers
    "BGAssetManager.h"
)


# Create Library (Name Should Be Parent Dir Name)
add_library(BGAsset ${LoggingSystem_Sources} ${LoggingSystem_Headers} ${BACKWARD_ENABLE})
target_link_libraries(BGAsset 
    glm
    )
target_include_directories(BGAsset PUBLIC ./)
target_link_libraries(${PROJECT_NAME} BGAsset)