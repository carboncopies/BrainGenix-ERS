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


// Detect Joysticks
void ERS_CLASS_ControllerInputManager::UpdateNumberJoysticks() {

    // Iterate Through All 16 Supported Joysticks
    NumberJoysticks_ = 0;
    for (int i = 0; i < 16; i++) {
        if(glfwJoystickPresent(i)) {
            NumberJoysticks_ ++;
        }
    }

}

// Update Number Axes Per Joystick
void ERS_CLASS_ControllerInputManager::UpdateNumberAxesPerJoystick() {

    // Clear JS Axes List
    JoystickAxes_.erase(JoystickAxes_.begin(), JoystickAxes_.end());

    // Iterate Through Current Number Joysticks
    for (int i = 0; i < NumberJoysticks_; i++) {
        int NumAxes;
        glfwGetJoystickAxes(i, &NumAxes);
        JoystickAxes_.push_back(NumAxes);
    }

}

// Get Data For Each Axis
void ERS_CLASS_ControllerInputManager::UpdateJoystickValues() {

    // Clear Value
    JoystickValues_.erase(JoystickValues_.begin(), JoystickValues_.end());

    // Iterate Through All Joysticks
    for (int JoystickIndex = 0; JoystickIndex < NumberJoysticks_; JoystickIndex++) {


        // Iterate Through Each Axis Of Joystick
        for (int JoystickAxis = 0; JoystickAxis < JoystickAxes_[JoystickIndex]; JoystickAxis++) {


        }


    }

}


// Update Controllers
void ERS_CLASS_ControllerInputManager::UpdateControllers() {

    // Update Data
    UpdateNumberJoysticks();
    UpdateNumberAxesPerJoystick();    

}