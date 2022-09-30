###############################
# ERS Build Versioning System #
###############################

ERSBuildLogger(${Green} "Configuring Version Header File")
configure_File(CMAKE_SCRIPTS_DIR/VersioningSystem/ERS_Version.h.in CMAKE_)
ERSBuildLogger(${BoldGreen} "Finished Configuring Assimp Library")