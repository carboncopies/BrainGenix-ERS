##########################
# Builds Library For ERS #
##########################

include(ExternalProject)


ERSBuildLogger(${Green} "Configuring CPPFS Library")
ExternalProject_Add("CPPFS" 
    SOURCE_DIR ${LIB_DIR}/cppfs
    BINARY_DIR ${BIN_DIR}
    )
# add_subdirectory(${LIB_DIR}/cppfs)
# disable_target_warnings(cppfs)
ERSBuildLogger(${BoldGreen} "Finished Configuring CPPFS Library")