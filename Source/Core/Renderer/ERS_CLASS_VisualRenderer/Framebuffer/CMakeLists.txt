########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_CLASS_Framebuffer

            # Add Source Files (.cpp)
            "Framebuffer.cpp"

            # Add Header Files (.h)
            "Framebuffer.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_CLASS_Framebuffer
    glm
    glad
    glfw
    IMGUI
    )

# Link Internal Libs
target_link_libraries(ERS_CLASS_Framebuffer
    ERS_CLASS_LoggingSystem
    ERS_STRUCT_Shader
    ERS_ShaderLoader
    )

target_include_directories(ERS_CLASS_Framebuffer PUBLIC ./)
