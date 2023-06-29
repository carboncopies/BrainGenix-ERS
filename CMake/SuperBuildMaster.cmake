# Superbuild Main Runner

# Setup System
include (ExternalProject)

set_property (DIRECTORY PROPERTY EP_BASE Dependencies)

set (DEPENDENCIES)
set (EXTRA_CMAKE_ARGS)


# Include Superbuilds
include(${CMAKE_UTILS_DIR}/SuperBuilds/OZZAnimation.cmake)
include(${CMAKE_UTILS_DIR}/SuperBuilds/Lucifer.cmake)
include(${CMAKE_UTILS_DIR}/SuperBuilds/LuaJIT.cmake)
include(${CMAKE_UTILS_DIR}/SuperBuilds/ERS.cmake)

