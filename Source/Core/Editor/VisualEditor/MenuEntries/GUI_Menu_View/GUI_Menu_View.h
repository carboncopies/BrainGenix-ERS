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

#include <ERS_Editor_ThemeManager.h>
#include <ERS_Editor_FontManager.h>

#include <GUI_Window_ThemeSelector.h>




/**
 * @brief This class provides the "File" Menu In The Editor.
 * 
 */
class GUI_Menu_View {


    // Member Vars
    private:

        std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<SystemUtils Instance, Used To Get Systems From Other Classes*/
        std::shared_ptr<ERS_CLASS_ThemeManager> ThemeManager_; /**<Theme Manager Instance Ptr*/
        std::unique_ptr<Window_ThemeSelector> Window_ThemeSelector_; /**<Theme Selector Window*/
        std::shared_ptr<ERS_CLASS_FontManager> FontManager_; /**<Pointer To FontManager Instance*/

        // Window Show/Hide Vars
        bool ShowFontPicker_ = false; /**<Control Varaible to show/hide font picker window*/


    // Member Functions
    public:


        /**
         * @brief Construct a new gui menu object
         * 
         * @param SystemUtils 
         */
        GUI_Menu_View(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, std::shared_ptr<ERS_CLASS_ThemeManager> ThemeManager, std::shared_ptr<ERS_CLASS_FontManager> FontManager);


        /**
         * @brief Destroy the gui menu object
         * 
         */
        ~GUI_Menu_View();


        /**
         * @brief This function Draws The View Menu Contents.
         * 
         */
        void Draw();


};