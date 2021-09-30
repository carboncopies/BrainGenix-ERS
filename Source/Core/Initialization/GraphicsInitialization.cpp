 //======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for initializing graphics systems.
    Additonal Notes: None
    Date Created: 2021-05-31
*/ 

#include <string>

#include <bgfx/bgfx.h>



#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD 
    #define GLFW_EXPOSE_NATIVE_X11
#else
    #define GLFW_EXPOSE_NATIVE_WIN32
#endif

#include <GLFW/glfw3.h>


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

            // Initialize BGFX
            Logger.Log("Initializing BGFX Rendering Library", 4);
            bgfx::init();


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
                Logger.Log("Creating GLFW Window Surface", 3);
                Window = glfwCreateWindow(WindowWidth, WindowHeight, WindowTitle, NULL, NULL);


                // Connect BGFX To Display Surface - NOTE: THIS IS A WIP, MUST BE ABLE TO RENDER TO NETWORK DISPLAY SURFACE
                // Get BGFX Platform Data
                Logger.Log("Collecting BGFX Platform Data", 3);
                bgfx::PlatformData PlatformDataInstance;


                // Magic Platform Instance Stuff
                #if BX_PLATFORM_LINUX || BX_PLATFORM_BSD 
                
                    // Add Nice Linux Message :)
                    Logger.Log("Detected Linux/BSD Platform - Far Better Than Windows/OSX", 3);

                    #if ENTRY_CONFIG_USE_WAYLAND
                        PlatformDataInstance.ndt      = glfwGetWaylandDisplay(); 
                    #else 
                        PlatformDataInstance.ndt      = glfwGetX11Display(); 
                        PlatformDataInstance.nwh      = (void*)glfwGetX11Window(Window);
                    #endif 
                    
                #elif BX_PLATFORM_OSX
                
                        // Add Snarky OSX Message
                        Logger.Log("Detected OSX - Yuck, You Should Use Linux/BSD", 3);

                        PlatformDataInstance.ndt      = NULL; 
                
                #elif BX_PLATFORM_WINDOWS 
                
                        // Add Snarky Windows Message
                        Logger.Log("Detected Windows - Not As Bad As OSX, Still Though, You Should Use Linux/BSD", 3);

                        PlatformDataInstance.ndt      = NULL; 
                        PlatformDataInstance.nwh      = glfwGetWin32Window(Window);
                
                #endif

                // Log Setting Platform Data
                Logger.Log("Setting Platform Data", 2);
                //bgfx::setPlatformData(PlatformDataInstance);




            } else {

                // Log GLFW Disabled
                Logger.Log("GLFW Local Window Disabled In Config File", 4);

            }

            






        }


};