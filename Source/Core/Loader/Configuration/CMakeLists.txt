########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################



# Specify CPP Files In Source (Name Should Start With Parent Dir Name)
set(Configuration_Sources

)

# Specify Header Files In Source (Name Should Start With Parent Dir Name)
set(Configuration_Headers

)


# Create Library (Name Should Be Parent Dir Name)
add_library(Configuration ${LoggingSystem_Sources} ${LoggingSystem_Headers} ${BACKWARD_ENABLE})
target_link_libraries(Configuration 
    glm
    )
target_include_directories(Configuration PUBLIC ./)
target_link_libraries(${PROJECT_NAME} Configuration)