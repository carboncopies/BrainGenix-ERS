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

        // Interface Config
        ImGui::MenuItem("Color Theme", "", &Windows_->GUI_Window_ThemeSelector_->Enabled_);
        ImGui::MenuItem("System Font", "", &Windows_->GUI_Window_FontSelector_->Enabled_);


        ImGui::Separator();


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