##############################
# Builds Library For PHFUtil #
##############################

ERSBuildLogger(${Green} "Configuring WhereAmI Library")
add_subdirectory(${LIB_DIR}/NonSuperBuild/whereami)
disable_target_warnings(WhereAmI)
ERSBuildLogger(${BoldGreen} "Finished Configuring WhereAmI Library")