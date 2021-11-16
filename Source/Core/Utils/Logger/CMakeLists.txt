########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# NOTE: CMAKE PROJECT NAMES SHOULD BE NAMED WITH THE FOLLOWING CONVENTION
# BG-ERS-{NAME OF HEADER FILE WITHOUT ".h"}


project (
    "BG-ERS-LoggingSystem"
    LANGUAGES CXX
    )


add_library(BG-ERS-LoggingSystem ${PROJECT_SOURCE_DIR}/LoggingSystem.cpp)


add_executable(LoggingSystem ${PROJECT_SOURCE_DIR}/LoggingSystem.cpp)
target_link_libraries(LoggingSystem BG-ERS-LoggingSystem)

