//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing the main renderer system.
    Additonal Notes: None
    Date Created: 2021-10-13
*/ 


#include "Core/Renderer/Visual/LocalWindowDisplaySystem.cpp"

#include "Core/Renderer/Visual/VisualRenderer.h"

#include <vulkan/vulkan.h>


// Define Visual Renderer Class
void VisualRenderer::InitializeSystem(LoggerClass sERSLogger, YAML::Node sERSConfig) {

    // Create Local References
    Logger = sERSLogger;
    SystemConfiguration = sERSConfig;

    // Initialize GLFW
    Logger.Log("Reading System Configuration For 'BOOL': 'WindowEnabled'", 2);
    LocalWindowEnabled = SystemConfiguration["WindowEnabled"].as<bool>();
    if (LocalWindowEnabled) {
        Logger.Log("Initializing 'Core::Renderer::Visual::LocalWindowDisplaySystem'", 4);
        sERSLocalWindowDisplaySystem.InitWindow(Logger, SystemConfiguration);
        Logger.Log("Initialized 'Core::Renderer::Visual::LocalWindowDisplaySystem'", 3);
    } else {
        Logger.Log("Initialization Skip 'Core::Renderer::Visual::LocalWindowDisplaySystem' Due To Config Param", 3);
    };

    // Initialize Vulkan
    Logger.Log("Initializing 'Core::Renderer::Visual::VisualRenderer::Vulkan'", 4);
    //InitVulkan();
    Logger.Log("Initialized 'Core::Renderer::Visual::VisualRenderer::Vulkan'", 3);



}
