###############################
# ERS Build Versioning System #
###############################

ERSBuildLogger(${Green} "Configuring Version Header File")

set(TEST, "An example value")

configure_File(${CMAKE_SCRIPTS_DIR}/VersioningSystem/ERS_Version.h.in ${SRC_DIR}/Interface/Configuration/VersioningSystem/ERS_Version.h)
ERSBuildLogger(${BoldGreen} "Finished Configuring Assimp Library")