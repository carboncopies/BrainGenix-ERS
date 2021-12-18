# THIS CMAKE IS NOT PART OF THE LIBRARY, AND WAS MADE BY THE ERS DEV TEAM


add_library(ImGuiFileDialog 
    "ImGuiFileDialog.h"
    "ImGuiFileDialogConfig.h"
    "ImGuiFileDialog.cpp"
)

set_property(TARGET ImGuiFileDialog PROPERTY CXX_STANDARD 17)

target_link_libraries(ImGuiFileDialog

    IMGUI
    glad
    glfw
)

target_include_directories(ImGuiFileDialog PUBLIC ./)