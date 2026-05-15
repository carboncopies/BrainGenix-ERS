//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ControllerInputManager.h>



ERS_CLASS_ControllerInputManager::ERS_CLASS_ControllerInputManager(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;

    SystemUtils_->Logger_->Log("Initializing ERS Controller Input Manager", 5);

    DetectControllers();


}

ERS_CLASS_ControllerInputManager::~ERS_CLASS_ControllerInputManager() {

    SystemUtils_->Logger_->Log("ERS Controller Input Manager Destructor Called", 6);

}


void ERS_CLASS_ControllerInputManager::UpdateNumberInputDevices() {

    // Iterate Through All 16 Supported Controllers
    NumberInputDevices_ = 0;
    InputDeviceIDs_.erase(InputDeviceIDs_.begin(), InputDeviceIDs_.end());

    for (int i = 0; i <= GLFW_JOYSTICK_LAST; i++) {
        if(glfwJoystickPresent(i)) {
            NumberInputDevices_ ++;
            InputDeviceIDs_.push_back(i);
        }
    }

}

void ERS_CLASS_ControllerInputManager::CheckIfSupportedControllers() {

    // Clear Controller Supported List
    IsControllerSupported_.erase(IsControllerSupported_.begin(), IsControllerSupported_.end());

    // Iterate Through Current Number Controllers
    for (unsigned int i = 0; i < InputDeviceIDs_.size(); i++) {
        IsControllerSupported_.push_back(glfwJoystickIsGamepad(InputDeviceIDs_[i]));
    }

}

void ERS_CLASS_ControllerInputManager::UpdateControllerStates() {

    // Clear States
    ControllerStates_.erase(ControllerStates_.begin(), ControllerStates_.end());
    ControllerNames_.erase(ControllerNames_.begin(), ControllerNames_.end());
    ControllerSettings_.erase(ControllerSettings_.begin(), ControllerSettings_.end());
    NumberControllers_ = 0;

    // Iterate Through Joysticks, Check If Controller
    for (unsigned int i = 0; i < InputDeviceIDs_.size(); i++) {

        if ((i < IsControllerSupported_.size()) && IsControllerSupported_[i]) {

            // Get Controller Info
            GLFWgamepadstate State;
            if (!glfwGetGamepadState(InputDeviceIDs_[i], &State)) {
                continue;
            }

            const char* ControllerName = glfwGetGamepadName(InputDeviceIDs_[i]);
            ControllerStates_.push_back(State);

            // Append To Name
            if (ControllerName == nullptr) {
                ControllerNames_.push_back("Unknown Controller");
            } else {
                ControllerNames_.push_back(std::string(ControllerName));
            }

            // Add Default Settings
            ControllerSettings_.push_back(ERS_STRUCT_ControllerSettings());

        }

    }

    NumberControllers_ = (int)ControllerStates_.size();


}


void ERS_CLASS_ControllerInputManager::UpdateControllers() {

    // Update Data
    DetectControllers();
    UpdateControllerStates();

}


void ERS_CLASS_ControllerInputManager::DetectControllers() {

    // Update Data
    UpdateNumberInputDevices();
    CheckIfSupportedControllers();

}
