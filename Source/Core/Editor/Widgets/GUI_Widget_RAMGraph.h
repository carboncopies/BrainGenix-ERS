//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <vector>
#include <iostream>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <imgui.h>
#include <implot.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_SystemUtils.h>
#include <ERS_STRUCT_HardwareInfo.h>

/**
 * @brief Create GUI Widget "Framerate Graph"
 * 
 */
class Widget_RAMGraph {

private:

    ERS_STRUCT_SystemUtils* SystemUtils_; /**<System Utils Pointer*/

    std::vector<float> TotalRAM_; /**<Total Amount Of RAM In GB In The System*/
    std::vector<float> UsedRAM_; /**<Total Amount Of RAM Used In The System*/
    std::vector<float> TotalSwap_; /**<Total Amount Of Swap In The System*/
    std::vector<float> UsedSwap_; /**<Total Amount Of Used Swap In The SYstem*/


public:

    bool Enabled_ = true; /**<Show/Hide Widget*/

public:

    /**
     * @brief Construct a new Widget_RAMGraph object
     * 
     * @param SystemUtils 
     */
    Widget_RAMGraph(ERS_STRUCT_SystemUtils* SystemUtils);
    
    /**
     * @brief Destroy the Widget_RAMGraph object
     * 
     */
    ~Widget_RAMGraph();


    /**
     * @brief Function that draws the window, should internally check if enable variable is set to true.
     * 
     */
    void Draw();


};