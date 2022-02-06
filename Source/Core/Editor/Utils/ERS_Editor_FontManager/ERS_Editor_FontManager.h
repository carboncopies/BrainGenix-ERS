//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <vector>
#include <iostream>
#include <filesystem>
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_CLASS_LoggingSystem.h>


/**
 * @brief Load, parse, and apply fonts to ImGui.
 * 
 */
class ERS_CLASS_FontManager {

    private:

        std::shared_ptr<ERS_CLASS_LoggingSystem> Logger_; /**<ERS_CLASS_LoggingSystem Instance Pointer*/
        const char* FontsDirectoryPath_; /**<Path where fonts are to be searched for */

        std::vector<std::string> FontPathList_; /**<List of fonts located at the given paths*/
        std::vector<std::string> FontNameList_; /**<List of font names for gui rendering*/
        
        float FontSize_ = 14; /**<Set Default Font Size In Pixels*/
        int FontSelector_ = 0; /**<Set Font Selector Int*/
        bool UpdateFont_ = false; /**<Indicate If Font Needs To Be Updated*/

        bool EndsWith(const std::string& Input, const std::string& Ending);

    public:

        ERS_CLASS_FontManager(std::shared_ptr<ERS_CLASS_LoggingSystem> Logger, const char* FontsDirPath = "EditorAssets/Fonts");
        ~ERS_CLASS_FontManager();

        void IndexFonts();
        void UseFont(int FontIndex);
        void UseFont(std::string FontName);
        void SetFontSize(float FontSize);
        void FontSelectorWindow(bool *WindowEnabled);
        void CheckUpdateFont();

};