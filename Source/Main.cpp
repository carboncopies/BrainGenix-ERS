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
#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <LuciferIL/Lucifer_IncludeOnce.h>
#include <LuciferIL/Lucifer.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <GPURequest.h>
#include <RendererManager.h>

#include <BG/Common/Logger/Logger.h>
#include <BG/Common/Logger/LogSystemInfo.h>
#include <HardwareInformation.h>
#include <ArgumentParser.h>
#include <ModelImporter.h>
#include <LocalConfigLoader.h>


#include <SceneManager.h>

#include <InputOutputSubsystem.h>
#include <FramerateManager.h>
#include <ProjectLoader.h>
#include <ProjectManager.h>
#include <ProjectWriter.h>
#include <ControllerInputManager.h>

#include <HumanInputDeviceUtils.h>
#include <SystemUtils.h>
#include <ProjectUtils.h>
#include <RendererSettings.h>

//#include <PythonInterpreterIntegration.h>
#include <ERS_CLASS_LuaJITInterpreterIntegration.h>


#include <GetExecutablePath.h>


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


int main(int NumArguments, char** ArguemntValues) {


    // Initialize System Vars
    std::unique_ptr<ERS_STRUCT_SystemUtils> SystemUtils = std::make_unique<ERS_STRUCT_SystemUtils>();
    SystemUtils->SystemShouldRun_ = std::make_unique<bool>(true);

    // Load Local System Configuration File
    YAML::Node Config;
    bool Status = BrainGenix::ERS::Module::LoadLocalConfiguration("Config.yaml", Config);
    SystemUtils->LocalSystemConfiguration_ = std::make_unique<YAML::Node>(Config);
    if (!Status) {
        return 65535;
    }

    // Instantiate Logging Subsystem
    SystemUtils->Logger_ = std::make_unique<BG::Common::Logger::LoggingSystem>(*SystemUtils->LocalSystemConfiguration_.get());
    SystemUtils->Logger_->Log("Initialized Logging System", 5);

    // Handle Command Line Arguments
    BrainGenix::ERS::Module::ArgumentParser ArgumentParser = BrainGenix::ERS::Module::ArgumentParser(SystemUtils->Logger_.get());
    ArgumentParser.ParseArguments(NumArguments, ArguemntValues);
    SystemUtils->ArgumentString_ = ArgumentParser.GetArgumentString();
    SystemUtils->Arguments_ = ArgumentParser.GetArgumentPairs();
    

    // Setup Framerate Manager
    SystemUtils->Logger_->Log("Initializing Framerate Manager Subsystem", 5);
    SystemUtils->FramerateManager_ = std::make_unique<ERS_CLASS_FramerateManager>();
    SystemUtils->Logger_->Log("Initialized Framerate Manager", 4);


    // Startup IO Subsystem And Other Related Systems
    SystemUtils->ERS_IOSubsystem_ = std::make_unique<ERS_InputOutputSubsystem>(
        SystemUtils->Logger_.get(),
        *SystemUtils->LocalSystemConfiguration_.get(),
        SystemUtils->Arguments_
    );
    SystemUtils->ERS_HardwareInformation_ = std::make_unique<ERS_HardwareInformation>(
        SystemUtils->Logger_.get(),
        *SystemUtils->LocalSystemConfiguration_.get()
    );

   /* SystemUtils->ERS_CLASS_PythonInterpreterIntegration_ = std::make_unique<ERS_CLASS_PythonInterpreterIntegration>(
        SystemUtils->Logger_.get()
    );*/
    SystemUtils->ERS_CLASS_LuaJITInterpreterIntegration_ = std::make_unique<ERS_CLASS_LuaJITInterpreterIntegration>(
        SystemUtils->Logger_.get()
    );
    //Testing LuaScript
    ERS_CLASS_LuaJITInterpreterIntegration lua_interpreter( SystemUtils->Logger_.get());
    lua_interpreter.Test_Script();

    SystemUtils->RendererSettings_ = std::make_unique<ERS_STRUCT_RendererSettings>();


    // Create ProjectUtils Struct
    SystemUtils->Logger_->Log("Setting Up Project Utilities Structure", 3);
    std::unique_ptr<ERS_STRUCT_ProjectUtils> ProjectUtils = std::make_unique<ERS_STRUCT_ProjectUtils>();

    // Setup Loaders
    SystemUtils->Logger_->Log("Instantiating Scene Manager Shared Pointer", 4);
    ProjectUtils->SceneManager_ = std::make_unique<ERS_CLASS_SceneManager>(SystemUtils->Logger_.get());

    SystemUtils->Logger_->Log("Instantiating Model Loader Shared Pointer", 4);
    ProjectUtils->ModelLoader_ = std::make_unique<ERS_CLASS_ModelLoader>(SystemUtils.get());

    SystemUtils->Logger_->Log("Instantiating Scene Loader Shared Pointer", 4);
    ProjectUtils->SceneLoader_ = std::make_unique<ERS_CLASS_SceneLoader>(SystemUtils.get(), ProjectUtils->ModelLoader_.get());

    SystemUtils->Logger_->Log("Instantiating ERS Project Loader Pointer", 4);
    ProjectUtils->ProjectLoader_ = std::make_unique<ERS_CLASS_ProjectLoader>(SystemUtils.get());

    SystemUtils->Logger_->Log("Instantiating ERS Project Writer Pointer", 4);
    ProjectUtils->ProjectWriter_ = std::make_unique<ERS_CLASS_ProjectWriter>(SystemUtils.get());

    SystemUtils->Logger_->Log("Instantiating ERS Project Manager Pointer", 4);
    ProjectUtils->ProjectManager_ = std::make_unique<ERS_CLASS_ProjectManager>(SystemUtils.get(), ProjectUtils->ProjectLoader_.get(), ProjectUtils->ProjectWriter_.get(), ProjectUtils->SceneManager_.get(), ProjectUtils->SceneLoader_.get());

    SystemUtils->Logger_->Log("Instantiating ERS Model Importer", 4);
    ProjectUtils->ModelImporter_ = std::make_unique<ERS_ModelImporter>(SystemUtils.get());


    // Setup Human Input Devices
    SystemUtils->Logger_->Log("Setting Up Human Input Device Managers", 5);

    // Create Struct
    std::unique_ptr<ERS_STRUCT_HumanInputDeviceUtils> HIDUtils = std::make_unique<ERS_STRUCT_HumanInputDeviceUtils>();

    // Setup Controller Manager
    SystemUtils->Logger_->Log("Instantiating ERS Controller Input Manager", 5);
    HIDUtils->ControllerInputManager = std::make_unique<ERS_CLASS_ControllerInputManager>(SystemUtils.get());
    SystemUtils->Logger_->Log("Finished Setting Up Human Input Device Managers", 5);    


    // Instantiate RendererManager
    RendererManager sERSRendererManager(SystemUtils.get(), ProjectUtils.get(), HIDUtils.get());


    BG::Common::Logger::LogSystemInfo(SystemUtils->Logger_.get());


    // Initialize Times
    float DeltaTime = 0.0f;
    float LastFrame = 0.0f;

    // Enter Main Loop
    while (*SystemUtils->SystemShouldRun_) {

        // Calculate Frametime
        float CurrentTime = glfwGetTime();
        DeltaTime = CurrentTime - LastFrame;
        LastFrame = CurrentTime;

        // Calculate Last FrameTime
        SystemUtils->FramerateManager_->StartNewFrame();



        // Update Joysticks
        HIDUtils->ControllerInputManager->UpdateControllers();


        // Update Renderers
        sERSRendererManager.UpdateLoop(DeltaTime);



        // End Frame
        SystemUtils->FramerateManager_->DelayUntilNextFrame();

    }


    // Test Clear Project
    ProjectUtils->SceneManager_->Scenes_.erase(ProjectUtils->SceneManager_->Scenes_.begin(), ProjectUtils->SceneManager_->Scenes_.end());


    // Program Exit (Destructors Automatically Called)
    return 0;

}
