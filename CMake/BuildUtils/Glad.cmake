##########################
# Builds Library For ERS #
##########################

ERSBuildLogger(${Green} "Configuring Glad Library")
add_subdirectory(${LIB_DIR}/NonSuperBuild/glad)
disable_target_warnings(glad)
ERSBuildLogger(${BoldGreen} "Finished Configuring Glad Library")