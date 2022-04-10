##########################
# Builds Library For ERS #
##########################

ERSBuildLogger(${Green} "Configuring Backward Library")
if (${ENABLE_BACKWARD})
    add_subdirectory(${LIB_DIR}/backward)
else
    set(BACKWARD_ENABLE "")
ERSBuildLogger(${BoldGreen} "Finished Configuring Backward Library")