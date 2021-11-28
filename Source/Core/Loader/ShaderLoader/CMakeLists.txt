########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ShaderLoader

            # Add Source Files (.cpp)
            "ShaderLoader.cpp"

            # Add Header Files (.h)
            "ShaderLoader.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ShaderLoader
    )

# Link Internal Libs
target_link_libraries(ShaderLoader
    )

target_include_directories(ShaderLoader PUBLIC ./)
target_link_libraries(${PROJECT_NAME} ShaderLoader)

