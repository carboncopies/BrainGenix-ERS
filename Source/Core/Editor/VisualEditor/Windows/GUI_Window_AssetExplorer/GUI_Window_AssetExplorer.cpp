//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This Window file is responsible for creating a system Window.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-17
*/

#include <GUI_Window_AssetExplorer.h>


// Constructor
Window_AssetExplorer::Window_AssetExplorer(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils) {

    // Copy System Utils Pointer Struct
    SystemUtils_ = SystemUtils;

    // Log Init
    SystemUtils_->Logger_->Log("Initializing GUI_Window_AssetExplorer", 5);

}

// Destructor
Window_AssetExplorer::~Window_AssetExplorer() {

    // Log Destructor Call
    SystemUtils_->Logger_->Log("GUI_Window_AssetExplorer Destructor Called", 6);


}


// Draw Window
void Window_AssetExplorer::Draw() {

    if (Enabled_) {
    bool Visible = ImGui::Begin("Asset Explorer", &Enabled_);

        // Set Default Window Size
        ImGui::SetWindowSize(ImVec2(300,0), ImGuiCond_FirstUseEver);


        if (Visible) {

            
            if (AdvancedMode_) {

                
            }


        }

    ImGui::End();
    }


}