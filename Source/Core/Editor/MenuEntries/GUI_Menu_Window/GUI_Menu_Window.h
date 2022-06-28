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
#include <ERS_CLASS_VisualRenderer.h>

#include <ERS_STRUCT_SystemUtils.h>
#include <ERS_STRUCT_ProjectUtils.h>

#include <GUI_Widget_FramerateCounter.h>
#include <GUI_Window_RenderingSettings.h>
#include <GUI_Widget_FramerateHistogram.h>
#include <GUI_Window_FramerateGraph.h>
#include <GUI_Widget_FrameratePlot.h>
#include <GUI_Window_FrameLatencyGraph.h>
#include <GUI_Window_ObjectProperties.h>
#include <GUI_Window_RAMGraph.h>

#include <GUI_Window_SceneTree.h>
#include <GUI_Window_SystemLog.h>
#include <GUI_Window_AssetExplorer.h>
#include <GUI_Window_ScriptEditor.h>

#include <ERS_Editor_3DCursor.h>
#include <ERS_SceneManager.h>


/**
 * @brief This class provides the "File" Menu In The Editor.
 * 
 */
class GUI_Menu_Window {


private:

    ERS_STRUCT_SystemUtils* SystemUtils_; /**<SystemUtils Instance, Used To Get Systems From Other Classes*/
    ERS_STRUCT_ProjectUtils* ProjectUtils_; /**<Project Utils Instance*/

    // Instantiate Widgets here
    Widget_FramerateCounter Widget_FramerateCounter_; /**<Widget Instance*/
    Widget_FramerateHistogram Widget_FramerateHistogram_; /**<Widget Instance*/
    GUI_Window_FramerateGraph GUI_Window_FramerateGraph_; /**<Widget Instance*/
    Widget_FrameratePlot Widget_FrameratePlot_; /**<Widget Instance*/

    std::unique_ptr<GUI_Window_RAMGraph> GUI_Window_RAMGraph_; /**<Widget Instance*/
    std::unique_ptr<GUI_Window_RenderingSettings> GUI_Window_RenderingSettings_; /**<Widget Instance*/
    std::unique_ptr<GUI_Window_ObjectProperties> GUI_Window_ObjectProperties_; /**<Widget Instance*/
    std::unique_ptr<Widget_FrameLatencyGraph> Widget_FrameLatencyGraph_; /**<Widget Instance*/

    // Instantiate Windows Here
    std::unique_ptr<Window_SceneTree> Window_SceneTree_; /**<Window Instance*/
    std::unique_ptr<Window_SystemLog> Window_SystemLog_; /**<Window Instance*/
    std::unique_ptr<Window_AssetExplorer> Window_AssetExplorer_; /**<Window Instance*/
    std::unique_ptr<Window_ScriptEditor> Window_ScriptEditor_; /**Window Instance*/
    ERS_CLASS_VisualRenderer* VisualRenderer_; /**<ERS_CLASS_VisualRenderer instance*/


public:


    /**
     * @brief Construct a new gui menu object
     * 
     * @param SystemUtils 
     */
    GUI_Menu_Window(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils, Cursors3D* Cursors3D, ERS_CLASS_SceneManager* SceneManager, ERS_CLASS_VisualRenderer* VisualRendererInstance);


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