########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(Renderer 

            # Add Source Files (.cpp)
            "RendererManager.cpp"

            # Add Header Files (.h)
            "RendererManager.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Renderer
    yaml-cpp
    glm
    glad
    glfw
    FreeImage
    )

# Link Internal Libs
target_link_libraries(Renderer
    LoggingSystem
    VisualRenderer
    IOManager
    VisualEditor
    3DCursor

    ERS_ModelWriter
    ERS_ModelLoader
    ERS_STRUCT_IOData
    ERS_STRUCT_SystemUtils
    )

target_include_directories(Renderer PUBLIC ./)
