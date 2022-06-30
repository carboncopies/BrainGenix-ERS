//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_SystemUtils.h>


/**
 * @brief This class owns all windows, and instantiates them. 
 * Additionally, it provides functionality for the layout manager to show/hide different windows.
 * Finally, it provides the functionality to draw all windows irrespective of what the menus are doing.
 * 
 */
class ERS_CLASS_WindowManager {

private:

    ERS_STRUCT_SystemUtils* SystemUtils_; /**<Pointer to System utillities struct, used to get things like logger, etc.*/

    std::vector<std::string> WindowNames_; /**<List of all understood window names, populated by constructor*/

public:

    /**
     * @brief Construct a new ers class windowmanager object
     * 
     */
    ERS_CLASS_WindowManager();

    /**
     * @brief Destroy the ers class windowmanager object
     * 
     */
    ~ERS_CLASS_WindowManager();


    /**
     * @brief Call this once per frame at the end of the GUI update process - will call the draw function on all windows in the system.
     * 
     */
    void UpdateAllWindows();

    /**
     * @brief Returns a list containing the name of all windows in the system. 
     * These names can be used to query the state of a given window, or set the state of that window.
     * 
     * @return std::vector<std::string> 
     */
    std::vector<std::string> GetWindowNames();

    /**
     * @brief Use this function to get the state of the window in question.
     * Will return true for enabled, or false for disabled.
     * 
     * @param WindowName 
     * @return true 
     * @return false 
     */
    bool GetWindowStatus(std::string WindowName);

    /**
     * @brief Enable or disable a window with this function.
     * Pass in the window's name and the state to set it to.
     * 
     * @param WindowName 
     * @param WindowStatus 
     */
    void SetWindowStatus(std::string WindowName, bool WindowStatus);

};