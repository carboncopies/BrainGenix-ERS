########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################



# Specify CPP Files In Source (Name Should Start With Parent Dir Name)
set(AssetLoaderQueue_Sources
    "AssetLoaderQueue.cpp"
)

# Specify Header Files In Source (Name Should Start With Parent Dir Name)
set(AssetLoaderQueue_Headers
    "AssetLoaderQueue.h"
)


# Create Library (Name Should Be Parent Dir Name)
add_library(AssetLoaderQueue ${LoggingSystem_Sources} ${LoggingSystem_Headers} ${BACKWARD_ENABLE})
target_link_libraries(AssetLoaderQueue 
    yaml-cpp
    glm
    glad
    glfw
    )
target_include_directories(AssetLoaderQueue PUBLIC ./)
target_link_libraries(${PROJECT_NAME} AssetLoaderQueue)