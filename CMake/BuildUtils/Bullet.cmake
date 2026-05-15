############################
# Builds Bullet Integration #
############################

ERSBuildLogger(${Green} "Configuring Bullet Physics Support")
option(ENABLE_BULLET "Build ERS with Bullet physics dependency plumbing for future scene integration" OFF)

add_library(ERS_Bullet INTERFACE)

if (ENABLE_BULLET)
    find_package(Bullet CONFIG QUIET)

    set(ERS_BULLET_TARGETS "")
    if (DEFINED BULLET_LIBRARIES AND NOT "${BULLET_LIBRARIES}" STREQUAL "")
        list(APPEND ERS_BULLET_TARGETS ${BULLET_LIBRARIES})
    else()
        foreach(ERS_BULLET_TARGET IN ITEMS
            BulletDynamics
            BulletCollision
            LinearMath
            BulletSoftBody
            BulletInverseDynamics
            Bullet3Common
            Bullet3Dynamics
        )
            if (TARGET ${ERS_BULLET_TARGET})
                list(APPEND ERS_BULLET_TARGETS ${ERS_BULLET_TARGET})
            endif()
        endforeach()
    endif()

    if (ERS_BULLET_TARGETS)
        list(REMOVE_DUPLICATES ERS_BULLET_TARGETS)
        target_link_libraries(ERS_Bullet INTERFACE ${ERS_BULLET_TARGETS})
        target_compile_definitions(ERS_Bullet INTERFACE ERS_ENABLE_BULLET)
        ERSBuildLogger(${Green} "Bullet physics support enabled")
    else()
        message(WARNING "ENABLE_BULLET is ON but the Bullet package was not found or did not expose usable targets. Physics build plumbing will remain disabled.")
        ERSBuildLogger(${Yellow} "Bullet package not found, support disabled")
    endif()
else()
    ERSBuildLogger(${Green} "Bullet physics support disabled, skipping")
endif()

ERSBuildLogger(${BoldGreen} "Finished Configuring Bullet Physics Support")
