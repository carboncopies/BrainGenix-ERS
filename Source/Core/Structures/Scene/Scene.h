//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file creates the scene structure.
    Documentation Status: Done
    Additonal Notes: None
    Date Created: 2021-11-22
*/

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <Model.h>



/**
 * @brief The scene structure contains the data for an entire "level". It references other models, scripts, audio, and more to construct the environment.
 * 
 */
struct ERS_OBJECT_SCENE{

    // Raw Info Yaml
    YAML::Node SceneData; /**<YAML::Node Containing Copy Of Raw Scene Information*/

    // List Of Required Materials (For Now, Can Only Be Models)
    std::vector<std::shared_ptr<ERS_OBJECT_MODEL>> Models; /**<List of models currently loading. Will attempt to render anyway unless manually suppressed*/

    // Model That's Currently Selected
    int SelectedModel = 0; /**<The Model That Is Currently Selected*/
    bool HasSelectionChanged = true; /**<Indicates if the selected item(s) have changed*/

    // Scene Metadata
    long SceneFormatVersion; /**<Sets The Current Scene Version (from File/DB Entry), determines If System Can Load It*/
    std::string SceneName; /**<Metadata Setting Scene Name From It's Scene File/DB Entry*/
    long ScenePath; /**<String containing asset path*/

    // Status Variables
    bool IsSceneLoaded = false; /**<Status Variable Indiciating If The Scene Can Be Rendered Yet, Or If It's Yet To Be Loaded/Still Loading*/

};