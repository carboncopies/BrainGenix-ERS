//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file provides a GUI menu entry.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-17
*/

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


/**
 * @brief This class provides the "File" Menu In The Editor.
 * 
 */
class GUI_Menu_Settings {

    // Member Vars
    private:

        std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<SystemUtils Instance, Used To Get Systems From Other Classes*/
        std::shared_ptr<ERS_STRUCT_HumanInputDeviceUtils> HIDUtils_; /**<HID Utils Pointer*/

    // Member Functions
    public:


        /**
         * @brief Construct a new gui menu settings object
         * 
         * @param SystemUtils 
         */
        GUI_Menu_Settings(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils,  std::shared_ptr<ERS_STRUCT_HumanInputDeviceUtils> HIDUtils);


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