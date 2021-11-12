//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the main file of the system.
    Additonal Notes: None
    Date Created: 2021-11-01
*/

#include "Core/Loader/Configuration/ConfigurationLoader.h"
#include "Core/Management/LoggingSystem.h"
#include "Core/Renderer/Renderer.h"

#include "Core/Structures/DataBuffer/DataBuffer.h"

int main() {



    

    // Load System Configuration File
    YAML::Node SystemConfiguration = LoadConfig("Config.yaml");

    // Instantiate Logging Subsystem //
    LoggerClass sERSLogger;
    sERSLogger.InitializeLogger(SystemConfiguration);

    sERSLogger.Log("Initialized 'Management::Logger::LoggerClass'", 5);


    // ERS_STRUCTURE_DATA_BUFFER Test;
    // Test.Init(&sERSLogger);
    // Test.AddToBuffer((long)1, 0);
    // std::cout<<*Test.PullFromBuffer(0)<<std::endl;

    // Initialize Renderer
    Renderer sERSRenderer;
    sERSLogger.Log("Initializing Renderer", 5);
    sERSRenderer.InitializeRenderer(&SystemConfiguration, &sERSLogger);
    sERSLogger.Log("Initialized Renderer", 5);

    // Enter Main Loop
    bool SystemShouldRun = true;
    while (SystemShouldRun) {

        SystemShouldRun = sERSRenderer.UpdateLoop();

    }

    // Cleanup
    sERSRenderer.CleanUp();

}