# Create Library (Name Should Be Parent Dir Name)
add_library(GUI_Window_AssetStreamingSettings

            "GUI_Window_AssetStreamingSettings.cpp"
            "GUI_Window_AssetStreamingSettings.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(GUI_Window_AssetStreamingSettings PRIVATE
    glad
    glfw
    IMGUI
    )

# Link Internal Libs
target_link_libraries(GUI_Window_AssetStreamingSettings PRIVATE
    ERS_STRUCT_SystemUtils
    ERS_STRUCT_ProjectUtils
    ERS_ModelLoader
    )

target_include_directories(GUI_Window_AssetStreamingSettings PUBLIC ./)