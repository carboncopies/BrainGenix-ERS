########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ImageLoader

            # Add Source Files (.cpp)
            "FileIO.cpp"
            "ImageDecoder.cpp"

            # Add Header Files (.h)
            "FileIO.h"
            "ImageDecoder.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ImageLoader
    yaml-cpp
    glm
    glad
    glfw
    )

# Link Internal Libs
target_link_libraries(ImageLoader
    NoClip
    LoggingSystem
    )

target_include_directories(ImageLoader PUBLIC ./)
target_link_libraries(${PROJECT_NAME} ImageLoader)