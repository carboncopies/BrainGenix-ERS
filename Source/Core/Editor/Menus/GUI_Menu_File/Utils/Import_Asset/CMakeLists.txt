########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_Editor_ImportAsset

            # Add Source Files (.cpp)
            "ERS_Editor_ImportAsset.cpp"
            "ERS_Editor_ModelImporter.cpp"
            "GUI_ImportAsset.cpp"


            # Add Header Files (.h)
            "ERS_Editor_ImportAsset.h"
            "ERS_Editor_ModelImporter.h"
            "GUI_ImportAsset.h"
            
            ${BACKWARD_ENABLE}
            )
set_property(TARGET ERS_Editor_ImportAsset PROPERTY CXX_STANDARD 17)
            
# Link 3rd Party Libs
target_link_libraries(ERS_Editor_ImportAsset
    yaml-cpp
    glm
    IMGUI
    ImGuiFileDialog
    assimp
    FreeImage
    )

# Link Internal Libs
target_link_libraries(ERS_Editor_ImportAsset
    ERS_CLASS_LoggingSystem

    ERS_STRUCT_SystemUtils
    ERS_STRUCT_Mesh
    ERS_STRUCT_Texture
    ERS_STRUCT_Vertex
    ERS_STRUCT_Model
    ERS_STRUCT_IOData

    GUI_Window_ImportProgressBar
    )

target_include_directories(ERS_Editor_ImportAsset PUBLIC ./)