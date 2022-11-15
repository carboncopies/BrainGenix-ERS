##########################
# Builds Library For ERS #
##########################

include(ExternalProject)

ERSBuildLogger(${Green} "Configuring Lucifer Library")
add_subdirectory(${LIB_DIR}/LuciferIL/LuciferIL)
disable_target_warnings(Lucifer)

# ExternalProject_Add(LuciferIL

#     # Specify Directory Configuration Options
#     SOURCE_DIR ${LIB_DIR}/LuciferIL/LuciferIL
#     BINARY_DIR ${BIN_DIR}/ThirdParty/Lucifer
    
#     # Show Output To Terminal
#     LOG_DOWNLOAD TRUE
#     LOG_UPDATE TRUE
#     LOG_PATCH TRUE
#     LOG_CONFIGURE TRUE
#     LOG_BUILD TRUE
#     LOG_INSTALL TRUE
#     LOG_TEST TRUE
#     LOG_MERGED_STDOUTERR TRUE

#     USES_TERMINAL_DOWNLOAD TRUE
#     USES_TERMINAL_UPDATE TRUE
#     USES_TERMINAL_PATCH TRUE
#     USES_TERMINAL_CONFIGURE TRUE
#     USES_TERMINAL_BUILD TRUE
#     USES_TERMINAL_INSTALL TRUE
#     USES_TERMINAL_TEST TRUE

#     # # Set Configuation Commands
# 	# UPDATE_COMMAND "${BOOST_UPDATE_COMMAND}"
# 	# CONFIGURE_COMMAND ""
# 	# BUILD_COMMAND ./b2 ${BOOST_LIBS_TO_BUILD_CMD} -j ${N} ${NUM_PROCESSORS} toolset=${BOOST_TOOLSET} link=static stage ${BOOST_CONFIG_OPTIONS}
# 	# INSTALL_COMMAND ""
# )

ERSBuildLogger(${BoldGreen} "Finished Configuring Lucifer Library")
