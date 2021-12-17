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

        std::shared_ptr<LoggerClass> Logger_; /**<LoggerClass Instance*/
        const char* ThemePath_; /**<Filepath Where Themes Are Located*/

        std::vector<YAML::Node> ThemeFiles_; /**<List Of YAML::Node files*/

        ImVec4 ReadColor(const char* NodeName, YAML::Node Target); /**<Reads A Color From The Config*/


    public:

        ImVec4 ClearColor_; /**Set Clear Color For Background*/
        std::vector<std::string> ThemeNames_; /**<List of theme names (based on filename)*/

        /**
         * @brief Construct a new Theme Manager object
         * 
         * @param Logger_ 
         * @param ThemePath 
         */
        ThemeManager(std::shared_ptr<LoggerClass> Logger, const char* ThemePath = "EditorAssets/Configuration/Themes");

        /**
         * @brief Destroy the Theme Manager object
         * 
         */
        ~ThemeManager();

        

        /**
         * @brief Load themes from disk
         * 
         */
        void LoadThemes();

        /**
         * @brief Create the theme menu
         * 
         */
        //FIXME: MOVE MENU UPDATE FUNCTION OUT OF GUP INTO THIS FUNCTION!!!!
        void CreateThemeMenu();

        /**
         * @brief Apply the selected theme
         * 
         * @param ThemeID 
         */
        void ApplyThemes(int ThemeID);

        /**
         * @brief Apply the selected theme
         * 
         * @param ThemeName 
         */
        void ApplyThemes(const char* ThemeName);

};