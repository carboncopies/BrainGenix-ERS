# Create Library (Name Should Be Parent Dir Name)
add_library(WhereAmI

            # Add Source Files (.cpp)
            "src/whereami.c"

            # Add Header Files (.h)
            "src/whereami.h"
            
            ${BACKWARD_ENABLE}
            )
set_property(TARGET WhereAmI PROPERTY CXX_STANDARD 17)

# Link 3rd Party Libs
target_link_libraries(WhereAmI
    yaml-cpp
    glm
    assimp
    FreeImage
    Lucifer
    ghc_filesystem
    )

# Link Internal Libs
target_link_libraries(WhereAmI
    ERS_STRUCT_Mesh
    ERS_STRUCT_Model
    ERS_STRUCT_Vertex
    ERS_STRUCT_ModelWriterData
    ERS_STRUCT_SystemUtils
    ERS_STRUCT_IOData
    )
    target_include_directories(WhereAmI PUBLIC ./src)
    target_include_directories(WhereAmI PUBLIC ./)
