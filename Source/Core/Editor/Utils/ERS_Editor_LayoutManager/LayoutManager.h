
//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <string>
#include <filesystem>
#include <imgui.h>
#include <fstream>
#include <map>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <BG/Common/Logger/Logger.h>
#include <SystemUtils.h>
#include <WindowManager.h>


struct ERS_STRUCT_EditorLayout {
    int index;
    std::string name;
    std::string IniString;

    std::map<std::string, bool> WindowNameStatus;
};

/**
 * @brief Creates the user profile manager class.
 *
 */
class ERS_CLASS_LayoutManager {


private:

    ERS_STRUCT_SystemUtils*  SystemUtils_   = nullptr; /**<Pointer to System utillities struct, used to get things like logger, etc.*/
    BG::Common::Logger::LoggingSystem* Logger_        = nullptr; /**<ERS_CLASS_LoggingSystem Instance Pointer*/
    ERS_CLASS_WindowManager* WindowManager_ = nullptr; /**<Window Manager Class Instance*/
    
    std::string LayoutDirectory_; /**<This string stores the path to the editor's layout directory ending in a trailing slash*/
    std::string ActiveLayoutName_; /**<Name of the currentl layout that's applied to the editor*/


    std::vector<YAML::Node> LayoutFiles_; /**<List Of YAML::Node files*/
    int Index = 0; /**<The index of Layout structs*/

public:

    std::vector<std::string> LayoutNames_; /**<List of layout display names (based on display name entry in YAML file)*/
    std::vector<ERS_STRUCT_EditorLayout> Layouts_; /**<List of Layout structs that store the layouts*/

    /**
     * @brief Construct a new Layout Manager object
     *
     * @param Logger
     * @param WindowManager
     * @param LayoutDirectory
     */
    ERS_CLASS_LayoutManager(BG::Common::Logger::LoggingSystem* Logger, const char* LayoutDirectory = "EditorAssets/Layouts/");

    /**
     * @brief Destroy the Layout Manager object
     *
     */
    ~ERS_CLASS_LayoutManager();

    /**
    * @brief Save the current layout the user is using.
    *  It will return the set YAML string for the layout
    */
    void SaveLayout(std::string LayoutName);

    /**
    * @brief Load layouts from disk.
    */
    void LoadLayouts();

    /**
    * @brief Apply the selected layout.
    *
    * @param LayoutID
    */
    void ApplyLayout(int LayoutID);

    /**
    * @brief Apply the selected layout.
    *
    * @param LayoutName
    */
    void ApplyLayout(std::string LayoutName);

    /**
     * @brief Returns the name of the active layout.
     * 
     * @return std::string 
     */
    std::string GetActiveLayoutName();

    /**
     * @brief Returns a list of names for all layouts.
     * 
     * @return std::vector<std::string> 
     */
    std::vector<std::string> GetLayoutNames();

    /**
     * @brief Creates a new layout and adds it to the editor's layout choices.
     * 
     * @param Name 
     */
    void CreateLayout(std::string Name);

};