###################################################
# Builds Monado's Prerequisites And Monado Itself #
###################################################

## GLSLang tools needs to be here! (glslang-validator?)

## Ideally, Eigen would be built in the project too



if (WIN32)
  message("VR Support Disabled On Windows, Use Linux. The Monado Runtime Doesn't Support Windows")
else()
  message("[ERS BUILD SYSTEM] Building Monado OpenXR Runtime")
  add_subdirectory(${LIB_DIR}/monado)
endif()
