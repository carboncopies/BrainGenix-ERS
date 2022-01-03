########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################

# Add Subdirs
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Utils)

# Create Library (Name Should Be Parent Dir Name)
add_library(Menu_File

            # Add Source Files (.cpp)
            "GUI_Menu_File.cpp"

            # Add Header Files (.h)
            "GUI_Menu_File.h"


            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Menu_File
    glad
    glfw
    IMGUI
    )

# Link Internal Libs
target_link_libraries(Menu_File
    LoggingSystem
    ERS_STRUCT_SystemUtils

    ERS_Editor_ImportAsset

    ERS_SceneWriter
    ERS_ProjectLoader

    ERS_SceneManager
    Scene

    #Window_ProjectSettings
    )

target_include_directories(Menu_File PUBLIC ./)
