##########################
# Builds Library For ERS #
##########################

ERSBuildLogger(${Green} "Configuring Zep Library")
add_subdirectory(${LIB_DIR}/zep)
disable_target_warnings(Zep)
ERSBuildLogger(${BoldGreen} "Finished Configuring Zep Library")