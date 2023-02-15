# ERS Superbuild


# Configuration Parameters
set(TARGET_NAME FreeImage)
set(LIB_SOURCE_DIR ${LIB_DIR}/SuperBuild/FreeImage/FreeImage)



# First part of two, build the library if we're currently doing so
if (USE_SUPERBUILD)



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
      -DFreeImage_DIR=${CMAKE_CURRENT_BINARY_DIR}/Dependencies/Install/ThirdParty_${TARGET_NAME}/  
    )
    message(STATUS "Added CMake Path Argument")

    
# Run second part of build, create target/find library we built in the above superbuild target
else()

    option (${FreeImage_DIR} "Location Of meshoptimizer Build (Used In Superbuild Process)")

    message(STATUS "FreeImage Install Directory: ${FreeImage_DIR}")
    FILE(GLOB_RECURSE Includes ${FreeImage_DIR}*/*.h)
    FILE(GLOB_RECURSE Libs ${FreeImage_DIR}*/*.a)
    add_library(FreeImage ${Includes})
    target_link_libraries(FreeImage ${Libs})
    set_target_properties(FreeImage PROPERTIES LINKER_LANGUAGE CXX)
    target_include_directories(FreeImage PUBLIC ${FreeImage_DIR}/include)

endif()


# FreeImage's CMakeLists Has Been Modified As Stated Below
# ### ++ MODIFIED BY ERS TEAM FOR SUPERBUILDS ++ ###

# FILE(GLOB Includes ${CMAKE_CURRENT_SOURCE_DIR}/Source/*.h)
# install(TARGETS ${PROJECT_NAME})
# install(FILES ${Includes} DESTINATION include)

# ### ++ END MODIFICATIONS ++ ###