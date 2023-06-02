##########################
# Builds Library For ERS #
##########################

ERSBuildLogger(${Green} "Configuring PlatformFolders Library")

# ExternalProject_Add(PlatformFolders

#     # Specify Directory Configuration Options
#     SOURCE_DIR ${LIB_DIR}/PlatformFolders
#     BINARY_DIR ${BIN_DIR}
#     INSTALL_DIR ${BIN_DIR}
    
#     # # Show Output To Terminal
#     # LOG_DOWNLOAD TRUE
#     # LOG_UPDATE TRUE
#     # LOG_PATCH TRUE
#     # LOG_CONFIGURE TRUE
#     # LOG_BUILD TRUE
#     # LOG_INSTALL TRUE
#     # LOG_TEST TRUE
#     # LOG_MERGED_STDOUTERR TRUE

#     # USES_TERMINAL_DOWNLOAD TRUE
#     # USES_TERMINAL_UPDATE TRUE
#     # USES_TERMINAL_PATCH TRUE
#     # USES_TERMINAL_CONFIGURE TRUE
#     # USES_TERMINAL_BUILD TRUE
#     # USES_TERMINAL_INSTALL TRUE
#     # USES_TERMINAL_TEST TRUE

#     # # Set Configuation Commands
# 	# UPDATE_COMMAND "${BOOST_UPDATE_COMMAND}"
# 	# CONFIGURE_COMMAND ""
# 	# BUILD_COMMAND ./b2 ${BOOST_LIBS_TO_BUILD_CMD} -j ${N} ${NUM_PROCESSORS} toolset=${BOOST_TOOLSET} link=static stage ${BOOST_CONFIG_OPTIONS}
# 	# INSTALL_COMMAND ""
# )


# find_package(platform_folders REQUIRED)
add_subdirectory(${LIB_DIR}/NonSuperBuild/PlatformFolders)
disable_target_warnings(platform_folders)
ERSBuildLogger(${BoldGreen} "Finished Configuring PlatformFolders Library")