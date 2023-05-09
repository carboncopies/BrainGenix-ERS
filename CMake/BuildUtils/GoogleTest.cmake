##########################
# Builds Library For ERS #
##########################

ERSBuildLogger(${Green} "Configuring GoogleTest Library")
add_subdirectory(${LIB_DIR}/NonSuperBuild/GoogleTest)
ERSBuildLogger(${BoldGreen} "Finished Configuring GoogleTest Library")