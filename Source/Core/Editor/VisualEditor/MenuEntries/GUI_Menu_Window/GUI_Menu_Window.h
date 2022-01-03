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
#include <GUI_Widget_FrameLatencyGraph.h>
#include <GUI_Widget_ObjectProperties.h>

#include <GUI_Window_SceneTree.h>
#include <GUI_Window_SystemLog.h>

#include <ERS_Editor_3DCursor.h>
#include <ERS_SceneManager.h>


/**
 * @brief This class provides the "File" Menu In The Editor.
 * 
 */
class GUI_Menu_Window {


    // Member Vars
    private:

        std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<SystemUtils Instance, Used To Get Systems From Other Classes*/


        // Instantiate Widgets here
        Widget_FramerateCounter Widget_FramerateCounter_; /**<Widget Instance*/
        Widget_FramerateHistogram Widget_FramerateHistogram_; /**<Widget Instance*/
        Widget_FramerateGraph Widget_FramerateGraph_; /**<Widget Instance*/
        Widget_FrameratePlot Widget_FrameratePlot_; /**<Widget Instance*/
        std::unique_ptr<Widget_RenderingSettings> Widget_RenderingSettings_; /**<Widget Instance*/
        std::shared_ptr<Widget_ObjectProperties> Widget_ObjectProperties_; /**<Widget Instance*/
        std::unique_ptr<Widget_FrameLatencyGraph> Widget_FrameLatencyGraph_; /**<Widget Instance*/

        // Instantiate Windows Here
        std::shared_ptr<Window_SceneTree> Window_SceneTree_; /**<Window Instance*/
        std::unique_ptr<Window_SystemLog> Window_SystemLog_; /**<Window Instance*/

    // Member Functions
    public:


        /**
         * @brief Construct a new gui menu object
         * 
         * @param SystemUtils 
         */
        GUI_Menu_Window(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, std::shared_ptr<Cursors3D> Cursors3D, std::shared_ptr<SceneManager> SceneManager);


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