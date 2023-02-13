# ERS Superbuild


# Configuration Parameters
set(TARGET_NAME OZZ-Animation)
set(LIB_SOURCE_DIR ${LIB_DIR}/ozz-animation)

# Add To Dependencies
list (APPEND DEPENDENCIES ThirdParty_${TARGET_NAME})

# Create External Project
ExternalProject_Add (ThirdParty_${TARGET_NAME}

    SOURCE_DIR ${LIB_SOURCE_DIR}
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}
    STAMP_DIR ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}/Stamp

    BINARY_DIR  = ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}/Build
    INSTALL_DIR = ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}/Build
    LOG_DIR     = ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}/Logs

    # INSTALL_COMMAND ""

    CMAKE_ARGS -DASSIMP_BUILD_ASSIMP_TOOLS:BOOL=OFF
               -DASSIMP_BUILD_ZLIB:BOOL=ON
               -DASSIMP_BUILD_SAMPLES:BOOL=OFF
               -DASSIMP_BUILD_TESTS:BOOL=OFF
               -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}/Install


)

list (APPEND EXTRA_CMAKE_ARGS
  -Dassimp_DIR=${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}/Install/lib/cmake/assimp-5.2/
)