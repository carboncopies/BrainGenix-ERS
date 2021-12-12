//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the main file of the system.
    Additional Notes: None
    Date Created: 2021-11-01
*/


// Standard Libraries (BG convention: use <> instead of "")

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <LocalConfigurationLoader.h>
#include <LoggingSystem.h>

#include <RendererManager.h>
#include <HardwareInformation.h>




//
//
//
//-----------------------------------------------------------------------------------------------------
//
// FIXME: Add proper lighting system (phong and more advanced (and shadow maps))
// FIXME: implement animations (character deformations)
// FIXME: implement offscreen rendering
// FIXME: add other features to this list later, (audio rendering, ray tracing, etc.)
// FIXME: Update this card with more info as needed!
//
//-----------------------------------------------------------------------------------------------------
//
//
//
//
//


/**
 * @brief Entry point.
 * 
 * @return int 
 */
int main() {

    // Initialize System State Bool
    bool SystemShouldRun = true; /**<Indicates If System Should Run, False Will Cause System To Exit On Next RunLoop Iteration>*/

    // Load Local System Configuration File
    YAML::Node sERSLocalSystemConfiguration = LoadConfig("Config.yaml");

    // Instantiate Logging Subsystem
    std::shared_ptr<LoggerClass> sERSLogger = std::make_shared<LoggerClass>(sERSLocalSystemConfiguration);
    sERSLogger->Log("Initialized Logging System", 5);

    // Instantiate HardwareInformation System
    HardwareInformation sERSHardwareInformation(sERSLogger, sERSLocalSystemConfiguration);

    // Instantiate RendererManager
    RendererManager sERSRendererManager(&sERSLocalSystemConfiguration, &sERSLogger, &SystemShouldRun);



    
    // Log Logo Text
    sERSLogger->Log("Starting BrainGenix-ERS Instance", 2);
    sERSLogger->Log("", 5);
    sERSLogger->Log("---------------------------------------------------------------------------", 5);
    sERSLogger->Log("\x1b[38;2;0;128;55m██████╗ ██████╗  █████╗ ██╗███╗   ██╗\x1b[38;2;130;68;208m ██████╗ ███████╗███╗   ██╗██╗██╗  ██╗", 5);
    sERSLogger->Log("\x1b[38;2;0;128;55m██╔══██╗██╔══██╗██╔══██╗██║████╗  ██║\x1b[38;2;130;68;208m██╔════╝ ██╔════╝████╗  ██║██║╚██╗██╔╝", 5);
    sERSLogger->Log("\x1b[38;2;0;128;55m██████╔╝██████╔╝███████║██║██╔██╗ ██║\x1b[38;2;130;68;208m██║  ███╗█████╗  ██╔██╗ ██║██║ ╚███╔╝ ", 5);
    sERSLogger->Log("\x1b[38;2;0;128;55m██╔══██╗██╔══██╗██╔══██║██║██║╚██╗██║\x1b[38;2;130;68;208m██║   ██║██╔══╝  ██║╚██╗██║██║ ██╔██╗ ", 5);
    sERSLogger->Log("\x1b[38;2;0;128;55m██████╔╝██║  ██║██║  ██║██║██║ ╚████║\x1b[38;2;130;68;208m╚██████╔╝███████╗██║ ╚████║██║██╔╝ ██╗", 5);
    sERSLogger->Log("\x1b[38;2;0;128;55m╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝\x1b[38;2;130;68;208m ╚═════╝ ╚══════╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝", 5);
    sERSLogger->Log("---------------------------------------------------------------------------", 5);
    sERSLogger->Log("", 5);
    sERSLogger->Log("    +-----------------------------------------------------------------+", 4);
    sERSLogger->Log("    |     BrainGenix-ERS Real-Time Environment Rendering System       |", 4);
    sERSLogger->Log("    +-----------------------------------------------------------------+", 4);
    sERSLogger->Log("", 4);


    // Initialize Times
    float DeltaTime = 0.0f;
    float LastFrame = 0.0f;

    // Enter Main Loop
    while (SystemShouldRun) {

        // Calculate Frametime
        float CurrentTime = glfwGetTime();
        DeltaTime = CurrentTime - LastFrame;
        LastFrame = CurrentTime;

        // Update Renderers
        sERSRendererManager.UpdateLoop(DeltaTime);

    }

    // Program Exit (Destructors Automatically Called)
    return 0;

}