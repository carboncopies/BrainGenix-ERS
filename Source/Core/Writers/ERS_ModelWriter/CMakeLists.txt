########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_ModelWriter

            # Add Source Files (.cpp)
            "ModelWriter.cpp"

            # Add Header Files (.h)
            "ModelWriter.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_ModelWriter
    )

# Link Internal Libs
target_link_libraries(ERS_ModelWriter
    bg-common-logger
    ERS_STRUCT_Model
    ERS_STRUCT_Scene
    ERS_STRUCT_Mesh
    ERS_STRUCT_Texture
    bg-ers-iosubsystem
    ERS_STRUCT_ModelWriterData
    )

target_include_directories(ERS_ModelWriter PUBLIC ./)

