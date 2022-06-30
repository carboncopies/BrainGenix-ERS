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

public:
    ERS_CLASS_WindowManager();
    ~ERS_CLASS_WindowManager();


};