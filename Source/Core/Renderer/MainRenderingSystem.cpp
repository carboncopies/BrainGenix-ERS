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
void MainRenderer::InitRenderer(LoggerClass sERSLogger, YAML::Node sERSConfig, bool ShutdownToggle) {

    // Create Local References
    Logger_ = sERSLogger;
    SystemConfiguration_ = sERSConfig;
    SystemShutdownInvoked_ = ShutdownToggle;



    // Initialize Graphics Subsystem
    Logger_.Log("Initializing 'Core::Renderer::MainRenderingSystem'", 5);
    sERSVisualRenderer_.InitializeSystem(sERSLogger, SystemConfiguration_, SystemShutdownInvoked_);
    Logger_.Log("Initialized 'Renderer::Visual::VisualRenderer'", 5);


}

// Define MainRenderer::UpdateRender
void MainRenderer::UpdateRender() {

    // Update Visual Rendering System
    sERSVisualRenderer_.RenderLoop();

}


// Define MainRenderer::CleanUp
void MainRenderer::CleanUp() {
    
    // Log Shutdown Called
    Logger_.Log("Shutting Down 'Core::Renderer::MainRenderingSystem'", 5);

    // Shut Down Visual Renderer
    sERSVisualRenderer_.CleanUp();

}