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
#include <Tracy.hpp>

#include <yaml-cpp/yaml.h>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <RendererManager.h>
#include <ERS_CLASS_LoggingSystem.h>
#include <HardwareInformation.h>

#include <ERS_SceneManager.h>


#include <ERS_InputOutputSubsystem.h>
#include <ERS_ModelWriter.h>
#include <ERS_FramerateManager.h>
#include <ERS_ProjectLoader.h>
#include <ERS_ProjectManager.h>
#include <ERS_ProjectWriter.h>
#include <ERS_ControllerInputManager.h>

#include <ERS_STRUCT_HumanInputDeviceUtils.h>
#include <ERS_STRUCT_SystemUtils.h>
#include <ERS_STRUCT_ProjectUtils.h>




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


int main() {

    // Initialize System Vars
    std::shared_ptr<bool> SystemShouldRun = std::make_shared<bool>(true);
    std::unique_ptr<ERS_STRUCT_SystemUtils> SystemUtils = std::make_unique<ERS_STRUCT_SystemUtils>();
    SystemUtils->SystemShouldRun_ = SystemShouldRun;

    // Load Local System Configuration File
    YAML::Node sERSLocalSystemConfiguration = YAML::LoadFile("Config.yaml");
    SystemUtils->LocalSystemConfiguration_ = std::make_shared<YAML::Node>(sERSLocalSystemConfiguration);

    // Instantiate Logging Subsystem
    SystemUtils->Logger_ = std::make_unique<ERS_CLASS_LoggingSystem>(sERSLocalSystemConfiguration);
    SystemUtils->Logger_->Log("Initialized Logging System", 5);

    // Setup Framerate Manager
    SystemUtils->Logger_->Log("Initializing Framerate Manager Subsystem", 5);
    std::shared_ptr<ERS_CLASS_FramerateManager> sERSFrameRateManager = std::make_shared<ERS_CLASS_FramerateManager>();
    SystemUtils->FramerateManager_ = sERSFrameRateManager;
    SystemUtils->Logger_->Log("Initialized Framerate Manager", 4);

    // Copy Config Params
    try {
        SystemUtils->Logger_->Log("Reading Configuration File For 'IsLinux'", 2);
        SystemUtils->IsLinux_ = sERSLocalSystemConfiguration["IsLinux"].as<bool>();
    } catch(YAML::BadSubscript) {
        SystemUtils->Logger_->Log("Error Reading Configuration File For 'IsLinux' Boolean Value, Defaulting To False", 9);
    }

    // Startup IO Subsystem And Other Related Systems
    std::shared_ptr<ERS_CLASS_InputOutputSubsystem> sERSIOSubSystem = std::make_shared<ERS_CLASS_InputOutputSubsystem>(SystemUtils->Logger_.get(), sERSLocalSystemConfiguration);
    SystemUtils->ERS_IOSubsystem_ = sERSIOSubSystem;
    std::shared_ptr<ERS_CLASS_ModelWriter> sERSModelWriter = std::make_shared<ERS_CLASS_ModelWriter>(SystemUtils->Logger_.get(), sERSIOSubSystem);
    SystemUtils->ERS_ModelWriter_ = sERSModelWriter;


    // Instantiate HardwareInformation System
    HardwareInformation sERSHardwareInformation(SystemUtils->Logger_.get(), sERSLocalSystemConfiguration);


    // Create ProjectUtils Struct
    SystemUtils->Logger_->Log("Setting Up Project Utilities Structure", 3);
    std::shared_ptr<ERS_STRUCT_ProjectUtils> ProjectUtils = std::make_shared<ERS_STRUCT_ProjectUtils>();

    // Setup Loaders
    SystemUtils->Logger_->Log("Instantiating Scene Manager Shared Pointer", 4);
    std::shared_ptr<ERS_CLASS_SceneManager> sERSSceneManager = std::make_shared<ERS_CLASS_SceneManager>(SystemUtils->Logger_);
    SystemUtils->Logger_->Log("Copying Shared Pointer To Project Utils Struct", 3);
    ProjectUtils->SceneManager_ = sERSSceneManager;

    SystemUtils->Logger_->Log("Instantiating Model Loader Shared Pointer", 4);
    std::shared_ptr<ERS_CLASS_ModelLoader> sERSModelLoader = std::make_shared<ERS_CLASS_ModelLoader>(SystemUtils.get());
    SystemUtils->Logger_->Log("Copying Shared Pointer To Project Utils Struct", 3);
    ProjectUtils->ModelLoader_ = sERSModelLoader;

    SystemUtils->Logger_->Log("Instantiating Scene Loader Shared Pointer", 4);
    std::shared_ptr<ERS_CLASS_SceneLoader> sERSSceneLoader = std::make_shared<ERS_CLASS_SceneLoader>(SystemUtils.get(), sERSModelLoader);
    SystemUtils->Logger_->Log("Copying Shared Pointer To Project Utils Struct", 3);
    ProjectUtils->SceneLoader_ = sERSSceneLoader;

    SystemUtils->Logger_->Log("Instantiating ERS Project Loader Pointer", 4);
    std::shared_ptr<ERS_CLASS_ProjectLoader> sERSProjectLoader = std::make_shared<ERS_CLASS_ProjectLoader>(SystemUtils.get());
    SystemUtils->Logger_->Log("Instantiating Project Loader Shared Pointer", 4);
    ProjectUtils->ProjectLoader_ = sERSProjectLoader;

    SystemUtils->Logger_->Log("Instantiating ERS Project Writer Pointer", 4);
    std::shared_ptr<ERS_CLASS_ProjectWriter> sERSProjectWriter = std::make_shared<ERS_CLASS_ProjectWriter>(SystemUtils.get());
    SystemUtils->Logger_->Log("Instantiating Project Writer Shared Pointer", 4);
    ProjectUtils->ProjectWriter_ = sERSProjectWriter;

    SystemUtils->Logger_->Log("Instantiating ERS Project Manager Pointer", 4);
    std::shared_ptr<ERS_CLASS_ProjectManager> sERSProjectManager = std::make_shared<ERS_CLASS_ProjectManager>(SystemUtils.get(), sERSProjectLoader, sERSProjectWriter, sERSSceneManager, sERSSceneLoader);
    SystemUtils->Logger_->Log("Copying Shared Pointer To Project Utils Struct", 3);
    ProjectUtils->ProjectManager_ = sERSProjectManager;


    // Setup Human Input Devices
    SystemUtils->Logger_->Log("Setting Up Human Input Device Managers", 5);

    // Create Struct
    std::shared_ptr<ERS_STRUCT_HumanInputDeviceUtils> HIDUtils = std::make_shared<ERS_STRUCT_HumanInputDeviceUtils>();

    // Setup Controller Manager
    SystemUtils->Logger_->Log("Instantiating ERS Controller Input Manager", 5);
    std::shared_ptr<ERS_CLASS_ControllerInputManager> sERSControllerManager = std::make_shared<ERS_CLASS_ControllerInputManager>(SystemUtils.get());
    SystemUtils->Logger_->Log("Copying Shared Pointer To HumanInputDeviceUtils Struct", 4);
    HIDUtils->ControllerInputManager = sERSControllerManager;

    // VR Driver here?

    // More????

    SystemUtils->Logger_->Log("Finished Setting Up Human Input Device Managers", 5);    


    // Instantiate RendererManager
    RendererManager sERSRendererManager(SystemUtils.get(), ProjectUtils, HIDUtils);


    
    // Log Logo Text
    SystemUtils->Logger_->Log("Starting BrainGenix-ERS Instance", 2);
    SystemUtils->Logger_->Log("", 5);
    SystemUtils->Logger_->Log("---------------------------------------------------------------------------", 5);
    SystemUtils->Logger_->Log("\x1b[38;2;0;128;55m██████╗ ██████╗  █████╗ ██╗███╗   ██╗\x1b[38;2;130;68;208m ██████╗ ███████╗███╗   ██╗██╗██╗  ██╗", 5);
    SystemUtils->Logger_->Log("\x1b[38;2;0;128;55m██╔══██╗██╔══██╗██╔══██╗██║████╗  ██║\x1b[38;2;130;68;208m██╔════╝ ██╔════╝████╗  ██║██║╚██╗██╔╝", 5);
    SystemUtils->Logger_->Log("\x1b[38;2;0;128;55m██████╔╝██████╔╝███████║██║██╔██╗ ██║\x1b[38;2;130;68;208m██║  ███╗█████╗  ██╔██╗ ██║██║ ╚███╔╝ ", 5);
    SystemUtils->Logger_->Log("\x1b[38;2;0;128;55m██╔══██╗██╔══██╗██╔══██║██║██║╚██╗██║\x1b[38;2;130;68;208m██║   ██║██╔══╝  ██║╚██╗██║██║ ██╔██╗ ", 5);
    SystemUtils->Logger_->Log("\x1b[38;2;0;128;55m██████╔╝██║  ██║██║  ██║██║██║ ╚████║\x1b[38;2;130;68;208m╚██████╔╝███████╗██║ ╚████║██║██╔╝ ██╗", 5);
    SystemUtils->Logger_->Log("\x1b[38;2;0;128;55m╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝\x1b[38;2;130;68;208m ╚═════╝ ╚══════╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝", 5);
    SystemUtils->Logger_->Log("---------------------------------------------------------------------------", 5);
    SystemUtils->Logger_->Log("", 5);
    SystemUtils->Logger_->Log("    +-----------------------------------------------------------------+", 4);
    SystemUtils->Logger_->Log("    |     BrainGenix-ERS Real-Time Environment Rendering System       |", 4);
    SystemUtils->Logger_->Log("    +-----------------------------------------------------------------+", 4);
    SystemUtils->Logger_->Log("", 4);


    // Initialize Times
    float DeltaTime = 0.0f;
    float LastFrame = 0.0f;

    // Enter Main Loop
    while (*SystemShouldRun) {

        // Calculate Frametime
        float CurrentTime = glfwGetTime();
        DeltaTime = CurrentTime - LastFrame;
        LastFrame = CurrentTime;

        // Calculate Last FrameTime
        sERSFrameRateManager->StartNewFrame();


        // Update Joysticks
        sERSControllerManager->UpdateControllers();


        // Update Renderers
        sERSRendererManager.UpdateLoop(DeltaTime);



        // End Frame
        sERSFrameRateManager->DelayUntilNextFrame();

    }


    // Test Clear Project
    sERSSceneManager->Scenes_.erase(sERSSceneManager->Scenes_.begin(), sERSSceneManager->Scenes_.end());


    // Program Exit (Destructors Automatically Called)
    return 0;

}