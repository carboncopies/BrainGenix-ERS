//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing the visual local display system.
    Additonal Notes: None
    Date Created: 2021-10-13
*/ 

#include <GLFW/glfw3.h>
#include <string>

#include "Core/Renderer/Visual/LocalWindowDisplaySystem.h"



// Define LocalWindowDisplaySystem::InitWindow
void LocalWindowDisplaySystem::InitWindow(LoggerClass sERSLogger, YAML::Node sERSConfig) {

    // Create Local References
    Logger = sERSLogger;
    SystemConfiguration = sERSConfig;

    // Log Initialization
    Logger.Log("Initializing GLFW", 2);

    // Initialize GLFW
    glfwInit();

    // Read Window Configuration Parameters
    Logger.Log("Reading System Configuration For 'INT': 'WindowWidth'", 2);
    WindowX = SystemConfiguration["WindowWidth"].as<int>();
    Logger.Log("Reading System Configuration For 'INT': 'WindowHeight'", 2);
    WindowY = SystemConfiguration["WindowHeight"].as<int>();
    Logger.Log("Reading System Configuration For 'STD::STRING': 'WindowTitle'", 2);
    WindowTitle = SystemConfiguration["WindowTitle"].as<std::string>();
    
    
    

}
