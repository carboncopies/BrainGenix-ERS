########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################



# Specify CPP Files In Source (Name Should Start With Parent Dir Name)
set(DataBuffer_Sources
    "DataBuffer.cpp"
)

# Specify Header Files In Source (Name Should Start With Parent Dir Name)
set(DataBuffer_Headers
    "DataBuffer.h"
)


# Create Library (Name Should Be Parent Dir Name)
add_library(DataBuffer ${LoggingSystem_Sources} ${LoggingSystem_Headers} ${BACKWARD_ENABLE})
target_link_libraries(DataBuffer 
    yaml-cpp
    glm
    glad
    glfw
    )
target_include_directories(DataBuffer PUBLIC ./)
target_link_libraries(${PROJECT_NAME} DataBuffer)