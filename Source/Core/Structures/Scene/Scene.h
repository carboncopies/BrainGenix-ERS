//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing scene interfacing to the rest of the system.
    Additonal Notes: None
    Date Created: 2021-11-11
*/    

#pragma once

#include <yaml-cpp/yaml.h>



struct ERS_STRUCTURE_SCENE {

    // Declare Scene Structs
    YAML::Node SceneData;
    
    // Metadata
    std::string SceneName;
    std::string FormatVersion;

    // Scene Data
    long NumberSubnodes;
    std::map<long, YAML::Node> Subnodes;


};
