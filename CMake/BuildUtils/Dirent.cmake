##########################
# Builds Library For ERS #
##########################

ERSBuildLogger(${Green} "Configuring Dirent Library")
add_subdirectory(${LIB_DIR}/dirent)
ERSBuildLogger(${BoldGreen} "Finished Configuring Dirent Library")