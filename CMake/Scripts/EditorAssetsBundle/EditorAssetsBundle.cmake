###############################
# ERS Build Versioning System #
###############################

ERSBuildLogger(${Cyan} "Configuring Editor Resources")


# Identify Resources Dir
message(STATUS "Detecting Build Type")
set(EDITOR_RESOURCES_DIR "${BIN_DIR}")
if (EXECUTABLE_TYPE == "OSX_Bundle")
    set(EDITOR_RESOURCES_DIR "${BIN_DIR}/${PROJECT_NAME}.app/Contents/MacOS")
    message(STATUS "Set Build Type To OSX Bundle")
else()
    message(STATUS "Set Build Type To Standard Binary")
endif()
message(STATUS "Set Editor Resources Path To '${EDITOR_RESOURCES_DIR}'")


# Configure Variables
message(STATUS "Configuring Config.yaml")
message(STATUS "--------------------")
set(DEFAULT_PROJECT_DIRECTORY "EditorAssets/Projects/DefaultProject/")
message(STATUS "Set DEFAULT_PROJECT_DIRECTORY to '${DEFAULT_PROJECT_DIRECTORY}'")
set(IS_LINUX "True")
if (WIN32 OR APPLE)
    set(IS_LINUX "False")
endif()
message(STATUS "Set IS_LINUX to '${IS_LINUX}'")
message(STATUS "--------------------")



# Set Config
message(STATUS "Configuring File")
configure_File(${CMAKE_SCRIPTS_DIR}/EditorAssetsBundle/Config.yaml.in ${BIN_DIR}/Config.yaml)

ERSBuildLogger(${BoldCyan} "Finished Configuring Editor Resources")
