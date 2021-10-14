//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing the visual local display system.
    Additonal Notes: None
    Date Created: 2021-10-13
*/ 

#include "Core/Renderer/Visual/LocalWindowDisplaySystem.h"

#include <GLFW/glfw3.h>

// Define LocalWindowDisplaySystem::InitWindow
void LocalWindowDisplaySystem::InitWindow(LoggerClass sERSLogger, YAML::Node sERSConfig) {

    // Create Local References
    Logger = sERSLogger;
    SystemConfiguration = sERSConfig;

    // Log Initialization
    Logger.Log("Initializing GLFW", 2);

    // Initialize GLFW
    glfwInit();



}
