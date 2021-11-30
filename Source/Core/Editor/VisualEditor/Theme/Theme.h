//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file provides theme loading functionality..
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-11-29
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
 * @brief This class provides functionality to load and apply themes from yaml files.
 * 
 */
class ThemeManager {


    private:

        LoggerClass *Logger_; /**<LoggerClass Instance*/
        const char* ThemePath_; /**<Filepath Where Themes Are Located*/

        std::vector<std::string> ThemeNames_; /**<List of theme names (based on filename)*/
        std::vector<YAML::Node> ThemeFiles_; /**<List Of YAML::Node files*/



    public:

        ThemeManager(LoggerClass *Logger_, const char* ThemePath = "EditorAssets/Configuration/Themes");
        ~ThemeManager();

        void LoadThemes();
        void CreateThemeMenu();
        void ApplyThemes(int ThemeID);


};