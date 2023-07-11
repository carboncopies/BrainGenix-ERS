##########################
# Builds Library For ERS #
##########################

ERSBuildLogger(${Green} "Configuring LuciferIL Library")
add_subdirectory(${LIB_DIR}/NonSuperBuild/LuciferIL/LuciferIL)
disable_target_warnings(Lucifer)
ERSBuildLogger(${BoldGreen} "Finished Configuring LuciferIL Library")