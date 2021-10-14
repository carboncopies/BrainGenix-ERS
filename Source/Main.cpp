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
#include "Core/Renderer/Visual/VisualRenderer.h"

int main() {

    // Load System Configuration File
    const YAML::Node SystemConfiguration = LoadConfig("Config.yaml");

    // Instantiate Logging Subsystem //
    LoggerClass sERSLogger;
    sERSLogger.InitializeLogger(SystemConfiguration);

    sERSLogger.Log("Initialized 'Management::Logger::LoggerClass'", 5);

    // Initialize Graphics Subsystem
    VisualRenderer sERSVisualRenderer;
    sERSVisualRenderer.InitializeSystem(sERSLogger);
    sERSLogger.Log("Initialized 'Renderer::Visual::VisualRenderer'", 5);


}