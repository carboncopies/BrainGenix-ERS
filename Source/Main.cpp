//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the main file of the system.
    Additonal Notes: None
    Date Created: 2021-09-28
*/

#include "Core/Initialization/ConfigurationLoader.cpp"

int main() {

    // Load System Configuration File
    const YAML::Node SystemConfiguration = LoadConfig("Config.yaml");

}