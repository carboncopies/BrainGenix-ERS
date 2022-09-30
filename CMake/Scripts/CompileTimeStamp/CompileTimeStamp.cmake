###############################
# ERS Build Versioning System #
###############################

ERSBuildLogger(${Green} "Configuring Timestamp Info")

message(" -- Detecting Timestamp Information")
string(COMPILE_TIME_STAMP TODAY "%Y%m%d")

message(" -- Configuring File ERS_CompileTimestamp.h.in")
configure_File(${CMAKE_SCRIPTS_DIR}/CompileTimestamp/ERS_CompileTimestamp.h.in ${SRC_DIR}/Interface/Configuration/CompileTimestamp/ERS_CompileTimestamp.h)

message(" -- Adding Timestamp Header Target")
add_subdirectory(${SRC_DIR}/Interface/Configuration/CompileTimestamp)

ERSBuildLogger(${BoldGreen} "Finished Configuring Timestamp Info")