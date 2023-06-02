# ERS Superbuild


# First part of two, build the library if we're currently doing so
if (USE_SUPERBUILD)

    # Configuration Parameters
    set(TARGET_NAME Assimp)
    set(LIB_SOURCE_DIR ${LIB_DIR}/SuperBuild/assimp)

    # Add To Dependencies
    list (APPEND DEPENDENCIES ThirdParty_${TARGET_NAME})

    # Create External Project
    message(STATUS "Configuring Library ${TARGET_NAME}")
    ExternalProject_Add (ThirdParty_${TARGET_NAME}
        SOURCE_DIR ${LIB_SOURCE_DIR}
        CMAKE_ARGS -DASSIMP_BUILD_ASSIMP_TOOLS:BOOL=OFF
                  -DASSIMP_BUILD_ZLIB:BOOL=ON
                  -DASSIMP_BUILD_SAMPLES:BOOL=OFF
                  -DASSIMP_BUILD_TESTS:BOOL=OFF
                  -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/Dependencies/Install/ThirdParty_${TARGET_NAME}/
    )
    message(STATUS "Finished Configuring Library ${TARGET_NAME}")

    message(STATUS "Adding CMake Path Argument")
    list (APPEND EXTRA_CMAKE_ARGS
        -Dassimp_DIR=${CMAKE_CURRENT_BINARY_DIR}/Dependencies/Install/ThirdParty_${TARGET_NAME}/lib/cmake/assimp-5.2/
    )
    message(STATUS "Added CMake Path Argument")


# Run second part of build, create target/find library we built in the above superbuild target
else()

    option (assimp_DIR "Location Of Assimp Configuration File (Used In Superbuild Process)")

    message(STATUS "Assimp Configuration Install Directory: ${assimp_DIR}")
    find_package(assimp REQUIRED)

endif()