###################################################
# Builds Monado's Prerequisites And Monado Itself #
###################################################

## GLSLang tools needs to be here! (glslang-validator?)

## Ideally, Eigen would be built in the project too



if (WIN32)
    ERSBuildLogger(${Yellow} "VR Support Disabled On Windows, Use Linux. The Monado Runtime Doesn't Support Windows")
else()
    ERSBuildLogger(${Green} "Configuring Monado OpenXR Runtime")
    add_subdirectory(${LIB_DIR}/monado)
    ERSBuildLogger(${Green} "Finished Configuring Monado OpenXR Runtime")
endif()
