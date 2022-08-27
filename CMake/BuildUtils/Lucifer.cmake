##########################
# Builds Library For ERS #
##########################

ERSBuildLogger(${Green} "Configuring Lucifer Library")
cmake_policy(SET CMP0063 NEW)
add_subdirectory(${LIB_DIR}/LuciferIL/LuciferIL)
disable_target_warnings(Lucifer)
ERSBuildLogger(${BoldGreen} "Finished Configuring Lucifer Library")
