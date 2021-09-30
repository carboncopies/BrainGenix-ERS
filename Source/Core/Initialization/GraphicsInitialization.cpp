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
#include <bgfx/platform.h>



#include <GLFW/glfw3.h>
//#if BX_PLATFORM_LINUX || BX_PLATFORM_BSD 
#define GLFW_EXPOSE_NATIVE_X11
#define GLFW_EXPOSE_NATIVE_GLX
//#else
//    #define GLFW_EXPOSE_NATIVE_WIN32
//#endif
#include <GLFW/glfw3native.h>




class GraphicsSubsystem {

    private:
    
        // Declare Vars
        YAML::Node SystemConfiguration;
        LoggerClass Logger;
        GLFWwindow* Window;
    

    public:

        // Declare Config Params
        int RenderWidthPixels;
        int RenderHeightPixels;
        bool LocalWindowEnabled;

        // Main Initialization Function
        void InitializeGraphics(YAML::Node SystemConfigurationDict, LoggerClass LoggerInstance) {

            // Create Pointers To SystemConfig and Logger
            SystemConfiguration = SystemConfigurationDict;
            Logger = LoggerInstance;

            // Log Graphics Init
            Logger.Log("Initializng Graphics Subsystem", 3);

            // Create BGFX Init Object
            Logger.Log("Creating BGFX Init Configuration", 4);
            bgfx::Init BgfxInitConfig;


            // Initialize Local Window
            Logger.Log("Running Local Window Init", 3);
            Logger.Log("Checking Config File For: 'WindowEnabled' Parameter", 2);

            LocalWindowEnabled = SystemConfiguration["WindowEnabled"].as<bool>();

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


                PlatformDataInstance.ndt      = glfwGetX11Display(); 
                PlatformDataInstance.nwh      = (void*)glfwGetX11Window(Window);

                // // Magic Platform Instance Stuff
                // #if BX_PLATFORM_LINUX || BX_PLATFORM_BSD 
                
                //     // Add Nice Linux Message :)
                //     Logger.Log("Detected Linux/BSD Platform - Far Better Than Windows/OSX", 3);

                //     #if ENTRY_CONFIG_USE_WAYLAND
                //         PlatformDataInstance.ndt      = glfwGetWaylandDisplay(); 
                //     #else 
                //         PlatformDataInstance.ndt      = glfwGetX11Display(); 
                //         PlatformDataInstance.nwh      = (void*)glfwGetX11Window(Window);
                //     #endif 
                    
                // #elif BX_PLATFORM_OSX
                
                //         // Add Snarky OSX Message
                //         Logger.Log("Detected OSX - Yuck, You Should Use Linux/BSD", 3);

                //         PlatformDataInstance.ndt      = NULL; 
                
                // #elif BX_PLATFORM_WINDOWS 
                
                //         // Add Snarky Windows Message
                //         Logger.Log("Detected Windows - Not As Bad As OSX, Still Though, You Should Use Linux/BSD", 3);

                //         PlatformDataInstance.ndt      = NULL; 
                //         PlatformDataInstance.nwh      = glfwGetWin32Window(Window);
                
                // #endif

                // Log Setting Platform Data
                Logger.Log("Setting Platform Data", 2);
                BgfxInitConfig.platformData = PlatformDataInstance;

                bgfx::glfwSetWindow(Window);


            } else {

                // Log GLFW Disabled
                Logger.Log("GLFW Local Window Disabled In Config File", 4);

            }

            
            // More Platform Configuration Stuff
            Logger.Log("Setting BGFX Rendering Parameters", 3);

            Logger.Log("Checking Config File For 'UseVulkan' Parameter", 2);
            bool UseVulkanBackend = SystemConfiguration["UseVulkan"].as<bool>();

            if (UseVulkanBackend) {
                // Log Vulkan Backend
                Logger.Log("Setting Rendering Backend To Vulkan", 1);
                BgfxInitConfig.type = bgfx::RendererType::Vulkan;
            } else {
                // Log OpenGL Backend
                Logger.Log("Setting Rendering Backend To OpenGL", 1);
                BgfxInitConfig.type = bgfx::RendererType::OpenGL;
            }

            Logger.Log("Checking Config File For 'RenderWidthPixels' Parameter", 3);
            RenderWidthPixels = SystemConfiguration["RenderWidthPixels"].as<int>();
            BgfxInitConfig.resolution.width = RenderWidthPixels;
            Logger.Log("Checking Config File For 'RenderHeightPixels' Parameter", 3);
            RenderHeightPixels = SystemConfiguration["RenderHeightPixels"].as<int>();            
            BgfxInitConfig.resolution.height = RenderHeightPixels;

            // Initialize BGFX
            Logger.Log("Initializing BGFX", 5);
            bgfx::init(BgfxInitConfig);
            bgfx::renderFrame();

            // Set Window Redraw Paramaters
            bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x443355FF, 1.0f, 0);
            bgfx::setViewRect(0, 0, 0, RenderWidthPixels, RenderHeightPixels);


        }


};