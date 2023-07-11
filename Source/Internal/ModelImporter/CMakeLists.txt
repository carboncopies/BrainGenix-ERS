########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_ModelImporter

            # Add Source Files (.cpp)
            "ModelImporter.cpp"

            # Add Header Files (.h)
            "ModelImporter.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_ModelImporter
    yaml-cpp
    glm
    assimp::assimp
    freeimage::FreeImage
    ThreadNamingUtils
    )

# Link Internal Libs
target_link_libraries(ERS_ModelImporter
    ERS_STRUCT_Model
    ERS_STRUCT_ModelWriterData
    ERS_STRUCT_SystemUtils

    ERS_ExternalModelLoader
    ERS_ModelWriter
    )

target_include_directories(ERS_ModelImporter PUBLIC ./)