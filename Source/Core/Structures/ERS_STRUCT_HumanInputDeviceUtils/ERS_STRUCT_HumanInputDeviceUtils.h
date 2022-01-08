//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for implementing the human input device managers struct.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2022-01-08
*/

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <vector>
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_ControllerInputManager.h>


/**
 * @brief This system is responsible for getting controller input
 * 
 */
struct ERS_STRUCT_HumanInputDeviceUtils {


    std::shared_ptr<ERS_CLASS_ControllerInputManager> ControllerInputManager; /**<Pointer to ERS Controller Input Manager*/


};