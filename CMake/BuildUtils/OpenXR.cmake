#############################
# Builds OpenXR Integration #
#############################

ERSBuildLogger(${Green} "Configuring OpenXR Support")
option(ENABLE_OPENXR "Build ERS with OpenXR loader/header plumbing for future XR integration" OFF)

add_library(ERS_OpenXR INTERFACE)

if (ENABLE_OPENXR)
    find_package(OpenXR CONFIG QUIET)
    if ((NOT TARGET OpenXR::openxr_loader) AND (NOT TARGET OpenXR::headers) AND (NOT TARGET OpenXR::Loader))
        find_package(OpenXR QUIET COMPONENTS loader headers)
    endif()

    if ((NOT TARGET OpenXR::openxr_loader) AND TARGET OpenXR::Loader)
        add_library(OpenXR::openxr_loader INTERFACE IMPORTED)
        set_target_properties(OpenXR::openxr_loader PROPERTIES
            INTERFACE_LINK_LIBRARIES "OpenXR::Loader")
    endif()

    if ((NOT TARGET OpenXR::headers) AND TARGET OpenXR::Headers)
        add_library(OpenXR::headers INTERFACE IMPORTED)
        set_target_properties(OpenXR::headers PROPERTIES
            INTERFACE_LINK_LIBRARIES "OpenXR::Headers")
    endif()

    if (TARGET OpenXR::openxr_loader)
        target_link_libraries(ERS_OpenXR INTERFACE OpenXR::openxr_loader)
        if (TARGET OpenXR::headers)
            target_link_libraries(ERS_OpenXR INTERFACE OpenXR::headers)
        endif()
        target_compile_definitions(ERS_OpenXR INTERFACE ERS_ENABLE_OPENXR)
        ERSBuildLogger(${Green} "OpenXR support enabled")
    else()
        message(WARNING "ENABLE_OPENXR is ON but the OpenXR loader package was not found. XR build plumbing will remain disabled.")
        ERSBuildLogger(${Yellow} "OpenXR package not found, support disabled")
    endif()
else()
    ERSBuildLogger(${Green} "OpenXR support disabled, skipping")
endif()

ERSBuildLogger(${BoldGreen} "Finished Configuring OpenXR Support")
