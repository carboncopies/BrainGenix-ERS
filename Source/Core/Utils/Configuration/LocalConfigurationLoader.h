//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing the configuration loading classes.
    Documentation Status: No Docs Added.
    Additonal Notes: None
    Date Created: 2021-05-31
*/ 

#pragma once

#include <string>
#include <yaml-cpp/yaml.h>

/** breif LoadConfig - Loads and parses YAML file.
 * details This functions read and parsea a yaml file.
 * You'll need a 
static YAML::Node LoadConfig(const char* ConfigurationPath) {

    // Read Configuration //
    YAML::Node ConfigurationDictionary = YAML::LoadFile(ConfigurationPath);

    // Return Dictionary //
    return ConfigurationDictionary;

}