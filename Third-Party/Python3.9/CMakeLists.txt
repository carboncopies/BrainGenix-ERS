 
# Automatically copies python binaries to bin dir on windows
if (WIN32)

    ERS_BUILD_
    file(COPY "${LIB_DIR}/Python3.9/Binaries" DESTINATION "${BIN_DIR}/")

endif()