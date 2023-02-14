# ERS Superbuild


# First part of two, build the library if we're currently doing so
if (USE_SUPERBUILD)

    # Configuration Parameters
    set(TARGET_NAME OZZ-Animation)
    set(LIB_SOURCE_DIR ${LIB_DIR}/SuperBuild/ozz-animation)

    # Add To Dependencies
    list (APPEND DEPENDENCIES ThirdParty_${TARGET_NAME})

    # Create External Project
    message(STATUS "Configuring Library ${TARGET_NAME}")
    ExternalProject_Add (ThirdParty_${TARGET_NAME}

        SOURCE_DIR ${LIB_SOURCE_DIR}
        # PREFIX ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}

        # STAMP_DIR   = ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}/Stamp
        # BINARY_DIR  = ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}/Build
        # INSTALL_DIR = ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}/Install
        # LOG_DIR     = ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}/Logs

        # INSTALL_COMMAND ""

        CMAKE_ARGS -Dozz_build_tools:BOOL=OFF
                  -Dozz_build_samples:BOOL=OFF
                  -Dozz_build_howtos:BOOL=OFF
                  -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/Dependencies/Install/ThirdParty_${TARGET_NAME}/


    )
    message(STATUS "Finished Configuring Library ${TARGET_NAME}")

    message(STATUS "Adding CMake Path Argument")
    list (APPEND EXTRA_CMAKE_ARGS
      -Dozz-animation_DIR=${CMAKE_CURRENT_BINARY_DIR}/Dependencies/Install/ThirdParty_${TARGET_NAME}/  
    )
    message(STATUS "Added CMake Path Argument")


# Run second part of build, create target/find library we built in the above superbuild target
else()

    option (ozz-animation_DIR "Location Of OZZAnimation Build (Used In Superbuild Process)")

    message(STATUS "OZZ-Animation Install Directory: ${ozz-animation_DIR}")
    FILE(GLOB_RECURSE OZZAnimationIncludes ${ozz-animation_DIR}*/*.h)
    FILE(GLOB_RECURSE OZZAnimationLibs ${ozz-animation_DIR}*/*.so)
    add_library(ozz_animation ${OZZAnimationIncludes})
    target_link_libraries(ozz_animation ${OZZAnimationLibs})
    set_target_properties(ozz_animation PROPERTIES LINKER_LANGUAGE CXX)

endif()