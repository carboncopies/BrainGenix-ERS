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
            ImGui::Combo("Selected Controller", &SelectedController_, ControllerNames_, NumberControllers, NumberControllers);
            ImGui::Separator();

            // Check if there aren't any controllers, display no controllers message
            if (NumberControllers == 0) {
                ImGui::TextColored(ImVec4(1.0f, 0.2f, 0.2f, 1.0f), "No controllers detected. Try running 'Detect New Controllers'");
            } else {

                // Get Game Controller State
                GLFWgamepadstate State = HIDUtils_->ControllerInputManager->ControllerStates_[SelectedController_];

                // Display Joystick Info
                ImGui::Text("Left Joystick Vertical Axis: %d", State.axes[GLFW_GAMEPAD_AXIS_LEFT_Y]);
                ImGui::Text("Left Joystick Horizontal Axis: %d", State.axes[GLFW_GAMEPAD_AXIS_LEFT_X]);
                
                ImGui::Text("");

                ImGui::Text("Right Joystick Vertical Axis: %d", State.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y]);
                ImGui::Text("Right Joystick Horizontal Axis: %d", State.axes[GLFW_GAMEPAD_AXIS_RIGHT_X]);


            }

        }

    ImGui::End();
    }


}