# ERS Superbuild


# Add To Dependencies
list (APPEND DEPENDENCIES ThirdParty_Assimp)

# Create External Project
ExternalProject_Add (ThirdParty_Assimp

    SOURCE_DIR ${LIB_DIR}/assimp
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/Assimp

    BINARY_DIR   = ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/Assimp/Build
    INSTALL_DIR  = ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/Assimp/Build
    LOG_DIR      = ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/Assimp/Logs

    INSTALL_COMMAND ""

    CMAKE_ARGS -DASSIMP_BUILD_ASSIMP_TOOLS:BOOL=OFF
               -DASSIMP_BUILD_ZLIB:BOOL=ON
               -DASSIMP_BUILD_SAMPLES:BOOL=OFF
               -DASSIMP_BUILD_TESTS:BOOL=OFF

)

# ExternalProject_Get_Property(ThirdParty_Assimp install_dir)
# include_directories(${install_dir}/include)


# list (APPEND EXTRA_CMAKE_ARGS
#   -DBOOST_ROOT=${CMAKE_CURRENT_BINARY_DIR}/Dependencies/Source/ep_boost
#   -DBoost_NO_SYSTEM_PATHS=ON)