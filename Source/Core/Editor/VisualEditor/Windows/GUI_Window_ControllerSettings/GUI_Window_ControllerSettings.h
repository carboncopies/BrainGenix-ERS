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


/**
 * @brief Window for the Import progress bar.
 * 
 */
class Window_ControllerSettings {

    private:

        std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<Pointers To System Resources*/
        std::shared_ptr<ERS_STRUCT_HumanInputDeviceUtils> HIDUtils_; /**<Pointer To Human Input Device Info*/


    public:

        bool Enabled_ = false; /**<Is Popup Enabled*/


    public:

        /**
         * @brief Construct a new Window_ControllerSettings object
         * 
         */
        Window_ControllerSettings(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, std::shared_ptr<ERS_STRUCT_HumanInputDeviceUtils> HIDUtils);
        
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