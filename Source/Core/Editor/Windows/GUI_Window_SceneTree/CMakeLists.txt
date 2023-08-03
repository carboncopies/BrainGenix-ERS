########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################

# Create Library (Name Should Be Parent Dir Name)
add_library(GUI_Window_SceneTree

            # Add Source Files (.cpp)
            "GUI_Window_SceneTree.cpp"
            "DuplicateModel.cpp"
            "DuplicateScene.cpp"
            "DuplicatePointLight.cpp"
            "DuplicateDirectionalLight.cpp"
            "DuplicateSpotLight.cpp"
            "PointLightRenameModal.cpp"
            "DirectionalLightRenameModal.cpp"
            "SpotLightRenameModal.cpp"
            "SceneRenameModal.cpp"
            "ModelRenameModal.cpp"
            "DeleteScene.cpp"
            "DeleteModel.cpp"
            "DeletePointLight.cpp"
            "DeleteDirectionalLight.cpp"
            "DeleteSpotLight.cpp"
            "ModelReplaceModal.cpp"


            # Add Header Files (.h)
            "GUI_Window_SceneTree.h"
            "DuplicateModel.h"
            "DuplicateScene.h"
            "DuplicatePointLight.h"
            "DuplicateDirectionalLight.h"
            "DuplicateSpotLight.h"
            "PointLightRenameModal.h"
            "DirectionalLightRenameModal.h"
            "SpotLightRenameModal.h"
            "SceneRenameModal.h"
            "ModelRenameModal.h"
            "DeleteScene.h"
            "DeleteModel.h"
            "DeletePointLight.h"
            "DeleteDirectionalLight.h"
            "DeleteSpotLight.h"
            "ModelReplaceModal.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(GUI_Window_SceneTree
    glad
    glfw
    IMGUI
    )

# Link Internal Libs
target_link_libraries(GUI_Window_SceneTree
    ERS_STRUCT_SystemUtils
    ERS_STRUCT_ProjectUtils
    ERS_STRUCT_SceneObject

    bg-common-logger
    
    ERS_Editor_3DCursor

    ERS_STRUCT_Scene
    ERS_SceneManager
    )

target_include_directories(GUI_Window_SceneTree PUBLIC ./)
