##########################
# Builds Library For ERS #
##########################

option(ENABLE_EGL "Configure EGL support for future off-screen rendering targets" ON)

ERSBuildLogger(${Green} "Configuring EGL Support")
if (ENABLE_EGL AND UNIX AND NOT APPLE)

    find_path(EGL_INCLUDE_DIR NAMES EGL/egl.h)
    find_library(EGL_LIBRARY NAMES EGL)

    if ((NOT EGL_INCLUDE_DIR) OR (NOT EGL_LIBRARY))
        message(FATAL_ERROR "ENABLE_EGL is ON but EGL headers or the EGL library were not found. Install libegl1-mesa-dev or reconfigure with -DENABLE_EGL=OFF.")
    endif()

    add_library(ERS_EGL INTERFACE)
    target_include_directories(ERS_EGL INTERFACE ${EGL_INCLUDE_DIR})
    target_link_libraries(ERS_EGL INTERFACE ${EGL_LIBRARY})

    ERSBuildLogger(${BoldGreen} "Finished Configuring EGL Support")
else()
    ERSBuildLogger(${Yellow} "Skipping EGL Support On This Platform")
endif()
