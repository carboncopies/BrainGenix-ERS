########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################



# Specify CPP Files In Source (Name Should Start With Parent Dir Name)
set(NoClip_Sources
    "NoClip.cpp"
)

# Specify Header Files In Source (Name Should Start With Parent Dir Name)
set(NoClip_Headers
    "NoClip.h"
)


# Create Library (Name Should Be Parent Dir Name)
add_library(NoClip ${LoggingSystem_Sources} ${LoggingSystem_Headers} ${BACKWARD_ENABLE})
target_link_libraries(NoClip 
    glm
    )
target_include_directories(NoClip PUBLIC ./)
target_link_libraries(${PROJECT_NAME} NoClip)