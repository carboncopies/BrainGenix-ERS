###############################
# ERS Build Versioning System #
###############################

ERSBuildLogger(${Green} "Configuring Platform Info")

message(" -- Configuring File ERS_CompilePlatformInfo.h.in")
configure_File(${CMAKE_SCRIPTS_DIR}/CompilePlatformInfo/ERS_CompilePlatformInfo.h.in ${SRC_DIR}/Interface/Configuration/CompilePlatformInfo/ERS_CompilePlatformInfo.h)
message(" -- Adding CompilePlatformInfo Header Target")
add_subdirectory(${SRC_DIR}/Interface/Configuration/CompilePlatformInfo)

ERSBuildLogger(${BoldGreen} "Finished Configuring Platform Info")