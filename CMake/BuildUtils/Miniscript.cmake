##########################
# Builds Library For ERS #
##########################

ERSBuildLogger(${Green} "Configuring Miniscript Library")
add_subdirectory(${LIB_DIR}/miniscript/MiniScript-cpp)
ERSBuildLogger(${BoldGreen} "Finished Configuring Miniscript Library")