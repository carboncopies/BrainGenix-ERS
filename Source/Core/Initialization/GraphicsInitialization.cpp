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
    GLFWwindow* Window;

    public:

        // Main Initialization Function
        void InitializeGraphics(YAML::Node SystemConfigurationDict, LoggerClass LoggerInstance) {

            // Create Pointers To SystemConfig and Logger
            SystemConfiguration = SystemConfigurationDict;
            Logger = LoggerInstance;

            // Log Graphics Init
            Logger.Log("Initializng Graphics Subsystem", 3);

            // Initialize Local Window
            Logger.Log("Running Local Window Init", 3);
            Logger.Log("Checking Config File For: 'WindowEnabled' Parameter", 2);

            const bool LocalWindowEnabled = SystemConfiguration["WindowEnabled"].as<bool>();

            if (LocalWindowEnabled == true) {

                // Log Window Creation
                Logger.Log("Local Window Enabled, Creating GLFW Window", 3);

                // Get Desired Window Resolution
                Logger.Log("Reading GLFW Window Resolution Parameters", 2);

                int WindowWidth;
                int WindowHeight;

                Logger.Log("Checking Config File For: 'WindowWidth' Parameter", 2);
                WindowWidth = SystemConfiguration["WindowWidth"].as<int>();
                Logger.Log(std::string("Read Value As: '" + std::string(WindowWidth) + "'").c_str(), 1);

                Logger.Log("Checking Config File For 'WindowHeight' Parameter", 2);
                WindowHeight = SystemConfiguration["WindowHeight"].as<int>();
                Logger.Log(std::string("Read Value As: '" + std::string(WindowHeight) + "'").c_str(), 1);

                // create window
                glfwInit();
                //Window = glfwCreateWindow()

            }

        }

};