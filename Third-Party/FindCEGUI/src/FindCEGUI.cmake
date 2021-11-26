# The original code for this file is by Andreas Schneider (mail@cynapses.org)
# and was published under the New BSD license (it was a FindIrrlicht.cmake
# file).
#
# - Try to find CEGUI
# Once done this will define
#
#  CEGUI_FOUND - system has CEGUI
#  CEGUI_INCLUDE_DIRS - the CEGUI include directory
#  CEGUI_LIBRARIES - Link these to use CEGUI
#  CEGUI_DEFINITIONS - Compiler switches required for using CEGUI
#
#  Copyright (c) 2016 Nicolás A. Ortega <nicolas.ortega.froysa@gmail.com>
#
#  Redistribution and use is allowed according to the terms of the GNU GPLv3
#  license.
#


if (CEGUI_LIBRARIES AND CEGUI_INCLUDE_DIRS)
    # in cache already
    set(CEGUI_FOUND TRUE)
else (CEGUI_LIBRARIES AND CEGUI_INCLUDE_DIRS)
    find_path(CEGUI_INCLUDE_DIR
        NAMES
            CEGUI
        PATHS
            /usr/include
            /usr/include/CEGUI
            /usr/include/cegui-0
            /usr/include/cegui-0.7.6
            /usr/include/cegui-0.8.4
            /usr/local/include
            /usr/local/include/CEGUI
            /usr/local/include/cegui-0
            /usr/local/include/cegui-0.7.6
            /usr/local/include/cegui-0.8.4
            /usr/local/include/cegui-0.8.7
            /usr/include/x86_64-linux-gnu/cegui-0.8.7/
            /opt/local/include
            /sw/include
    )

    find_library(CEGUI_LIBRARY
        NAMES
            CEGUIBase
            CEGUIBase-0
            CEGUIBase-0.7.6
            CEGUIBase-0.8.4
            CEGUIBase-0.8.7

        PATHS
            /usr/lib
            /usr/local/lib
            /opt/local/lib
            /sw/lib
    )

    if (CEGUI_LIBRARY)
        set(CEGUI_FOUND TRUE)
    endif (CEGUI_LIBRARY)

    set(CEGUI_INCLUDE_DIRS
        ${CEGUI_INCLUDE_DIR}
    )

    if (CEGUI_FOUND)
        set(CEGUI_LIBRARIES
            ${CEGUI_LIBRARIES}
            ${CEGUI_LIBRARY}
        )
    endif (CEGUI_FOUND)

    if (CEGUI_INCLUDE_DIRS AND CEGUI_LIBRARIES)
        set(CEGUI_FOUND TRUE)
    endif (CEGUI_INCLUDE_DIRS AND CEGUI_LIBRARIES)

    if (CEGUI_FOUND)
        if (NOT CEGUI_FIND_QUIETLY)
            message(STATUS "Found CEGUI: ${CEGUI_LIBRARIES}")
        endif (NOT CEGUI_FIND_QUIETLY)
    else (CEGUI_FOUND)
        if (CEGUI_FIND_REQUIRED)
            message(FATAL_ERROR "Could not find CEGUI")
        endif (CEGUI_FIND_REQUIRED)
    endif (CEGUI_FOUND)
    # Show the CEGUI_INCLUDE_DIRS and CEGUI_LIBRARIES variables only in the
    # advanced view
    mark_as_advanced(CEGUI_INCLUDE_DIRS CEGUI_LIBRARIES)

endif (CEGUI_LIBRARIES AND CEGUI_INCLUDE_DIRS)
