##########################
# Builds Library For ERS #
##########################

ERSBuildLogger(${Green} "Configuring Backward Library")
add_subdirectory(${LIB_DIR}/backward)
ERSBuildLogger(${BoldGreen} "Finished Configuring Backward Library")