

# Configuration Parameters
set(TARGET_NAME FreeImage)
set(PROJECT_SOURCE_DIR ${LIB_DIR}/FreeImage/FreeImage)

# Custom CMAKE For This Lib
file(COPY "${PROJECT_SOURCE_DIR}/Source/" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}/Build")
# End Custom CMAKE For This Lib


# Add To Dependencies
list (APPEND DEPENDENCIES ThirdParty_${TARGET_NAME})

# Create External Project
ExternalProject_Add (ThirdParty_${TARGET_NAME}

    SOURCE_DIR ${PROJECT_SOURCE_DIR}
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}
    STAMP_DIR ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}/Stamp

    BINARY_DIR  = ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}/Build
    INSTALL_DIR = ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}/Build
    LOG_DIR     = ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}/Logs

    INSTALL_COMMAND ""

    CMAKE_ARGS -Wno-dev
            #    -DASSIMP_BUILD_ZLIB:BOOL=ON
            #    -DASSIMP_BUILD_SAMPLES:BOOL=OFF
            #    -DASSIMP_BUILD_TESTS:BOOL=OFF

)


# list (APPEND EXTRA_CMAKE_ARGS
#   -DFreeImage_ROOT=${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}/Build
#   -DFreeImage_INCLUDE=${PROJECT_SOURCE_DIR}/Source
#   -DFreeImage_NO_SYSTEM_PATHS=ON)