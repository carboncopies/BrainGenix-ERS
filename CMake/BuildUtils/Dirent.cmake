##########################
# Builds Library For ERS #
##########################

ERSBuildLogger(${Green} "Configuring Dirent Library")
add_subdirectory(${LIB_DIR}/Dirent/Dirent)
disable_target_warnings(Dirent)
ERSBuildLogger(${BoldGreen} "Finished Configuring Dirent Library")