########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################



# Specify CPP Files In Source (Name Should Start With Parent Dir Name)
set(Scene_Sources
    "SceneDecoder.cpp"
)

# Specify Header Files In Source (Name Should Start With Parent Dir Name)
set(Scene_Headers
    "SceneDecoder.h"
)


# Create Library (Name Should Be Parent Dir Name)
add_library(Scene ${LoggingSystem_Sources} ${LoggingSystem_Headers} ${BACKWARD_ENABLE})
target_link_libraries(Scene 
    glm
    )
target_include_directories(Scene PUBLIC ./)
target_link_libraries(${PROJECT_NAME} Scene)