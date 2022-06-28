########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(Menu_Debug

            # Add Source Files (.cpp)
            "GUI_Menu_Debug.cpp"
            "ERS_CLASS_OpenGLDebug.cpp"

            # Add Header Files (.h)
            "GUI_Menu_Debug.h"
            "ERS_CLASS_OpenGLDebug.h"


            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Menu_Debug
    glad
    glfw
    IMGUI
    )

# Link Internal Libs
target_link_libraries(Menu_Debug

    Window_TestEditor

    ERS_STRUCT_SystemUtils
    )

target_include_directories(Menu_Debug PUBLIC ./)
