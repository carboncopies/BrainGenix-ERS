//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This Window file is responsible for creating a system Window.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-17
*/

#include <GUI_Window_ControllerSettings.h>


// Constructor
Window_ControllerSettings::Window_ControllerSettings(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, std::shared_ptr<ERS_STRUCT_HumanInputDeviceUtils> HIDUtils) {

    // Copy System Utils Pointer Struct
    SystemUtils_ = SystemUtils;
    HIDUtils_ = HIDUtils;

}

// Destructor
Window_ControllerSettings::~Window_ControllerSettings() {

}



// Draw Window
void Window_ControllerSettings::Draw() {


    if (Enabled_) {
    bool Visible = ImGui::Begin("Game Controller Settings", &Enabled_);

        // Set Window Size
        ImGui::SetWindowSize(ImVec2(600, 400), ImGuiCond_FirstUseEver);


        if (Visible) {
            
            // Active Selected Controller Dropdown
            int NumberControllers = HIDUtils_->ControllerInputManager->NumberControllers_;
            for (int i = 0; i < NumberControllers; i++) {
                ControllerNames_[i] = HIDUtils_->ControllerInputManager->ControllerNames_[i].c_str();
            }
            ImGui::Combo("Selected Controller", &SelectedController_, NumberControllers, NumberControllers);

        }

    ImGui::End();
    }


}