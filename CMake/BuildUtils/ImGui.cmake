##########################
# Builds Library For ERS #
##########################

ERSBuildLogger(${Green} "Configuring ImGui Library")
add_subdirectory(${LIB_DIR}/NonSuperBuild/imgui)
ERSBuildLogger(${BoldGreen} "Finished Configuring ImGui Library")