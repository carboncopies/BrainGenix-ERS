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
//#include <Tracy.hpp>

#include <yaml-cpp/yaml.h>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <LocalConfigurationLoader.h>
#include <LoggingSystem.h>
#include <ERS_InputOutputSubsystem.h>
#include <ERS_ModelWriter.h>

#include <ERS_STRUCT_SystemUtils.h>

#include <RendererManager.h>
#include <HardwareInformation.h>



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


/**
 * @brief Entry point.
 * 
 * @return int 
 */
int main() {

    // Initialize System Vars
    std::shared_ptr<bool> SystemShouldRun = std::make_shared<bool>(true);
    std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils = std::make_shared<ERS_STRUCT_SystemUtils>();
    SystemUtils->SystemShouldRun_ = SystemShouldRun;

    // Load Local System Configuration File
    YAML::Node sERSLocalSystemConfiguration = LoadConfig("Config.yaml");
    SystemUtils->LocalSystemConfiguration_ = std::make_shared<YAML::Node>(sERSLocalSystemConfiguration);

    // Instantiate Logging Subsystem
    std::shared_ptr<LoggerClass> sERSLogger = std::make_shared<LoggerClass>(sERSLocalSystemConfiguration);
    SystemUtils->Logger_ = sERSLogger;
    sERSLogger->Log("Initialized Logging System", 5);

    // Startup IO Subsystem And Other Related Systems
    std::shared_ptr<ERS_CLASS_InputOutputSubsystem> sERSIOSubSystem = std::make_shared<ERS_CLASS_InputOutputSubsystem>(sERSLogger, sERSLocalSystemConfiguration);
    SystemUtils->ERS_IOSubsystem_ = sERSIOSubSystem;
    std::shared_ptr<ERS_CLASS_ModelWriter> sERSModelWriter = std::make_shared<ERS_CLASS_ModelWriter>(sERSLogger, sERSIOSubSystem);
    SystemUtils->ERS_ModelWriter_ = sERSModelWriter;



    // Instantiate HardwareInformation System
    HardwareInformation sERSHardwareInformation(sERSLogger, sERSLocalSystemConfiguration);

    // Instantiate RendererManager
    RendererManager sERSRendererManager(SystemUtils);


    
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
    while (*SystemShouldRun) {

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