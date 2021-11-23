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

/**
 * @brief The scene structure contains the data for an entire "level". It references other models, scripts, audio, and more to construct the environment.
 * 
 */
struct Scene{

    YAML::Node SceneData; /**<YAML::Node Containing Copy Of Raw Scene Information*/

    


};