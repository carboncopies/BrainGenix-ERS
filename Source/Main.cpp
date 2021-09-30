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
#include "Core/Initialization/GraphicsInitialization.cpp"
#include "Core/Graphics/RenderLoop.cpp"

int main() {

    // Load System Configuration File
    const YAML::Node SystemConfiguration = LoadConfig("Config.yaml");

    // Instantiate Logging Subsystem //
    LoggerClass sERSLogger;
    sERSLogger.InitializeLogger(SystemConfiguration);

    sERSLogger.Log("Initialized Logger Subsystem", 5);

    // Initialize Graphics Subsystem
    GraphicsSubsystem sERSGraphicsSystem;
    sERSGraphicsSystem.InitializeGraphics(SystemConfiguration, sERSLogger);


    // Initialize Render Loop
    RenderLoopClass sERSRenderLoop;
    sERSRenderLoop.InitializeRenderLoop(sERSGraphicsSystem, sERSLogger);


    // Main Program Loop
    sERSLogger.Log("Entering Main Program Loop", 4);
    bool ProgramShouldRun = true;
    while (ProgramShouldRun) {

        // Update The Graphics
        sERSRenderLoop.RenderLoop();

    }

}