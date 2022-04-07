########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################

# Create Library (Name Should Be Parent Dir Name)
add_library(Window_ScriptEditor

            # Add Source Files (.cpp)
            "GUI_Window_ScriptEditor.cpp"

            # Add Header Files (.h)
            "GUI_Window_ScriptEditor.h"


            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Window_ScriptEditor
    IMGUI
    ImGuiColorTextEdit
    )

# Link Internal Libs
target_link_libraries(Window_ScriptEditor
    ERS_STRUCT_SystemUtils
    ERS_STRUCT_ProjectUtils
    ERS_STRUCT_Script
    )

target_include_directories(Window_ScriptEditor PUBLIC ./)
