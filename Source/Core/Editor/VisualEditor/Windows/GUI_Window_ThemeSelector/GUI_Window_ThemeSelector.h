//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This Window file is responsible for creating a system Window.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-17
*/

#pragma once


// Standard Libraries (BG convention: use <> instead of "")

// Third-Party Libraries (BG convention: use <> instead of "")
#include <imgui.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_Editor_ThemeManager.h>


/**
 * @brief This Class Provides The Theme Selector Window.
 * 
 */
class Window_ThemeSelector {


    // Private Member Vars
    private:

        std::shared_ptr<ERS_CLASS_ThemeManager> ThemeManager_; /**<Theme Manager Instance*/


    // Public Member Vars
    public:

        bool Enabled_; /**<Show/Hide Window*/


    // Public Member Functions
    public:

        /**
         * @brief Construct a new Window_ThemeSelector object
         * 
         * @param ThemeManager 
         */
        Window_ThemeSelector(std::shared_ptr<ERS_CLASS_ThemeManager> ThemeManager);

        /**
         * @brief Destroy the Window_ThemeSelector object
         * 
         */
        ~Window_ThemeSelector();

        /**
         * @brief Update the window contents, Call This Every Frame.
         * 
         */
        void Draw();



};