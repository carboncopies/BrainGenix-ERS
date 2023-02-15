##########################
# Builds Library For ERS #
##########################

ERSBuildLogger(${Green} "Configuring GLM Library")
add_subdirectory(${LIB_DIR}/NonSuperBuild/glm)
include_directories(${LIB_DIR}/NonSuperBuild/glm)
ERSBuildLogger(${BoldGreen} "Finished Configuring GLM Library")