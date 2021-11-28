########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################



# Specify CPP Files In Source (Name Should Start With Parent Dir Name)
set(Vertex_Sources
)

# Specify Header Files In Source (Name Should Start With Parent Dir Name)
set(Vertex_Headers
    "Vertex.h"
)


# Create Library (Name Should Be Parent Dir Name)
add_library(Vertex ${LoggingSystem_Sources} ${LoggingSystem_Headers} ${BACKWARD_ENABLE})
target_link_libraries(Vertex
    glm
    )
target_include_directories(Vertex PUBLIC ./)