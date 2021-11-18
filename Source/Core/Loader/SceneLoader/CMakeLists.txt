########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################



# Specify CPP Files In Source (Name Should Start With Parent Dir Name)
set(SceneLoader_Sources
    "SceneDecoder.cpp"
)

# Specify Header Files In Source (Name Should Start With Parent Dir Name)
set(SceneLoader_Headers
    "SceneDecoder.h"
)


# Create Library (Name Should Be Parent Dir Name)
add_library(SceneLoader ${LoggingSystem_Sources} ${LoggingSystem_Headers} ${BACKWARD_ENABLE})
target_link_libraries(SceneLoader
    glm
    )
target_include_directories(SceneLoader PUBLIC ./)
target_link_libraries(${PROJECT_NAME} SceneLoader)