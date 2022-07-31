//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Menu_Settings.h>


GUI_Menu_Settings::GUI_Menu_Settings(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_HumanInputDeviceUtils* HIDUtils, ERS_STRUCT_Windows* Windows) {

    SystemUtils_ = SystemUtils;
    HIDUtils_ = HIDUtils;
    Windows_ = Windows;

    SystemUtils_->Logger_->Log("Editor Setting Up Settings Menu", 4);



}

GUI_Menu_Settings::~GUI_Menu_Settings() {

    SystemUtils_->Logger_->Log("Editor Destroying Settings Menu", 4);

}

void GUI_Menu_Settings::Draw() {

    // File Menu
    if (ImGui::BeginMenu("Settings")) {

        // Layout Menu
        if (ImGui::BeginMenu("Editor Layout")) {
            
            
            // Create Submenu with layouts which the user can select from
            if (ImGui::BeginMenu("Select Layouts")) {



            ImGui::EndMenu();
            }

            // Normal buttons that the user can select
            if (ImGui::MenuItem("Save Active Layout")) {

            }
            
            if (ImGui::MenuItem("Create New Layout")) {

            }

            if (ImGui::MenuItem("Rename Active Layout")) {

            }

            if (ImGui::MenuItem("Re-Detect Layouts")) {

            }

        ImGui::EndMenu();
        }

        // Controller Settings
        if (ImGui::BeginMenu("Game Controllers")) {

            // Refresh
            if (ImGui::MenuItem("Detect New Controllers")) {
                HIDUtils_->ControllerInputManager->DetectControllers();
            }

            // Open Settings MEnu
            if (ImGui::MenuItem("Game Controller Settings")) {
                Windows_->GUI_Window_ControllerSettings_->Enabled_ = !Windows_->GUI_Window_ControllerSettings_->Enabled_;
            }

        ImGui::EndMenu();
        }


    ImGui::EndMenu();
    }


}