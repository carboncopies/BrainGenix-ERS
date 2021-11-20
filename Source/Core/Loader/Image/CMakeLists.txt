########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(Image

            # Add Source Files (.cpp)
            "FileIO.cpp"
            "ImageDecoder.cpp"

            # Add Header Files (.h)
            "FileIO.h"
            "ImageDecoder.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Image
    yaml-cpp
    glm
    glad
    glfw
    )

# Link Internal Libs
target_link_libraries(Image
    NoClip
    LoggingSystem
    )

target_include_directories(Image PUBLIC ./)
target_link_libraries(${PROJECT_NAME} Image)