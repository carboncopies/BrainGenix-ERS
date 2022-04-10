##########################
# Builds Library For ERS #
##########################

ERSBuildLogger(${Green} "Configuring ImGuiFileDialog Library")
add_subdirectory(${LIB_DIR}/ImGuiFileDialog-Lib_Only)
disable_target_warnings(ImGuiFileDialog)
ERSBuildLogger(${BoldGreen} "Finished Configuring ImGuiFileDialog Library")