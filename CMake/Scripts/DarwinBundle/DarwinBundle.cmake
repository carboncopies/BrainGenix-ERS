###############################
# ERS Build Versioning System #
###############################

ERSBuildLogger(${Cyan} "Configuring Darwin Bundle System")

add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${MAIN_SOURCES})            
set_target_properties(${PROJECT_NAME} PROPERTIES
    BUNDLE True
    MACOSX_BUNDLE_GUI_IDENTIFIER com.Carboncopies.BrainGenix.ERS
    MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
    MACOSX_BUNDLE_BUNDLE_VERSION "0.1"      
    MACOSX_BUNDLE_SHORT_VERSION_STRING "0.1"
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in
)


ERSBuildLogger(${BoldCyan} "Finished Configuring Darwin Bundle System")