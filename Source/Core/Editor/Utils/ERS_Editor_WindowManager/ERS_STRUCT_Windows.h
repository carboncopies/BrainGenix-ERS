//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <memory.h>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <GUI_Window_About.h>
#include <GUI_Window_AssetExplorer.h>
#include <GUI_Window_ControllerSettings.h>
#include <GUI_Window_FrameLatencyGraph.h>
#include <GUI_Window_FramerateCounter.h>
#include <GUI_Window_FramerateGraph.h>
#include <GUI_Window_FramerateHistogram.h>
#include <GUI_Window_FrameratePlot.h>
#include <GUI_Window_ImportProgressBar.h>
#include <GUI_Window_ObjectProperties.h>
#include <GUI_Window_ProjectSettings.h>
#include <GUI_Window_RAMGraph.h>
#include <GUI_Window_RenderingSettings.h>
#include <GUI_Window_SceneTree.h>
#include <GUI_Window_ScriptEditor.h>
#include <GUI_Window_ShaderEditor.h>
#include <GUI_Window_SystemLog.h>
#include <GUI_Window_TestEditor.h>
#include <GUI_Window_ThemeSelector.h>

/**
 * @brief This structure holds unique pointers to all windows that are instantiated by the GUI.
 * When adding a new window, add a unique_ptr here and update the WindowManager as well so that it's updated every frame.
 * 
 */
struct ERS_STRUCT_Windows {



};