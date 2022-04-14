##########################
# Builds Library For ERS #
##########################

ERSBuildLogger(${Green} "Configuring DevIL Library")
add_subdirectory(${LIB_DIR}/DevIL/DevIL)
disable_target_warnings(DevIL)
ERSBuildLogger(${BoldGreen} "Finished Configuring DevIL Library")
