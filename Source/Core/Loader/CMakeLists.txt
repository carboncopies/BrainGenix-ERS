########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################



# Specify CPP Files In Source (Name Should Start With Parent Dir Name)
set(AssetLoader_Sources
    "AssetLoader.cpp"
)

# Specify Header Files In Source (Name Should Start With Parent Dir Name)
set(AssetLoader_Headers
    "AssetLoader.h"
)


# Create Library (Name Should Be Parent Dir Name)
add_library(Loader ${LoggingSystem_Sources} ${LoggingSystem_Headers} ${BACKWARD_ENABLE})
target_link_libraries(Loader 
    yaml-cpp
    )
target_include_directories(Loader PUBLIC ./)
target_link_libraries(${PROJECT_NAME} Loader)

