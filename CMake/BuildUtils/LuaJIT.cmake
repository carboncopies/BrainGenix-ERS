##########################
# Builds Library For ERS #
##########################

ERSBuildLogger(${Green} "Configuring LuaJIT Library")
add_subdirectory(${LIB_DIR}/SuperBuild/LuaJIT/)
ERSBuildLogger(${BoldGreen} "Finished Configuring LuaJIT Library")
