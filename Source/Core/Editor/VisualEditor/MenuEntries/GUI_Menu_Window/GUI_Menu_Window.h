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

#include <GUI_Widget_FramerateCounter.h>
#include <GUI_Widget_RenderingSettings.h>
#include <GUI_Widget_FramerateHistogram.h>
#include <GUI_Widget_FramerateGraph.h>
#include <GUI_Widget_FrameratePlot.h>
#include <GUI_Widget_ObjectProperties.h>

#include <GUI_Window_SceneTree.h>

#include <3DCursor.h>


/**
 * @brief This class provides the "File" Menu In The Editor.
 * 
 */
class GUI_Menu_Window {


    // Member Vars
    private:

        ERS_STRUCT_SystemUtils SystemUtils_; /**<SystemUtils Instance, Used To Get Systems From Other Classes*/


    // Member Functions
    public:


        /**
         * @brief Construct a new gui menu object
         * 
         * @param SystemUtils 
         */
        GUI_Menu_Window(ERS_STRUCT_SystemUtils SystemUtils, std::shared_ptr<Cursors3D> Cursors3D);


        /**
         * @brief Destroy the gui menu object
         * 
         */
        ~GUI_Menu_Window();


        /**
         * @brief This function Draws The View Menu Contents.
         * 
         */
        void Draw();


};