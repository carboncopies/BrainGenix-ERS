########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################



# Specify CPP Files In Source (Name Should Start With Parent Dir Name)
set(Image_Sources
    "FileIO.cpp"
    "ImageDecoder.cpp"
)

# Specify Header Files In Source (Name Should Start With Parent Dir Name)
set(Image_Headers
    "FileIO.h"
    "ImageDecoder.h"
)


# Create Library (Name Should Be Parent Dir Name)
add_library(Image ${LoggingSystem_Sources} ${LoggingSystem_Headers} ${BACKWARD_ENABLE})
target_link_libraries(Image 
    glm
    )
target_include_directories(Image PUBLIC ./)
target_link_libraries(${PROJECT_NAME} Image)