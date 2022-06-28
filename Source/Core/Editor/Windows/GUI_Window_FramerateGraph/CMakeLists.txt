# Create Library (Name Should Be Parent Dir Name)
add_library(GUI_Window_FramerateGraph

            "GUI_Window_FramerateGraph.cpp"
            "GUI_Window_FramerateGraph.h"

            ${BACKWARD_ENABLE}
            )

# Link 3rd Party Libs
target_link_libraries(GUI_Window_FramerateGraph
    IMGUI
    ImPlot
    )

# Link Internal Libs
target_link_libraries(GUI_Window_FramerateGraph
    ERS_CLASS_LoggingSystem
    
    ERS_STRUCT_SystemUtils
    ERS_STRUCT_ProjectUtils
    ERS_STRUCT_RendererSettings
    ERS_STRUCT_HardwareInfo

    )

target_include_directories(GUI_Window_FramerateGraph PUBLIC ./)