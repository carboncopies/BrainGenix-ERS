########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_ModelWriter

            # Add Source Files (.cpp)
            "ERS_ModelWriter.cpp"

            # Add Header Files (.h)
            "ERS_ModelWriter.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_ModelWriter
    )

# Link Internal Libs
target_link_libraries(ERS_ModelWriter
    ERS_CLASS_LoggingSystem
    ERS_STRUCT_Model
    ERS_STRUCT_Scene
    ERS_STRUCT_Mesh
    Textures
    ERS_InputOutputSubsystem
    )

target_include_directories(ERS_ModelWriter PUBLIC ./)

