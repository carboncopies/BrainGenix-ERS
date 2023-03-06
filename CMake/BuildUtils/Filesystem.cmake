##########################
# Builds Library For ERS #
##########################

ERSBuildLogger(${Green} "Configuring Filesystem Library")
add_subdirectory(${LIB_DIR}/NonSuperBuild/filesystem)
# disable_target_warnings(ghc_filesystem)
ERSBuildLogger(${BoldGreen} "Finished Configuring Filesystem Library")