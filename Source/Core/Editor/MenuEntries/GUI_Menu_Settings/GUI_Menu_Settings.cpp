//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <GUI_Menu_Settings.h>


// Constructor
GUI_Menu_Settings::GUI_Menu_Settings(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, std::shared_ptr<ERS_STRUCT_HumanInputDeviceUtils> HIDUtils, std::shared_ptr<ERS_STRUCT_ProjectUtils> ProjectUtils) {

    // Copy In Pointer Struct
    SystemUtils_ = SystemUtils;
    HIDUtils_ = HIDUtils;
    ProjectUtils_ = ProjectUtils;

    // Log Initialization
    SystemUtils_->Logger_->Log("Editor Setting Up Settings Menu", 4);

    // Instantiate Window Classes
    Window_ControllerSettings_ = std::make_unique<Window_ControllerSettings>(SystemUtils_, HIDUtils_, ProjectUtils_);

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

        // Controller Settings
        if (ImGui::BeginMenu("Game Controllers")) {

            // Refresh
            if (ImGui::MenuItem("Detect New Controllers")) {
                HIDUtils_->ControllerInputManager->DetectControllers();
            }

            // Open Settings MEnu
            if (ImGui::MenuItem("Game Controller Settings")) {
                Window_ControllerSettings_->Enabled_ = !Window_ControllerSettings_->Enabled_;
            }

        ImGui::EndMenu();
        }


    ImGui::EndMenu();
    }


    // Draw Subwindows
    Window_ControllerSettings_->Draw();

}