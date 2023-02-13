# ERS Superbuild


# Configuration Parameters
set(TARGET_NAME Assimp)
set(LIB_SOURCE_DIR ${LIB_DIR}/assimp)

# Custom CMAKE For This Lib
# End Custom CMAKE For This Lib


# Add To Dependencies
list (APPEND DEPENDENCIES ThirdParty_${TARGET_NAME})

# Copy To Build Location
# file(COPY "${PROJECT_SOURCE_DIR}/ThirdParty/boost/" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/Dependencies/Source/ep_boost")

# Create External Project
ExternalProject_Add (ThirdParty_${TARGET_NAME}

    SOURCE_DIR ${LIB_SOURCE_DIR}
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}
    STAMP_DIR ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}/Stamp

    BINARY_DIR  = ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}/Build
    INSTALL_DIR = ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}/Build
    LOG_DIR     = ${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}/Logs

    INSTALL_COMMAND ""

    CMAKE_ARGS -DASSIMP_BUILD_ASSIMP_TOOLS:BOOL=OFF
               -DASSIMP_BUILD_ZLIB:BOOL=ON
               -DASSIMP_BUILD_SAMPLES:BOOL=OFF
               -DASSIMP_BUILD_TESTS:BOOL=OFF


)



# ExternalProject_Get_Property(ThirdParty_Assimp install_dir)
# include_directories(${install_dir}/include)


list (APPEND EXTRA_CMAKE_ARGS
  -Dassimp_DIR=${CMAKE_CURRENT_BINARY_DIR}/ThirdParty/${TARGET_NAME}/Build/generated
)