//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <vector>
#include <iostream>
#include <string>
#include <memory>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <imgui.h>


// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_SystemUtils.h>
#include <ERS_STRUCT_HumanInputDeviceUtils.h>
#include <ERS_STRUCT_ProjectUtils.h>

#include <ERS_Editor_WindowManager.h>

#include <GUI_Window_ControllerSettings.h>


/**
 * @brief This class provides the "File" Menu In The Editor.
 * 
 */
class GUI_Menu_Settings {

private:

    ERS_STRUCT_SystemUtils* SystemUtils_; /**<SystemUtils Instance, Used To Get Systems From Other Classes*/
    ERS_STRUCT_HumanInputDeviceUtils* HIDUtils_; /**<HID Utils Pointer*/
    ERS_CLASS_WindowManager* WindowManager_; /**<Class to manage the system's windows*/



public:


    /**
     * @brief Construct a new gui menu settings object
     * 
     * @param SystemUtils 
     */
    GUI_Menu_Settings(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_HumanInputDeviceUtils* HIDUtils, ERS_CLASS_WindowManager* WindowManager);


    /**
     * @brief Destroy the gui menu settings object
     * 
     */
    ~GUI_Menu_Settings();


    /**
     * @brief This function Draws The Settings Menu Contents.
     * 
     */
    void Draw();


};