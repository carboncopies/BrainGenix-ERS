 //======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for initializing graphics systems.
    Additonal Notes: None
    Date Created: 2021-05-31
*/ 

#include <string>

#include "Core/IO/WindowManager.cpp"


class GraphicsSubsystem {

    private:
    
    // Declare Vars
    YAML::Node SystemConfiguration;
    LoggerClass Logger;

    public:

        // Main Initialization Function
        void InitializeGraphics(YAML::Node SystemConfigurationDict, LoggerClass LoggerInstance) {

            // Create Pointers To SystemConfig and Logger
            SystemConfiguration = SystemConfigurationDict;
            Logger = LoggerInstance;

            // Log Graphics Init
            Logger.Log("Initializng Graphics Subsystem", 3);

            // Initialize Local Window
            Logger.Log("Running Local Window Init", 3)
            Logger.Log("Checking Config File For: 'WindowEnabled' Parameter", 2);

            const bool LocalWindowEnabled = SystemConfiguration["WindowEnabled"].as<bool>();

            Logger.Log(std::string("Found 'WindowEnabled' Parameter To Be: " + std::string(LocalWindowEnabled)).c_str(), 1);


        }

};