# ERS Superbuild

# First part of two, build the library if we're currently doing so
if (USE_SUPERBUILD)

    # Configuration Parameters
    set(TARGET_NAME LuaJIT)
    set(LIB_SOURCE_DIR ${LIB_DIR}/SuperBuild/LuaJIT)

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
      -DLuaJIT_DIR=${CMAKE_CURRENT_BINARY_DIR}/Dependencies/Install/ThirdParty_${TARGET_NAME}/  
    )
    message(STATUS "Added CMake Path Argument")

    
# Run second part of build, create target/find library we built in the above superbuild target
else()

    option (LuaJIT_DIR "Location Of LuaJIT Build (Used In Superbuild Process)")

    message(STATUS "LuaJIT Install Directory: ${LuaJIT_DIR}")
    FILE(GLOB_RECURSE Includes ${LuaJIT_DIR}*/*.h)
    FILE(GLOB_RECURSE Libs ${LuaJIT_DIR}*/*.a)
    message(STATUS ${Includes})
    add_library(LuaJIT ${Includes})
    target_link_libraries(LuaJIT ${Libs})
    set_target_properties(LuaJIT PROPERTIES LINKER_LANGUAGE CXX)
    target_include_directories(LuaJIT PUBLIC ${LuaJIT_DIR}/include)

endif()