

# Configuration Parameters
set(TARGET_NAME FreeImage)
set(THIRD_PARTY_DIR ${LIB_DIR}/FreeImage/FreeImage)


# Add To Dependencies
list (APPEND DEPENDENCIES ThirdParty_${TARGET_NAME})

# Create External Project
ExternalProject_Add (ThirdParty_${TARGET_NAME}

    SOURCE_DIR ${THIRD_PARTY_DIR}
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}

    BINARY_DIR   = ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}/Build
    INSTALL_DIR  = ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}/Build
    LOG_DIR      = ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}/Logs

    INSTALL_COMMAND ""

    # CMAKE_ARGS -DASSIMP_BUILD_ASSIMP_TOOLS:BOOL=OFF
    #            -DASSIMP_BUILD_ZLIB:BOOL=ON
    #            -DASSIMP_BUILD_SAMPLES:BOOL=OFF
    #            -DASSIMP_BUILD_TESTS:BOOL=OFF

)