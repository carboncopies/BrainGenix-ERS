########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# NOTE: CMAKE PROJECT NAMES SHOULD BE NAMED WITH THE FOLLOWING CONVENTION
# BG-ERS-{NAME OF HEADER FILE WITHOUT ".h"}


# Specify CPP Files In Source (Name Should Start With Parent Dir Name)
set(LoggingSystem_Sources
    "LoggingSystem.cpp"
)

# Specify Header Files In Source (Name Should Start With Parent Dir Name)
set(LoggingSystem_Headers
    "LoggingSystem.h"
)


# Create Library (Name Should Be Parent Dir Name)
add_library(LoggingSystem ${LoggingSystem_Sources} ${LoggingSystem_Headers})
target_link_libraries(LoggingSystem yaml-cpp)
target_include_directories(LoggingSystem PUBLIC ./)

target_link_libraries(${PROJECT_NAME} LoggingSystem)

