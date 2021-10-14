//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the main file of the system.
    Additonal Notes: None
    Date Created: 2021-09-28
*/


#include "Core/Initialization/ConfigurationLoader.cpp"
#include "Core/Management/LoggingSystem.cpp"
#include "Core/Renderer/MainRenderingSystem.cpp"

int main() {

    // Declare Variables
    bool SystemRunning = true;


    // Load System Configuration File
    const YAML::Node SystemConfiguration = LoadConfig("Config.yaml");

    // Instantiate Logging Subsystem //
    LoggerClass sERSLogger;
    sERSLogger.InitializeLogger(SystemConfiguration);

    sERSLogger.Log("Initialized 'Management::Logger::LoggerClass'", 5);

    // Initialize Main Rendering System
    sERSLogger.Log("Initializing 'Core::Renderer::MainRenderingSystem'", 5);
    MainRenderer RenderingSystem;
    RenderingSystem.InitRenderer(sERSLogger, SystemConfiguration);
    sERSLogger.Log("Initialized 'Core::Renderer::MainRenderingSystem'", 4);


    // Main Loop
    sERSLogger.Log("Entering Main ERS Program Loop", 4);
    while (SystemRunning) {

        MainRenderer.UpdateRender();

    }


    // Call Destructors, Shutdown System
    sERSLogger.Log("System Shutdown Invoked, Calling Destructors", 5);
    MainRenderer.CleanUp();

}