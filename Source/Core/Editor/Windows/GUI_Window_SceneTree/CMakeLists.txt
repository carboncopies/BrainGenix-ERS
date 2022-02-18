########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################

# Create Library (Name Should Be Parent Dir Name)
add_library(Window_SceneTree

            # Add Source Files (.cpp)
            "GUI_Window_SceneTree.cpp"
            "ERS_GUI_FUNCTION_DuplicateModel.cpp"
            "ERS_GUI_FUNCTION_DuplicateScene.cpp"
            "ERS_GUI_CLASS_SceneRenameModal.cpp"
            "ERS_GUI_CLASS_ModelRenameModal.cpp"
            "ERS_GUI_CLASS_DeleteScene.cpp"
            "ERS_GUI_CLASS_DeleteModel.cpp"


            # Add Header Files (.h)
            "GUI_Window_SceneTree.h"
            "ERS_GUI_FUNCTION_DuplicateModel.h"
            "ERS_GUI_FUNCTION_DuplicateScene.h"
            "ERS_GUI_CLASS_SceneRenameModal.h"
            "ERS_GUI_CLASS_ModelRenameModal.h"
            "ERS_GUI_CLASS_DeleteScene.h"
            "ERS_GUI_CLASS_DeleteModel.h"


            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Window_SceneTree
    glad
    glfw
    IMGUI
    )

# Link Internal Libs
target_link_libraries(Window_SceneTree
    ERS_STRUCT_SystemUtils
    ERS_STRUCT_ProjectUtils

    ERS_CLASS_LoggingSystem

    ERS_STRUCT_Scene
    ERS_SceneManager
    )

target_include_directories(Window_SceneTree PUBLIC ./)
