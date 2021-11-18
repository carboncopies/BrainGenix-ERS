########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################



# Specify CPP Files In Source (Name Should Start With Parent Dir Name)
set(ModelLoader_Sources
    "ModelDecoder.cpp"
)

# Specify Header Files In Source (Name Should Start With Parent Dir Name)
set(ModelLoader_Headers
    "ModelDecoder.h"
)


# Create Library (Name Should Be Parent Dir Name)
add_library(ModelLoader ${LoggingSystem_Sources} ${LoggingSystem_Headers} ${BACKWARD_ENABLE})
target_link_libraries(ModelLoader
    glm
    )
target_include_directories(ModelLoader PUBLIC ./)
target_link_libraries(${PROJECT_NAME} ModelLoader)