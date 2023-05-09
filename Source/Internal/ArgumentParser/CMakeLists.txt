########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################

# Configure Library Settings (MAINTAINERS: EDIT THIS SECTION)
set(LIBRARY_NAME "ERS_ArgumentParser")
set(LIB_SOURCE_FILES 
    "ArgumentParser.cpp"
    "ArgumentParser.h"
)
set(LIB_TEST_SOURCE_FILES
    "ArgumentParserTest.cpp"
    "ArgumentParserTest.h"
)
set(LIB_LINKS
    ERS_LoggingSystem
)



# Create Library
add_library(${LIBRARY_NAME} ${LIB_SOURCE_FILES} ${BACKWARD_ENABLE})
target_link_libraries(${LIBRARY_NAME} ${LIB_LINKS})
target_include_directories(${LIBRARY_NAME} PUBLIC ./)

# Run Tests IF Tests Enabled
if (${BG_ENABLE_TESTS})
    message(STATUS "Setting Up Unit Tests For ${LIBRARY_NAME}")

    # Enable Testing For this Lib
    # cmake docs are awful on this, it implies recursion but you need to do it manually
    enable_testing()
    include(GoogleTest)

    # Set Name of test executable
    set(LIBRARY_TEST_EXECUTABLE "${LIBRARY_NAME}-Test")
    set(BG_TEST_EXECUTABLES ${BG_TEST_EXECUTABLES} ${LIBRARY_TEST_EXECUTABLE} PARENT_SCOPE)
    message(STATUS "Created Unit Test Executable ${LIBRARY_TEST_EXECUTABLE}")
    message("${CMAKE_CURRENT_BINARY_DIR}")

    # Add Executable with that name, set include dirs, and link to our library to test as well as gtests
    add_executable(${LIBRARY_TEST_EXECUTABLE} ${LIB_TEST_SOURCE_FILES})
    target_include_directories(${LIBRARY_TEST_EXECUTABLE} PUBLIC ./)
    target_link_libraries(${LIBRARY_TEST_EXECUTABLE} ${LIBRARY_NAME} GTest::gtest_main )

    # Discover tests
    gtest_discover_tests(${LIBRARY_TEST_EXECUTABLE})

endif()
