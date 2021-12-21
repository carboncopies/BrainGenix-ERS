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
#include <filesystem>
#include <string>
#include <memory>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <imgui.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_SystemUtils.h>



/**
 * @brief This class provides the "File" Menu In The Editor.
 * 
 */
class GUI_Menu_Debug {


    // Member Vars
    private:

        std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<SystemUtils Instance, Used To Get Systems From Other Classes*/

        bool ShowImGuiDemoWindow_ = false; /**<Show/hide ImGui DemoWindow*/


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