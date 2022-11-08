##########################
# Builds Library For ERS #
##########################

ERSBuildLogger(${Green} "Configuring CPPFS Library")
add_subdirectory(${LIB_DIR}/cppfs)
disable_target_warnings(cppfs)
ERSBuildLogger(${BoldGreen} "Finished Configuring CPPFS Library")