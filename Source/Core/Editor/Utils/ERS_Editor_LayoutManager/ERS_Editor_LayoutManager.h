//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_CLASS_LoggingSystem.h>


/**
 * @brief Creates the user profile manager class.
 * 
 */
class ERS_CLASS_LayoutManager {


private:

    ERS_CLASS_LoggingSystem* Logger_; /**<ERS_CLASS_LoggingSystem Instance Pointer*/
    std::string LayoutDirectory_; /**<This string stores the path to the editor's layout directory ending in a trailing slash*/

public:

    /**
     * @brief Construct a new User Profile Manager object
     * 
     * @param Logger 
     */
    ERS_CLASS_LayoutManager(ERS_CLASS_LoggingSystem* Logger, const char* LayoutDirectory = "EditorAssets/Layouts/");

    /**
     * @brief Destroy the User Profile Manager object
     * 
     */
    ~ERS_CLASS_LayoutManager();


    /**
     * @brief This method indexs all yaml files within the specified layout directory.
     * This dir path is specified in the constructor. 
     * Returns false on fail and true on success.
     * 
     */
    bool IndexConfigs();

};