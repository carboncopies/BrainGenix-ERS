##########################
# Builds Library For ERS #
##########################

ERSBuildLogger(${Green} "Configuring CPPFS Library")
add_subdirectory(${LIB_DIR}/CPPFS)
disable_target_warnings(CPPFS)
ERSBuildLogger(${BoldGreen} "Finished Configuring CPPFS Library")