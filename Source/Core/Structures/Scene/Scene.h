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
    std::vector<ERS_OBJECT_MODEL> Models;

    // Scene Metadata
    long SceneFormatVersion;
    std:string SceneName;
    

    // Status Variables
    bool IsSceneReadyToLoad = false;
    bool IsSceneLoaded = false;


    /**
     * @brief Populate The Scene Structure, Fill In Vectors, etc. Should Be Called Before Sending Scene Struct To ModelLoader.
     * 
     * @param RawSceneData 
     */
    void ProcessScene(YAML::Node RawSceneData);


};