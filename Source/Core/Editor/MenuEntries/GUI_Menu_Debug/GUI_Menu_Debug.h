//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//


#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <vector>
#include <iostream>
#include <filesystem>
#include <string>
#include <memory>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <imgui.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_SystemUtils.h>

#include <GUI_Window_TestEditor.h>



/**
 * @brief This class provides the "File" Menu In The Editor.
 * 
 */
class GUI_Menu_Debug {


    // Member Vars
    private:

        std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<SystemUtils Instance, Used To Get Systems From Other Classes*/
        std::unique_ptr<Window_TestEditor> TestEditor_; /**<GUI Window Test Editor Instance*/

        bool ShowImGuiDemoWindow_ = false; /**<Show/hide ImGui DemoWindow*/
        bool DebugMenuEnabled_ = false; /**Enable/Disable Debug Menu*/


    // Member Functions
    public:


        /**
         * @brief Construct a new gui menu object
         * 
         * @param SystemUtils 
         */
        GUI_Menu_Debug(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils);


        /**
         * @brief Destroy the gui menu object
         * 
         */
        ~GUI_Menu_Debug();


        /**
         * @brief This function Draws The View Menu Contents.
         * 
         */
        void Draw();


};