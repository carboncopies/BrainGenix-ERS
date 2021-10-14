//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing the main rendering system.
    Additonal Notes: None
    Date Created: 2021-10-13
*/  


#include "Core/Renderer/Visual/VisualRenderer.cpp"

#include "Core/Renderer/MainRenderingSystem.h"



// Define MainRenderer::InitRenderer
MainRenderer::InitRenderer(LoggerClass sERSLogger, YAML::Node sERSConfig) {

    // Create Local References
    Logger = sERSLogger;
    SystemConfiguration = sERSConfig;


    // Initialize Graphics Subsystem
    Logger.Log("Initializing 'Core::Renderer::MainRenderingSystem'", 5);
    sERSVisualRenderer.InitializeSystem(sERSLogger, SystemConfiguration);
    Logger.Log("Initialized 'Renderer::Visual::VisualRenderer'", 5);


}