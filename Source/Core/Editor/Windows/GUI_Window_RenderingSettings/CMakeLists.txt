#######################################################################
# Use This CMakeLists.txt To Add Your Source Windows Subfolder Cmakes #
#######################################################################



target_sources(ERS_CLASS_Windows PUBLIC

            "GUI_Window_RenderingSettings/GUI_Window_RenderingSettings.cpp"
            "GUI_Window_RenderingSettings/GUI_Window_RenderingSettings.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(Widgets
    glad
    glfw
    IMGUI
    ImPlot
    )

# Link Internal Libs
target_link_libraries(Widgets
    ERS_CLASS_LoggingSystem
    
    ERS_Editor_ThemeManager
    ERS_Editor_FontManager
    ERS_Editor_3DCursor

    ERS_STRUCT_SystemUtils
    ERS_STRUCT_HardwareInfo
    ERS_STRUCT_Scene
    ERS_STRUCT_ProjectUtils
    ERS_STRUCT_RendererSettings


    ERS_SceneManager

    )

target_include_directories(ERS_CLASS_Windows PUBLIC ./)