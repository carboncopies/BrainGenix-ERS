//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing the configuration loading classes.
    Additonal Notes: None
    Date Created: 2021-05-31
*/ 

#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>


YAML::Node LoadConfig(const char* ConfigurationPath) {

    // Read Configuration //
    YAML::Node ConfigurationDictionary = YAML::Load(ConfigurationPath);

    // Return Dictionary //
    return ConfigurationDictionary;

}