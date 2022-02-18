##########################
# Builds Library For ERS #
##########################

ERSBuildLogger(${Green} "Configuring Assimp Library")
add_subdirectory(${LIB_DIR}/assimp)
target_include_directories(assimp PUBLIC ${LIB_DIR}/assimp/include)
disable_target_warnings(assimp)
ERSBuildLogger(${BoldGreen} "Finished Configuring Assimp Library")