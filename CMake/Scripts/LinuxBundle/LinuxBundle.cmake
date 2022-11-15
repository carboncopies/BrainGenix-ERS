###############################
# ERS Build Versioning System #
###############################

ERSBuildLogger(${Cyan} "Configuring Darwin Bundle System")

add_executable(${PROJECT_NAME} ${MAIN_SOURCES})

set(EXECUTABLE_TYPE "Binary")

ERSBuildLogger(${BoldCyan} "Finished Configuring Darwin Bundle System")