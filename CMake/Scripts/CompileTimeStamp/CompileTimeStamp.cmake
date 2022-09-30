###############################
# ERS Build Versioning System #
###############################

ERSBuildLogger(${Green} "Configuring Timestamp Info")

message(" -- Detecting Timestamp Information")
set(TARGET_OS_NAME ${CMAKE_SYSTEM_NAME})
set(TARGET_OS_VERSION ${CMAKE_SYSTEM_VERSION})
set(TARGET_PROCESSOR ${CMAKE_SYSTEM_PROCESSOR})

set(HOST_OS_NAME ${CMAKE_HOST_SYSTEM_NAME})
set(HOST_OS_VERSION ${CMAKE_HOST_SYSTEM_VERSION})
set(HOST_PROCESSOR ${CMAKE_HOST_SYSTEM_PROCESSOR})

message(" -- Configuring File ERS_CompileTimestamp.h.in")
configure_File(${CMAKE_SCRIPTS_DIR}/CompileTimestamp/ERS_CompileTimestamp.h.in ${SRC_DIR}/Interface/Configuration/CompileTimestamp/ERS_CompileTimestamp.h)
message(" -- Adding Timestamp Header Target")
add_subdirectory(${SRC_DIR}/Interface/Configuration/CompileTimestamp)

ERSBuildLogger(${BoldGreen} "Finished Configuring Timestamp Info")