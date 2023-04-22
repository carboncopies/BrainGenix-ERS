# ERS Superbuild

# First part of two, build the library if we're currently doing so
if (USE_SUPERBUILD)

    # Configuration Parameters
    set(TARGET_NAME ThreadNamingUtils)
    set(LIB_SOURCE_DIR ${LIB_DIR}/SuperBuild/ThreadNamingUtils)

    # Add To Dependencies
    list (APPEND DEPENDENCIES ThirdParty_${TARGET_NAME})

    # Create External Project
    message(STATUS "Configuring Library ${TARGET_NAME}")
    ExternalProject_Add (ThirdParty_${TARGET_NAME}

        SOURCE_DIR ${LIB_SOURCE_DIR}
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/Dependencies/Install/ThirdParty_${TARGET_NAME}/

    )
    message(STATUS "Finished Configuring Library ${TARGET_NAME}")

    message(STATUS "Adding CMake Path Argument")
    list (APPEND EXTRA_CMAKE_ARGS
      -DThreadNamingUtils_DIR=${CMAKE_CURRENT_BINARY_DIR}/Dependencies/Install/ThirdParty_${TARGET_NAME}/  
    )
    message(STATUS "Added CMake Path Argument")

    
# Run second part of build, create target/find library we built in the above superbuild target
else()

    option (ThreadNamingUtils_DIR "Location Of ThreadNamingUtils Build (Used In Superbuild Process)")

    message(STATUS "ThreadNamingUtils Install Directory: ${ThreadNamingUtils_DIR}")
    FILE(GLOB_RECURSE Includes ${ThreadNamingUtils_DIR}*/*.h)
    FILE(GLOB_RECURSE Libs ${ThreadNamingUtils_DIR}*/*.a)
    message(STATUS ${Includes})
    add_library(ThreadNamingUtils ${Includes})
    target_link_libraries(ThreadNamingUtils ${Libs})
    set_target_properties(ThreadNamingUtils PROPERTIES LINKER_LANGUAGE CXX)
    target_include_directories(ThreadNamingUtils PUBLIC ${ThreadNamingUtils_DIR}/include)

endif()