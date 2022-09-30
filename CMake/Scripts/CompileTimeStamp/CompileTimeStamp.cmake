###############################
# ERS Build Versioning System #
###############################

ERSBuildLogger(${Green} "Configuring Timestamp Info")

message(" -- Detecting Timestamp Information")
set(COMPILE_TIME_STAMP "")
string(COMPILE_TIME_STAMP TODAY "%Y%m%d")

message(" -- Configuring File ERS_CompileTimeStamp.h.in")
configure_File(${CMAKE_SCRIPTS_DIR}/CompileTimeStamp/ERS_CompileTimeStamp.h.in ${SRC_DIR}/Interface/Configuration/CompileTimeStamp/ERS_CompileTimeStamp.h)

message(" -- Adding Timestamp Header Target")
add_subdirectory(${SRC_DIR}/Interface/Configuration/CompileTimeStamp)

ERSBuildLogger(${BoldGreen} "Finished Configuring Timestamp Info")