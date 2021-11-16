########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# NOTE: CMAKE PROJECT NAMES SHOULD BE NAMED WITH THE FOLLOWING CONVENTION
# BG-ERS-{NAME OF HEADER FILE WITHOUT ".h"}
# NOTE: CMAKE LIBRARY NAMES SHOULD BE CREATED BASED ON THE FOLLOWING CONVENTION:
# BG-ERS-LIBRARY-{NAME OF HEADER FILE WITHOUT ".h"}

project (
    "BG-ERS-LoggingSystem"
    LANGUAGES CXX
    )


add_library(BG-ERS-LIBRARY-LoggingSystem ...)


add_executable(LoggingSystem ${PROJECT_SOURCE_DIR}/LoggingSystem.cpp)
target_link_libraries(LoggingSystem BG-ERS-LIBRARY-LoggingSystem)

