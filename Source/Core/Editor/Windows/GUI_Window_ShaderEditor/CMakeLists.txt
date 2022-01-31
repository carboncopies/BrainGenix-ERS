########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################

# Create Library (Name Should Be Parent Dir Name)
add_library(Window_ShaderEditor

            # Add Source Files (.cpp)
            "GUI_Window_ShaderEditor.cpp"

            # Add Header Files (.h)
            "GUI_Window_ShaderEditor.h"


            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Window_ShaderEditor
    IMGUI
    ImGuiColorTextEdit
    )

# Link Internal Libs
target_link_libraries(Window_ShaderEditor
    ERS_STRUCT_SystemUtils
    )

target_include_directories(Window_ShaderEditor PUBLIC ./)
