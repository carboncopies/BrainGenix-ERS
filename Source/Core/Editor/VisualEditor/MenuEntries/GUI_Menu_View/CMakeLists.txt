########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(Menu_View

            # Add Source Files (.cpp)

            "GUI_Menu_View.cpp"

            # Add Header Files (.h)
            "GUI_Menu_View.h"


            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Menu_View
    glad
    glfw
    IMGUI
    )

# Link Internal Libs
target_link_libraries(Menu_View
    LoggingSystem
    ERS_STRUCT_SystemUtils

    ERS_SceneWriter
    SceneManager

    Scene
    )

target_include_directories(Menu_View PUBLIC ./)
