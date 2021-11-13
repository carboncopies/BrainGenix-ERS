//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the main file of the system.
    Additonal Notes: None
    Date Created: 2021-11-01
*/

#include "Core/Loader/Configuration/ConfigurationLoader.h"
#include "Core/Management/LoggingSystem.h"
#include "Core/Renderer/Renderer.h"
#include "Core/System.cpp"
#include "Core/Loader/BGAsset/BGAssetLoader.cpp"

#include "Core/Version.h"


int main() {

    // Initialize System State Bool
    bool SystemShouldRun = true;

    // Load System Configuration File
    YAML::Node SystemConfiguration = LoadConfig("Config.yaml");

    // Instantiate Logging Subsystem //
    LoggerClass sERSLogger;
    sERSLogger.InitializeLogger(SystemConfiguration);

    sERSLogger.Log("Initialized 'Management::Logger::LoggerClass'", 5);

    // Initialize Asset Loader System
    AssetLoader sERSAssetLoader(&sERSLogger, &SystemConfiguration);

    // Initialize System
    sERSSubSystem sERSMainSubSystem(&sERSLogger, &SystemConfiguration, &SystemShouldRun, &sERSAssetLoader);

    // Initialize Renderers
    sERSMainSubSystem.InitializeRenderers();

    // Load In Model (TESTING - REMOVE THIS LATER AND MAKE A PROPER SOLUTION!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
    ERS_OBJECT_SCENE TestScene = LoadScene(0, &sERSLogger, true);
    sERSAssetLoader.LoadSceneAssets(TestScene);



    // Log Logo Text
    sERSLogger.Log("Starting BrainGenix-ERS Instance", 2);
    sERSLogger.Log("", 5);
    sERSLogger.Log("---------------------------------------------------------------------------", 5);
    sERSLogger.Log("\x1b[38;2;0;128;55m██████╗ ██████╗  █████╗ ██╗███╗   ██╗\x1b[38;2;130;68;208m ██████╗ ███████╗███╗   ██╗██╗██╗  ██╗", 5);
    sERSLogger.Log("\x1b[38;2;0;128;55m██╔══██╗██╔══██╗██╔══██╗██║████╗  ██║\x1b[38;2;130;68;208m██╔════╝ ██╔════╝████╗  ██║██║╚██╗██╔╝", 5);
    sERSLogger.Log("\x1b[38;2;0;128;55m██████╔╝██████╔╝███████║██║██╔██╗ ██║\x1b[38;2;130;68;208m██║  ███╗█████╗  ██╔██╗ ██║██║ ╚███╔╝ ", 5);
    sERSLogger.Log("\x1b[38;2;0;128;55m██╔══██╗██╔══██╗██╔══██║██║██║╚██╗██║\x1b[38;2;130;68;208m██║   ██║██╔══╝  ██║╚██╗██║██║ ██╔██╗ ", 5);
    sERSLogger.Log("\x1b[38;2;0;128;55m██████╔╝██║  ██║██║  ██║██║██║ ╚████║\x1b[38;2;130;68;208m╚██████╔╝███████╗██║ ╚████║██║██╔╝ ██╗", 5);
    sERSLogger.Log("\x1b[38;2;0;128;55m╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚═╝  ╚═══╝\x1b[38;2;130;68;208m ╚═════╝ ╚══════╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝", 5);
    sERSLogger.Log("---------------------------------------------------------------------------", 5);
    sERSLogger.Log("", 5);
    sERSLogger.Log("    +-----------------------------------------------------------------+", 4);
    sERSLogger.Log("    |     BrainGenix-ERS Real-Time Environment Rendering System       |", 4);
    sERSLogger.Log(std::string(std::string("    |     Version: ") + std::string(PROJECT_VERSION) + std::string("                                              |")).c_str(), 4);
    sERSLogger.Log(std::string(std::string("    |     Branch: ") + std::string(PROJECT_BRANCH) + std::string("                                                 |")).c_str(), 4);
    //ERSLogger.Log("    |     Clustersize: {NodeCount}                                              |", 4);
    sERSLogger.Log("    +-----------------------------------------------------------------+", 4);
    sERSLogger.Log("", 4);


    // Enter Main Loop
    while (SystemShouldRun) {

        sERSMainSubSystem.UpdateRenderers();

    }

    // Program Exit (Destructors Automatically Called)
    return 0;

}