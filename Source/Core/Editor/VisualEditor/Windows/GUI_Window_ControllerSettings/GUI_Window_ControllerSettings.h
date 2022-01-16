//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This Window file is responsible for creating a system Window.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-17
*/

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <memory>
#include <thread>
#include <string>
#include <mutex>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <imgui.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_SystemUtils.h>
#include <ERS_STRUCT_HumanInputDeviceUtils.h>
#include <ERS_STRUCT_ProjectUtils.h>


/**
 * @brief Used to remap buttons, adjust gains, set thresholds, etc. User adjustable controller settings.
 * 
 */
struct ControllerSettings {

    // Joystick Settings
    float MinThresholdJoystickLeftX; /**<Minimum value from joystick to be considered a value*/
    float MinThresholdJoystickLeftY; /**<Minimum value from joystick to be considered a value*/
    float MinThresholdJoystickRightX; /**<Minimum value from joystick to be considered a value*/
    float MinThresholdJoystickRightY; /**<Minimum value from joystick to be considered a value*/

    float MaxThresholdJoystickLeftX; /**<Maximum value from joystick before JS is fully on*/
    float MaxThresholdJoystickLeftY; /**<Minimum value from joystick to be considered a value*/
    float MaxThresholdJoystickRightX; /**<Minimum value from joystick to be considered a value*/
    float MaxThresholdJoystickRightY; /**<Minimum value from joystick to be considered a value*/

    float JoystickLeftXGain; /**<Joystick Gain*/
    float JoystickLeftYGain; /**<Joystick Gain*/
    float JoystickRightXGain; /**<Joystick Gain*/
    float JoystickRightYGain; /**<Joystick Gain*/

    // Trigger Settings
    float MinThresholdTriggerLeft; /**<Minimum value from trigger to be considered valid, all values below this are discarded*/
    float MinThresholdTriggerRight; /**<Minimum value from trigger to be considered valid, all values below this are discarded*/
    
    float MaxThresholdTriggerLeft; /**<Max value for trigger to be fully pressed*/
    float MaxThresholdTriggerRight; /**<Max value for trigger to be fully pressed*/

    // Button Remap
    int TriangleButtonIndex; /**<Button Index*/
    int SquareButtonIndex; /**<Button Index*/
    int CrossButtonIndex; /**<Button Index*/
    int CircleButtonIndex;/**<Button Index*/
    int BackButtonIndex; /**<Button Index*/
    int OptionsButtonIndex; /**<Button Index*/
    int MenuButtonIndex; /**<Button Index*/
    int JoystickRightButtonIndex; /**<Button Index*/
    int JoystickLeftButtonIndex; /**<Button Index*/
    int LeftBumperButtonIndex; /**<Button Index*/
    int RightBumperButtonIndex; /**<Button Index*/

};


/**
 * @brief Window for the Import progress bar.
 * 
 */
class Window_ControllerSettings {

    private:

        std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<Pointers To System Resources*/
        std::shared_ptr<ERS_STRUCT_HumanInputDeviceUtils> HIDUtils_; /**<Pointer To Human Input Device Info*/
        std::shared_ptr<ERS_STRUCT_ProjectUtils> ProjectUtils_; /**<Project Utils Pointer Struct*.


        const char* ControllerNames_[16]; /**<List Of Controller Names*/
        int SelectedController_ = 0; /**<Active Selected Controller*/


    private:
        
        /**
         * @brief Draws ImGui Text For Pressed/Released
         * 
         * @param ButtonName 
         * @param ButtonState 
         */
        void ButtonText(std::string ButtonName, bool ButtonState);

    public:

        bool Enabled_ = false; /**<Is Popup Enabled*/


    public:

        /**
         * @brief Construct a new Window_ControllerSettings object
         * 
         */
        Window_ControllerSettings(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, std::shared_ptr<ERS_STRUCT_HumanInputDeviceUtils> HIDUtils, std::shared_ptr<ERS_STRUCT_ProjectUtils> ProjectUtils);
        
        /**
         * @brief Destroy the Window_ControllerSettings object
         * 
         */
        ~Window_ControllerSettings();


        /**
         * @brief Draw import bar if needed (call every frame)
         * 
         */
        void Draw();

};