###############################
# ERS Build Versioning System #
###############################

ERSBuildLogger(${Cyan} "Configuring Editor Resources")


# Identify Resources Dir
set(EDITOR_RESOURCES_DIR "${BIN_DIR}")
if ()

# Configure Variables
set(DEFAULT_PROJECT_DIRECTORY "EditorAssets/Projects/DefaultProject/")
set(IS_LINUX "True")
if (WIN32 OR APPLE)
    set(IS_LINUX "False")
endif()



# Set Config
configure_File(${CMAKE_SCRIPTS_DIR}/EditorAssetsBundle/Config.yaml.in ${BIN_DIR}/Config.yaml)

ERSBuildLogger(${BoldCyan} "Finished Configuring Editor Resources")
