//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file provides a GUI menu entry.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-17
*/

#include <GUI_Menu_Settings.h>


// Constructor
GUI_Menu_Settings::GUI_Menu_Settings(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, std::shared_ptr<ERS_STRUCT_HumanInputDeviceUtils> HIDUtils) {

    // Copy In Pointer Struct
    SystemUtils_ = SystemUtils;
    HIDUtils_ = HIDUtils;

    // Log Initialization
    SystemUtils_->Logger_->Log("Editor Setting Up Settings Menu", 4);


}

// Destructor
GUI_Menu_Settings::~GUI_Menu_Settings() {

    // Log Destructor
    SystemUtils_->Logger_->Log("Editor Destroying Settings Menu", 4);

}

// Draw Function
void GUI_Menu_Settings::Draw() {

    // File Menu
    if (ImGui::BeginMenu("Settings")) {

        if (ImGui::MenuItem("Game Controller Settings")) {


        }

        
    ImGui::EndMenu();
    }


    // Draw Subwindows


}