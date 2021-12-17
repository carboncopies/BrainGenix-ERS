# THIS CMAKE IS NOT PART OF THE LIBRARY, AND WAS MADE BY THE ERS DEV TEAM


add_library(ImGuiFileDialog 
    "ImGuiFileDialog.h"
    "ImGuiFileDialogConfig.h"
    "ImGuiFileDialog.cpp"
)

target_link_libraries(ImGuiFileDialog

    IMGUI
    
)

target_include_directories(ImGuiFileDialog PUBLIC ./)