 //======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for initializing graphics systems.
    Additonal Notes: None
    Date Created: 2021-05-31
*/ 

#include "IO/WindowManager.cpp"


class GraphicsSubsystem {

    private:
    
    // Declare Vars
    YAML::Node SystemConfiguration;
    LoggerClass Logger;

    public:

        // Main Initialization Function
        void InitializeGraphics(YAML::Node SystemConfigurationDict, LoggerClass LoggerInstance) {

            // Create Pointers To SystemConfig and Logger
            SystemConfiguration = SYstemConfigurationDict;
            Logger = LoggerInstance;

            // Log Graphics Init

        }

};