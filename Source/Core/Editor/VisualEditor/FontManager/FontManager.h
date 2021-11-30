//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file provides font loading/selecting functionality.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-11-30
*/

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <vector>
#include <iostream>
#include <filesystem>
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

#include <imgui.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>


/**
 * @brief Load, parse, and apply fonts to ImGui.
 * 
 */
class FontManager {

    private:

        LoggerClass *Logger_; /**<LoggerClass Instance Pointer*/
        const char* FontsDirectoryPath_; /**<Path where fonts are to be searched for */

        std::vector<std::string> FontPathList_; /**<List of fonts located at the given paths*/
        std::vector<std::string> FontNameList_; /**<List of font names for gui rendering*/
        
        int FontSize_ = 14; /**<Set Default Font Size In Pixels*/


        bool EndsWith(const std::string& Input, const std::string& Ending);

    public:

        FontManager(LoggerClass *Logger, const char* FontsDirPath = "EditorAssets/Fonts");
        ~FontManager();

        void IndexFonts();
        void UseFont(int FontIndex);
        void FontSelectorWindow(bool *WindowEnabled);

};