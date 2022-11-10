###############################
# ERS Build Versioning System #
###############################

ERSBuildLogger(${Cyan} "Configuring Darwin Bundle System")

# Configure Variables For Use In Bundle
set(DEVELOPMENT_LANGUAGE "en")
set(EXECUTABLE_NAME ${PROJECT_NAME})
set(MACOS_ICON_PATH "${CMAKE_CURRENTSOURCE_DIR}/EditorAssets/Icons/ProgramIcon/Icon.svg")
set(PRODUCT_BUNDLE_IDENTIFIER "ProductBundleIdentifer")
set(PRODUCT_NAME ${PROJECT_NAME})
set(MACOSX_DEPLOYMENT_TARGET "macos")

# Setup Bundle
add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${MAIN_SOURCES})            
set_target_properties(${PROJECT_NAME} PROPERTIES
    BUNDLE True
    MACOSX_BUNDLE_GUI_IDENTIFIER com.Carboncopies.BrainGenix.ERS
    MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
    MACOSX_BUNDLE_BUNDLE_VERSION "0.1"      
    MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1"
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SCRIPTS_DIR}/DarwinBundle/Info.plist.in
)

set(EXECUTABLE_TYPE "OSX_Bundle")

set(APP_NAME ${PROJECT_NAME})

# # Destination paths below are relative to ${CMAKE_INSTALL_PREFIX}
# install(TARGETS ${APP_NAME}
#     BUNDLE DESTINATION . COMPONENT Runtime
#     RUNTIME DESTINATION bin COMPONENT Runtime
#     )

# # Note Mac specific extension .app
# set(APPS "\${CMAKE_INSTALL_PREFIX}/${APP_NAME}.app")

# # Directories to look for dependencies
# set(DIRS ${CMAKE_BINARY_DIR})

# install(CODE "include(BundleUtilities)
#     fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")")

# set(CPACK_GENERATOR "DRAGNDROP")
# include(CPack)

ERSBuildLogger(${BoldCyan} "Finished Configuring Darwin Bundle System")