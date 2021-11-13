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

#define PROJECT_NAME "@PROJECT_NAME@"
#define PROJECT_VERSION  "@PROJECT_VERSION@"
#define PROJECT_VERSION_MAJOR "@PROJECT_VERSION_MAJOR@"
#define PROJECT_VERSION_MINOR "@PROJECT_VERSION_MINOR@"
#define PTOJECT_VERSION_PATCH "@PROJECT_VERSION_PATCH@"

int main() {



    

    // Load System Configuration File
    YAML::Node SystemConfiguration = LoadConfig("Config.yaml");

    // Instantiate Logging Subsystem //
    LoggerClass sERSLogger;
    sERSLogger.InitializeLogger(SystemConfiguration);

    sERSLogger.Log("Initialized 'Management::Logger::LoggerClass'", 5);



    // Initialize Renderer
    Renderer sERSRenderer;
    sERSLogger.Log("Initializing Renderer", 5);
    sERSRenderer.InitializeRenderer(&SystemConfiguration, &sERSLogger);
    sERSLogger.Log("Initialized Renderer", 5);


    // Log Logo Text
    sERSLogger.Log("Starting BrainGenix-ERS Instance", 2);
    sERSLogger.Log("", 5);
    sERSLogger.Log("---------------------------------------------------------------------------", 5);
    sERSLogger.Log("\x1b[38;2;0;128;55m██████╗ ██████╗  █████╗ ██╗███╗   ██╗\x1b[38;2;130;68;208m ██████╗ ███████╗███╗   ██╗██╗██╗  ██╗", 5);
    sERSLogger.Log("\x1b[38;2;0;128;55m██╔══██╗██╔══██╗██╔══██╗██║████╗  ██║\x1b[38;2;130;68;208m██╔════╝ ██╔════╝████╗  ██║██║╚██╗██╔╝", 5);
    sERSLogger.Log("\x1b[38;2;0;128;55m██████╔╝██████╔╝███████║██║██╔██╗ ██║\x1b[38;2;130;68;208m██║  ███╗█████╗  ██╔██╗ ██║██║ ╚███╔╝ ", 5);
    sERSLogger.Log("\x1b[38;2;0;128;55m██╔══██╗██╔══██╗██╔══██║██║██║╚██╗██║\x1b[38;2;130;68;208m██║   ██║██╔══╝  ██║╚██╗██║██║ ██╔██╗ ", 5);
    sERSLogger.Log("\x1b[38;2;0;128;55m██████╔╝██║  ██║██║  ██║██║██║ ╚████║\x1b[38;2;130;68;208m╚██████╔╝███████╗██║ ╚████║██║██╔╝ ██╗", 5);
    sERSLogger.Log("\x1b[38;2;0;128;55m╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝\x1b[38;2;130;68;208m ╚═════╝ ╚══════╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝", 5);
    sERSLogger.Log("---------------------------------------------------------------------------", 5);
    sERSLogger.Log("", 5);
    sERSLogger.Log("    +-----------------------------------------------------------------+", 4);
    sERSLogger.Log("    |     BrainGenix-ERS Real-Time Environment Rendering System       |", 4);
    sERSLogger.Log(std::string(std::string("    |     Version:") + std::to_string(PROJECT_VERSION) + std::string("                                              |")).c_str(), 4);
    sERSLogger.Log("    |     Branch: {Branch}                                                 |", 4);
    sERSLogger.Log("    |     Clustersize: {NodeCount}                                              |", 4);
    sERSLogger.Log("    +-----------------------------------------------------------------+", 4);
    sERSLogger.Log("", 4);


    // Enter Main Loop
    bool SystemShouldRun = true;
    while (SystemShouldRun) {

        SystemShouldRun = sERSRenderer.UpdateLoop();

    }

    // Cleanup
    sERSRenderer.CleanUp();

}