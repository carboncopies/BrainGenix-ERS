# ERS Superbuild


# Configuration Parameters
set(TARGET_NAME YAMLCPP)
set(LIB_SOURCE_DIR ${LIB_DIR}/SuperBuild/yaml-cpp)



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
      -Dyaml-cpp_DIR=${CMAKE_CURRENT_BINARY_DIR}/Dependencies/Install/ThirdParty_${TARGET_NAME}/  
    )
    message(STATUS "Added CMake Path Argument")

    
# Run second part of build, create target/find library we built in the above superbuild target
else()

    option (${yaml-cpp_DIR} "Location Of meshoptimizer Build (Used In Superbuild Process)")

    message(STATUS "FreeImage Install Directory: ${yaml-cpp_DIR}")
    FILE(GLOB_RECURSE Includes ${yaml-cpp_DIR}*/*.h)
    FILE(GLOB_RECURSE Libs ${yaml-cpp_DIR}*/*.a)
    message(STATUS ${Includes})
    add_library(yaml-cpp ${Includes})
    target_link_libraries(yaml-cpp ${Libs})
    set_target_properties(yaml-cpp PROPERTIES LINKER_LANGUAGE CXX)
    target_include_directories(yaml-cpp PUBLIC ${yaml-cpp_DIR}/include)

endif()