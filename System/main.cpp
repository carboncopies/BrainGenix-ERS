//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing the main server-side binary of the system.
    Additonal Notes: None
    Date Created: 2021-05-30
*/


#include <iostream>
#include <string>

#include <yaml-cpp/yaml.h>


#include "Core/LocalWindowSystem/LocalWindowSystemModule.cpp"
#include "Core/Management/Logger/LoggerModule.cpp"
#include "Core/Initialization/ConfigurationLoader/ConfigurationLoaderModule.cpp"


int main(){

    // Load Configration File For Logger //
    const YAML::Node LoggerConfigration = LoadConfig("Config/LoggerConfig.yaml");

    // Instantiate
    Logger mLogger;
    mLogger.InitializeLogger();

    mLogger.Log("Test", 0);



    return 0;
}