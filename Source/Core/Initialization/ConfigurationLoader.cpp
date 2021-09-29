//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file loads the local system configuration file.
    Additonal Notes: None
    Date Created: 2021-09-28
*/

#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>


YAML::Node LoadConfig(const char* ConfigurationPath) {

    // Read Configuration
    YAML::Node ConfigurationDictionary = YAML::LoadFile(ConfigurationPath);

    // Return Dictionary
    return ConfigurationDictionary;

}