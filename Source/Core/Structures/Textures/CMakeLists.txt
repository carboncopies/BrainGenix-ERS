########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################



# Specify CPP Files In Source (Name Should Start With Parent Dir Name)
set(Texture_Sources
)

# Specify Header Files In Source (Name Should Start With Parent Dir Name)
set(Texture_Headers
    "Mesh.h"
)


# Create Library (Name Should Be Parent Dir Name)
add_library(Texture ${LoggingSystem_Sources} ${LoggingSystem_Headers} ${BACKWARD_ENABLE})
target_link_libraries(Texture
    glm
    )
target_include_directories(Texture PUBLIC ./)
target_link_libraries(${PROJECT_NAME} Texture)