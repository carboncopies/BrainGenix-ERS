###################################################
# Builds Monado's Prerequisites And Monado Itself #
###################################################

## GLSLang tools needs to be here! (glslang-validator?)

## Ideally, Eigen would be built in the project too



if (WIN32)
    ERSBuildLogger(${Yellow} "VR Support Disabled On Windows, Use Linux. The Monado Runtime Doesn't Support Windows")
else()

    # Handle Deps
    ERSBuildLogger(${Green} "Configuring Monado Dependencies")

    # Eigen
    ERSBuildLogger(${Green} "Configuring Eigen Library")
    set(EIGEN3_INCLUDE_DIR ${LIB_DIR}/eigen)
    ERSBuildLogger(${BoldGreen} "Finished Configuring Eigen Library")

    # HIDAPI
    ERSBuildLogger(${Green} "Configuring HIDAPI Library")
    set(HIDAPI_INCLUDE_DIR ${LIB_DIR}/hidapi/hidapi)
    set(HIDAPI_LIBRARY ${LIB_DIR}/hidapi/linux)
    ERSBuildLogger(${BoldGreen} "Finished Configuring HID Library")

    # OpenHMD
    ERSBuildLogger(${Green} "Configuring OpenHMD Library")
    set(OPENHMD_ROOT_DIR ${LIB_DIR}/OpenHMD)
    set(OPENHMD_LIBRARY ${LIB_DIR}/OpenHMD)
    ERSBuildLogger(${BoldGreen} "Finished Configuring OpenHMD Library")


    ERSBuildLogger(${BoldGreen} "Finished Configuring Monado Dependencies")

    # Build Monado
    ERSBuildLogger(${Green} "Configuring Monado OpenXR Runtime")
    add_subdirectory(${LIB_DIR}/monado)
    ERSBuildLogger(${BoldGreen} "Finished Configuring Monado OpenXR Runtime")

endif()
