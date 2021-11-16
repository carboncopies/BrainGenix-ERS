########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# NOTE: CMAKE PROJECT NAMES SHOULD BE NAMED WITH THE FOLLOWING CONVENTION
# BG-ERS-{NAME OF HEADER FILE WITHOUT ".h"}


# Specify Include Path (Should Match Location In Source Tree)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/Core/Utils/Logger)


# Specify CPP Files In Source
set(Logger_Sources
    "LoggingSystem.cpp"
)

# Specify Header Files In Source
set(Logger_Headers
    "LoggingSystem.h"
)
