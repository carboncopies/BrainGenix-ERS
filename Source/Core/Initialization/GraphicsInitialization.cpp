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

                // Get Desired Window Params
                Logger.Log("Reading GLFW Window Parameters", 2);

                Logger.Log("Checking Config File For: 'WindowWidth' Parameter", 2);
                int WindowWidth = SystemConfiguration["WindowWidth"].as<int>();
                Logger.Log("Checking Config File For: 'WindowHeight' Parameter", 2);
                int WindowHeight = SystemConfiguration["WindowHeight"].as<int>();
                Logger.Log("Checking Config File For: 'WindowTitle' Parameter", 2);
                const char* WindowTitle = SystemConfiguration["WindowTitle"].as<std::string>().c_str();

                // Initialize GLFW
                Logger.Log("Initializing GLFW", 4);
                glfwInit();

                // Create Window
                Logger.Log("Creating GLFW Window Surface", 3)
                Window = glfwCreateWindow(WindowWidth, WindowHeight, WindowTitle, NULL, NULL);

            }

        }

};