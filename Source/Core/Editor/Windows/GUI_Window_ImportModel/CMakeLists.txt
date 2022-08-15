########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(GUI_Window_ImportAsset

            # Add Source Files (.cpp)
            "GUI_Window_ImportAsset.cpp"
            "GUI_Window_ModelImporter.cpp"
            "GUI_Window_ImportAsset.cpp"


            # Add Header Files (.h)
            "GUI_Window_ImportAsset.h"
            "GUI_Window_ModelImporter.h"
            "GUI_Window_ImportAsset.h"
            
            ${BACKWARD_ENABLE}
            )
set_property(TARGET GUI_Window_ImportAsset PROPERTY CXX_STANDARD 17)
            
# Link 3rd Party Libs
target_link_libraries(GUI_Window_ImportAsset
    yaml-cpp
    glm
    IMGUI
    ImGuiFileDialog
    assimp
    FreeImage
    )

# Link Internal Libs
target_link_libraries(GUI_Window_ImportAsset
    ERS_CLASS_LoggingSystem

    ERS_STRUCT_SystemUtils
    ERS_STRUCT_Mesh
    ERS_STRUCT_Texture
    ERS_STRUCT_Vertex
    ERS_STRUCT_Model
    ERS_STRUCT_IOData
    ERS_STRUCT_ModelWriterData

    GUI_Window_ImportProgressBar
    )

target_include_directories(GUI_Window_ImportAsset PUBLIC ./)