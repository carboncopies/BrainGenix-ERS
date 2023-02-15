# ERS Superbuild


# Configuration Parameters
set(TARGET_NAME Lucifer)
set(LIB_SOURCE_DIR ${LIB_DIR}/SuperBuild/LuciferIL/LuciferIL)



# First part of two, build the library if we're currently doing so
if (USE_SUPERBUILD)



    # Add To Dependencies
    list (APPEND DEPENDENCIES ThirdParty_${TARGET_NAME})

    # Create External Project
    message(STATUS "Configuring Library ${TARGET_NAME}")
    ExternalProject_Add (
        ThirdParty_${TARGET_NAME}
        SOURCE_DIR ${LIB_SOURCE_DIR}
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/Dependencies/Install/ThirdParty_${TARGET_NAME}/
    )
    message(STATUS "Finished Configuring Library ${TARGET_NAME}")

    message(STATUS "Adding CMake Path Argument")
    list (APPEND EXTRA_CMAKE_ARGS
      -DLuciferIL_DIR=${CMAKE_CURRENT_BINARY_DIR}/Dependencies/Install/ThirdParty_${TARGET_NAME}/  
    )
    message(STATUS "Added CMake Path Argument")

    
# Run second part of build, create target/find library we built in the above superbuild target
else()

    option (${LuciferIL_DIR} "Location Of meshoptimizer Build (Used In Superbuild Process)")

    message(STATUS "Lucifer Install Directory: ${LuciferIL_DIR}")
    FILE(GLOB_RECURSE Includes ${LuciferIL_DIR}*/*.h)
    FILE(GLOB_RECURSE Libs ${LuciferIL_DIR}*/*.a)
    message(STATUS ${Includes})
    add_library(Lucifer ${Includes})
    target_link_libraries(Lucifer ${Libs})
    set_target_properties(Lucifer PROPERTIES LINKER_LANGUAGE CXX)
    target_include_directories(Lucifer PUBLIC ${LuciferIL_DIR}/include)
    target_include_directories(Lucifer PUBLIC ${LIB_DIR}/SuperBuild/LuciferIL/LuciferIL/Third-Party/stb/)
    

endif()