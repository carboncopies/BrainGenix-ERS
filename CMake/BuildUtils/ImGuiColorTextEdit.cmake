##########################
# Builds Library For ERS #
##########################

ERSBuildLogger(${Green} "Configuring ImGuiColorTextEdit Library")
add_subdirectory(${LIB_DIR}/NonSuperBuild/ImGuiColorTextEdit)
ERSBuildLogger(${BoldGreen} "Finished Configuring ImGuiColorTextEdit Library")