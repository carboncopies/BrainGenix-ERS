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
    std::cout << "Initializing System\n";
    std::cout << "Loading Logger Configuration File\n";
    const YAML::Node LoggerConfigration = LoadConfig("Config/LoggerConfig.yaml");


    // Instantiate Logger //
    std::cout << "Instantiating Logging System\n";
    Logger mLogger;
    mLogger.InitializeLogger();

    mLogger.Log("Logger Instantiation Successfull", 0);


    // Load Remaining Configuration Files //
    mLogger.Log("Loading Remaining Configuration Files");

    mLogger.Log("Loading WindowSystem Configuration File");
    const YAML::Node LocalWindowConfiguration = LoadConfig("Config/WindowSystemConfig.yaml");

    mLogger.Log("Done Loading Configuration Files");





    // Program Exit //
    return 0;
}