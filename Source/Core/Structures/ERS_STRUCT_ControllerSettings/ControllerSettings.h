//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")


/**
 * @brief Used to remap buttons, adjust gains, set thresholds, etc. User adjustable controller settings.
 * 
 */
struct ERS_STRUCT_ControllerSettings {

    // Controller Settings Name
    std::string SettingsProfileName = "Default Layout"; /**<Name of this profile. Shows in dropdown menu*/
    std::string ControllerName = "*"; /**<Name of the controller to apply this profile to*/

    // Joystick Settings
    float MinThresholdJoystickLeftX = 0.0f; /**<Minimum value from joystick to be considered a value*/
    float MinThresholdJoystickLeftY = 0.0f; /**<Minimum value from joystick to be considered a value*/
    float MinThresholdJoystickRightX = 0.0f; /**<Minimum value from joystick to be considered a value*/
    float MinThresholdJoystickRightY = 0.0f; /**<Minimum value from joystick to be considered a value*/

    float MaxThresholdJoystickLeftX = 1.0f; /**<Maximum value from joystick before JS is fully on*/
    float MaxThresholdJoystickLeftY = 1.0f; /**<Minimum value from joystick to be considered a value*/
    float MaxThresholdJoystickRightX = 1.0f; /**<Minimum value from joystick to be considered a value*/
    float MaxThresholdJoystickRightY = 1.0f; /**<Minimum value from joystick to be considered a value*/

    float JoystickLeftXGain = 1.0f; /**<Joystick Gain*/
    float JoystickLeftYGain = 1.0f; /**<Joystick Gain*/
    float JoystickRightXGain = 1.0f; /**<Joystick Gain*/
    float JoystickRightYGain = 1.0f; /**<Joystick Gain*/

    // Trigger Settings
    float MinThresholdTriggerLeft = 0.0f; /**<Minimum value from trigger to be considered valid, all values below this are discarded*/
    float MinThresholdTriggerRight = 0.0f; /**<Minimum value from trigger to be considered valid, all values below this are discarded*/
    
    float MaxThresholdTriggerLeft = 1.0f; /**<Max value for trigger to be fully pressed*/
    float MaxThresholdTriggerRight = 1.0f; /**<Max value for trigger to be fully pressed*/

    // Button Remap
    int TriangleButtonIndex = 3; /**<Button Index*/
    int SquareButtonIndex = 2; /**<Button Index*/
    int CrossButtonIndex = 0; /**<Button Index*/
    int CircleButtonIndex = 1;/**<Button Index*/
    int BackButtonIndex = 6; /**<Button Index*/
    int OptionsButtonIndex = 8; /**<Button Index*/
    int MenuButtonIndex = 7; /**<Button Index*/
    int JoystickRightButtonIndex = 10; /**<Button Index*/
    int JoystickLeftButtonIndex = 9; /**<Button Index*/
    int LeftBumperButtonIndex = 4; /**<Button Index*/
    int RightBumperButtonIndex = 5; /**<Button Index*/
    int DPADUpButtonIndex = 11; /**<Button Index*/
    int DPADDownButtonIndex = 12; /**<Button Index*/
    int DPADLeftButtonIndex = 13; /**<Button Index*/
    int DPADRightButtonIndex = 14; /**<Button Index*/

};
