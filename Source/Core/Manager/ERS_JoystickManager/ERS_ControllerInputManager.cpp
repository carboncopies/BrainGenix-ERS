//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for providing a system for getting joystick input and adding it to the input struct.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2022-01-08
*/

#include <ERS_ControllerInputManager.h>



// Constructor
ERS_CLASS_ControllerInputManager::ERS_CLASS_ControllerInputManager(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils) {

    // Copy Pointer
    SystemUtils_ = SystemUtils;

    // Log Initialization
    SystemUtils_->Logger_->Log("Initializing ERS Controller Input Manager", 5);



}

// Destructor
ERS_CLASS_ControllerInputManager::~ERS_CLASS_ControllerInputManager() {

    // Log Destructor Call
    SystemUtils_->Logger_->Log("ERS Controller Input Manager Destructor Called", 6);

}


// Detect InputDevices
void ERS_CLASS_ControllerInputManager::UpdateNumberInputDevices() {

    // Iterate Through All 16 Supported Controllers
    NumberInputDevices_ = 0;
    for (int i = 0; i < 16; i++) {
        if(glfwJoystickPresent(i)) {
            NumberInputDevices_ ++;
        }
    }

}

// Update Number Axes Per Joystick
void ERS_CLASS_ControllerInputManager::CheckIfSupportedControllers() {

    // Clear Controller Supported List
    IsControllerSupported_.erase(IsControllerSupported_.begin(), IsControllerSupported_.end());

    // Iterate Through Current Number Controllers
    for (int i = 0; i < NumberControllers_; i++) {
        IsControllerSupported_.push_back(glfwJoystickIsGamepad(i));
    }

}

// Get Data For Each Axis
void ERS_CLASS_ControllerInputManager::UpdateControllerStates() {

    // Clear States
    ControllerStates_.erase(ControllerStates_.begin(), ControllerStates_.end());
    ControllerNames_.erase(ControllerNames_.begin(), ControllerNames_.end());
    NumberControllers_ = 0;

    // Iterate Through Joysticks, Check If Controller
    for (int i = 0; i < NumberInputDevices_; i++) {

        if (IsControllerSupported_[i]) {

            // Incriment Number Of Controller Info
            NumberControllers_++;

            // Get Controller Info
            GLFWgamepadstate State;
            glfwGetGamepadState(i, &State);
            ControllerStates_.push_back(State);

            // Append To Name
            ControllerNames_.push_back(std::string(glfwGetGamepadName(i)));

            std::cout<<std::string(glfwGetGamepadName(i))<<std::endl;

        }

    }


}


// Update Controllers
void ERS_CLASS_ControllerInputManager::UpdateControllers() {

    // Update Data
    UpdateNumberInputDevices();
    CheckIfSupportedControllers();
    UpdateControllerStates();

}