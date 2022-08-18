########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_CLASS_ModelImporter

            # Add Source Files (.cpp)
            "ERS_CLASS_ModelImporter.cpp"

            # Add Header Files (.h)
            "ERS_CLASS_ModelImporter.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_CLASS_ModelImporter
    yaml-cpp
    glm
    assimp
    FreeImage
    ThreadNamingUtils
    )

# Link Internal Libs
target_link_libraries(ERS_CLASS_ModelImporter
    ERS_STRUCT_Model
    ERS_STRUCT_ModelWriterData
    ERS_STRUCT_SystemUtils

    ERS_CLASS_ExternalModelLoader
    ERS_ModelWriter
    )

target_include_directories(ERS_CLASS_ModelImporter PUBLIC ./)