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
Window_ControllerSettings::Window_ControllerSettings(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, std::shared_ptr<ERS_STRUCT_HumanInputDeviceUtils> HIDUtils, std::shared_ptr<ERS_STRUCT_ProjectUtils> ProjectUtils) {

    // Copy System Utils Pointer Struct
    SystemUtils_ = SystemUtils;
    HIDUtils_ = HIDUtils;
    ProjectUtils_ = ProjectUtils;

}

// Destructor
Window_ControllerSettings::~Window_ControllerSettings() {

}


// Button Text
void Window_ControllerSettings::ButtonText(std::string ButtonName, bool ButtonState) {

    // Generate Text
    std::string ButtonStateLabel = "Released";
    if (ButtonState) {
        ButtonStateLabel = "Pressed";
    }

    // Draw Text
    ImGui::Text("%s", (ButtonName + std::string(": ") + ButtonStateLabel).c_str());
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


            // Begin Tabs For Info, Config
            if (ImGui::BeginTabBar("Controller Settings Tab Bar")) {


                // Info Tab
                if (ImGui::BeginTabItem("Info")) {

                    // Info Child Window
                    ImGui::BeginChild("Controller Info");

                    // Check if there aren't any controllers, display no controllers message
                    if (NumberControllers == 0) {
                        ImGui::TextColored(ImVec4(1.0f, 0.2f, 0.2f, 1.0f), "No controllers detected. Try running 'Detect New Controllers'");
                    } else {

                        // Get Game Controller State
                        GLFWgamepadstate State = HIDUtils_->ControllerInputManager->ControllerStates_[SelectedController_];

                        // Joystick Info
                        ImGui::Separator();
                        ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), "Joysticks");
                        ImGui::Separator();

                        // Joystick Positions
                        ImGui::Text("Left Joystick Vertical Axis: %f", State.axes[GLFW_GAMEPAD_AXIS_LEFT_Y]);
                        ImGui::Text("Left Joystick Horizontal Axis: %f", State.axes[GLFW_GAMEPAD_AXIS_LEFT_X]);
                        
                        ImGui::Text("Right Joystick Vertical Axis: %f", State.axes[GLFW_GAMEPAD_AXIS_RIGHT_Y]);
                        ImGui::Text("Right Joystick Horizontal Axis: %f", State.axes[GLFW_GAMEPAD_AXIS_RIGHT_X]);

                        // Joysticks Pressed
                        ButtonText(std::string("Left Joystick"), State.buttons[GLFW_GAMEPAD_BUTTON_LEFT_THUMB]);
                        ButtonText(std::string("Right Joystick"), State.buttons[GLFW_GAMEPAD_BUTTON_RIGHT_THUMB]);

                        // Trigger Info
                        ImGui::Separator();
                        ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), "Triggers");
                        ImGui::Separator();

                        ImGui::Text("Left Trigger: %f", State.axes[GLFW_GAMEPAD_AXIS_LEFT_TRIGGER]);
                        ImGui::Text("Right Trigger: %f", State.axes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER]);

                        ButtonText("Left Bumper", State.buttons[GLFW_GAMEPAD_BUTTON_LEFT_BUMPER]);
                        ButtonText("Right Bumper", State.buttons[GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER]);


                        // DPAD Info
                        ImGui::Separator();
                        ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), "DPAD");
                        ImGui::Separator();

                        ButtonText("DPAD Up", State.buttons[GLFW_GAMEPAD_BUTTON_DPAD_UP]);
                        ButtonText("DPAD Down", State.buttons[GLFW_GAMEPAD_BUTTON_DPAD_DOWN]);
                        ButtonText("DPAD Left", State.buttons[GLFW_GAMEPAD_BUTTON_DPAD_LEFT]);
                        ButtonText("DPAD Right", State.buttons[GLFW_GAMEPAD_BUTTON_DPAD_RIGHT]);


                        // TRIANGLE/CIRCLE/SQUARE/X Buttons
                        ImGui::Separator();
                        ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), "Input Buttons");
                        ImGui::Separator();

                        ButtonText("Triangle", State.buttons[GLFW_GAMEPAD_BUTTON_TRIANGLE]);
                        ButtonText("Square", State.buttons[GLFW_GAMEPAD_BUTTON_SQUARE]);
                        ButtonText("Circle", State.buttons[GLFW_GAMEPAD_BUTTON_CIRCLE]);
                        ButtonText("Cross", State.buttons[GLFW_GAMEPAD_BUTTON_CROSS]);
                        
                        ButtonText("Back", State.buttons[GLFW_GAMEPAD_BUTTON_BACK]);
                        ButtonText("Menu", State.buttons[GLFW_GAMEPAD_BUTTON_GUIDE]);

                    }
                    ImGui::EndChild();

                ImGui::EndTabItem();
                }

                // Settings Tab
                if (ImGui::BeginTabItem("Settings")) {

                    // Child Settings
                    ImGui::BeginChild("Controller Setttings"); 


                    // Get Controller Settings Info
                    std::vector<std::shared_ptr<ERS_STRUCT_ControllerSettings>> ControllerSettings = ProjectUtils_->ProjectManager_->Project_.ControllerSettings;

                    // Update Controller Dropdown List And Index
                    if (SelectedControllerProfile_ > ControllerSettings.size()) {
                        SelectedControllerProfile_ = ControllerSettings.size() - 1;
                    }

                    for (int i = 0; i < ControllerSettings.size(); i++) {
                        ControllerProfileNames_[i] = ControllerSettings[i]->SettingsProfileName.c_str();
                    }

                    // Selector Dropdown
                    ImGui::Combo("Selected Controller Profile", &SelectedControllerProfile_, ControllerProfileNames_, ControllerSettings.size(),  ControllerSettings.size());
                    


                    // Check if there aren't any controllers, display no controllers message
                    if (NumberControllers == 0) {
                        ImGui::TextColored(ImVec4(1.0f, 0.2f, 0.2f, 1.0f), "No controllers detected. Try running 'Detect New Controllers'");
                    } else {


                    

                        // Thresholds
                        ImGui::Separator();
                        ImGui::TextColored(ImVec4(0.2f, 1.0f, 0.2f, 1.0f), "Joystick Thresholds");
                        ImGui::Separator();



                    }

                    ImGui::EndChild();

                ImGui::EndTabItem();
                }


            ImGui::EndTabBar();
            }

        }

    ImGui::End();
    }


}