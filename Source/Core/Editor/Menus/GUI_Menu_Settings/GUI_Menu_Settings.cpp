//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Menu_Settings.h>


GUI_Menu_Settings::GUI_Menu_Settings(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_HumanInputDeviceUtils* HIDUtils, ERS_STRUCT_Windows* Windows, ERS_Editor_LayoutManager* LayoutManager) {

    SystemUtils_ = SystemUtils;
    HIDUtils_ = HIDUtils;
    Windows_ = Windows;
    LayoutManager_ = LayoutManager;

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

                std::string ActiveLayoutName = LayoutManager_->GetActiveLayoutName();
                std::vector<std::string> LayoutNames = LayoutManager_->GetLayoutNames();
                for (unsigned int i = 0; i < LayoutNames.size(); i++) {
                    if (ImGui::Selectable(LayoutNames[i].c_str(), (LayoutNames[i] == ActiveLayoutName))) {
                        LayoutManager_->ApplyLayout(LayoutNames[i]);
                    }
                }

            ImGui::EndMenu();
            }

            // Normal buttons that the user can select
            if (ImGui::MenuItem("Save Active Layout")) {
                std::string ActiveLayoutName = LayoutManager_->GetActiveLayoutName();
                LayoutManager_->SaveLayout(ActiveLayoutName);
            }
            
            if (ImGui::MenuItem("Create New Layout")) {
                LayoutManager_->CreateLayout(std::string("Untitled Layout"));
            }

            if (ImGui::MenuItem("Rename Active Layout")) {
                // Todo later - not part of layout manager
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