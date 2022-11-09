##########################
# Builds Library For ERS #
##########################

ERSBuildLogger(${Green} "Configuring WhereAmI Library")
add_subdirectory(${LIB_DIR}/whereami)
disable_target_warnings(wherami)
ERSBuildLogger(${BoldGreen} "Finished Configuring WhereAmI Library")