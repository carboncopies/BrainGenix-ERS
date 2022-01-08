//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for providing a system for getting joystick input and adding it to the input struct.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2022-01-08
*/

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glad/glad.h>

#include <GLFW/glfw3.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_SystemUtils.h>


/**
 * @brief Get and update all joystick input devices, as well as associated controller buttons
 * 
 */
class ERS_CLASS_ControllerInputManager {

private:

    std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<Pointer to SystemUtils Struct*/

private:

    void UpdateNumberJoysticks(); /**<Updates the number of Joysticks present.*/
    void UpdateNumberAxesPerJoystick(); /**<Updates Number Of Axes Per Joystick*/
    void UpdateJoystickValues(); /**<Updates the values for every joystick axis*/

public:

    int NumberJoysticks_ = 0; /**<Current Number Of Detected Joysticks*/
    std::vector<int> JoystickAxes_; /**<Number of axes per joystick*/
    std::vector<std::vector<int>> JoystickValues_; /**<Values for each axis of each joystick*/


public:

    /**
     * @brief Construct a new ers class ControllerInputManager object
     * 
     * @param SystemUtils 
     */
    ERS_CLASS_ControllerInputManager(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils);

    /**
     * @brief Destroy the ers class ControllerInputManager object
     * 
     */
    ~ERS_CLASS_ControllerInputManager();


    /**
     * @brief Call this every frame, updates public member vars such as JS position, buttons, etc.
     * 
     */
    void UpdateControllers();



};