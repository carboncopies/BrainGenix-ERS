//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This widget file is responsible for creating a system widget.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-28
*/

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <vector>
#include <iostream>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <imgui.h>
#include <implot.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_SystemUtils.h>

/**
 * @brief Create GUI Widget "Framerate Graph"
 * 
 */
class Widget_FrameLatencyGraph {

private:

    std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<System Utils Pointer*/

public:

    // Show/Hide Var
    bool Enabled_ = true; /**<Show/Hide Widget*/

public:

    /**
     * @brief Construct a new Widget_FrameLatencyGraph object
     * 
     * @param SystemUtils 
     */
    Widget_FrameLatencyGraph(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils);
    
    /**
     * @brief Destroy the Widget_FrameLatencyGraph object
     * 
     */
    ~Widget_FrameLatencyGraph();


    /**
     * @brief Function that draws the window, should internally check if enable variable is set to true.
     * 
     */
    void Draw();


};