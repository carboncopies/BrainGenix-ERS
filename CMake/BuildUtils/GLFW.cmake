##########################
# Builds Library For ERS #
##########################

ERSBuildLogger(${Green} "Configuring GLFW Library")
add_subdirectory(${LIB_DIR}/NonSuperBuild/glfw)
disable_target_warnings(glfw)
ERSBuildLogger(${BoldGreen} "Finished Configuring GLFW Library")