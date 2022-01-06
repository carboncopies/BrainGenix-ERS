##########################
# Builds Library For ERS #
##########################

if (WIN32)
    ERSBuildLogger(${Yellow} "Database Support Disabled On Windows Due To SSL Errors, Please Use Linux/BSD Instead")
else()
    ERSBuildLogger(${Green} "Configuring MySQL Connector Library")
    add_subdirectory(${LIB_DIR}/mysql-connector-linux)
    ERSBuildLogger(${Green} "Finished Configuring MySQL Connector Library")
endif()