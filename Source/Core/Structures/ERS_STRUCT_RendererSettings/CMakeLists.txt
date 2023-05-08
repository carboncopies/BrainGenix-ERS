########################################################################
# This file is part of the BrainGenix-ERS Environment Rendering System #
########################################################################


# Create Library (Name Should Be Parent Dir Name)
add_library(ERS_STRUCT_RendererSettings

            # Add Source Files (.cpp)
            "RendererSettings.cpp"
            "ENUM_ShadowFilteringType.cpp"
            "ENUM_ShadowUpdateMode.cpp"
            

            # Add Header Files (.h)
            "RendererSettings.h"
            "ENUM_ShadowFilteringType.h"
            "ENUM_ShadowUpdateMode.h"
            
            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(ERS_STRUCT_RendererSettings
    )

# Link Internal Libs
target_link_libraries(ERS_STRUCT_RendererSettings
    )


target_include_directories(ERS_STRUCT_RendererSettings PUBLIC ./)
set_target_properties(ERS_STRUCT_RendererSettings PROPERTIES LINKER_LANGUAGE CXX)