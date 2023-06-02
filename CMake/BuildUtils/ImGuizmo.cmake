##########################
# Builds Library For ERS #
##########################

ERSBuildLogger(${Green} "Configuring ImGuizmo Library")
add_subdirectory(${LIB_DIR}/NonSuperBuild/ImGuizmo)
ERSBuildLogger(${BoldGreen} "Finished Configuring ImGuizmo Library")