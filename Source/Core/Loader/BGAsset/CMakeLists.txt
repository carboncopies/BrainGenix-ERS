########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################



# Specify CPP Files In Source (Name Should Start With Parent Dir Name)
set(Model_Sources
    "Mesh.cpp"
)

# Specify Header Files In Source (Name Should Start With Parent Dir Name)
set(Model_Headers
    "Mesh.h"
)


# Create Library (Name Should Be Parent Dir Name)
add_library(Model ${LoggingSystem_Sources} ${LoggingSystem_Headers} ${BACKWARD_ENABLE})
target_link_libraries(Model 
    glm
    )
target_include_directories(Model PUBLIC ./)
target_link_libraries(${PROJECT_NAME} Model)