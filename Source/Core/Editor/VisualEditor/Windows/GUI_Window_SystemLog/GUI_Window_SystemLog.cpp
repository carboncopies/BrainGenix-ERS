//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This Window file is responsible for creating a system Window.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-17
*/

#include <GUI_Window_SystemLog.h>


// Constructor
Window_SystemLog::Window_SystemLog(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils) {

    // Copy System Utils Pointer Struct
    SystemUtils_ = SystemUtils;

    // Log Init
    SystemUtils_->Logger_->Log("Initializing GUI_Window_SystemLog", 5);

}

// Destructor
Window_SystemLog::~Window_SystemLog() {

    // Log Destructor Call
    SystemUtils_->Logger_->Log("GUI_Window_SystemLog Destructor Called", 6);


}


// Draw Window
void Window_SystemLog::Draw() {


    if (Enabled_) {
    ImGui::Begin("System Log", &Enabled_);

        // Set Default Window Size
        ImGui::SetWindowSize(ImVec2(300,0), ImGuiCond_FirstUseEver);

        ImGui::Text("Test");


    ImGui::End();
    }


}