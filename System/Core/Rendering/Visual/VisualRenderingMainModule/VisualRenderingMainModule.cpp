//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing the main pipeline for the 3D visual rendering system.
    Additonal Notes: Makes use of the Vulkan API by the Khronos Group, make sure to have the SDK Installed.
    Date Created: 2021-06-01
*/ 


//#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <string>
#include <cstring>


class VisualRenderingPipeline {

    // Define "Local" Variables //
    private:

        //// IS THERE A WAY TO PUT EVERYTHING FROM HERE INTO A HEADER FILE? (OR A BETTER WAY TO DO THIS?) ////

        // Set Local Window Params //
        bool LocalWindowEnabled;
        int WindowResolutionX;
        int WindowResolutionY;

        std::string WindowTitle;



        
        // Set Private Ref To Logger //
        LoggerClass Logger;


        // Create Window Object //
        GLFWwindow* window;

        // Declare Vulkan Instance //
        VkInstance instance;

        // Define Vulkan Creation Instance //

        void CreateVulkanInstance() {



        };



    // Define Externally Accessible Objects //
    public:


        // Config Loacing Function //
        void InitializeConfiguration(LoggerClass Logger, const YAML::Node VisualRenderingConfiguration) {

            // TODO: CONFIGURATION DICTIONARY TELLING IT WHAT TO DO ABOUT LOCAL WINDOWS AND OTHER STUFF LIKE THAT.
            // Initialization Message //
            Logger.Log("Initializing Visual Rendering Pipeline");

            // Decode Configuration Dictionary //
            Logger.Log("Loading Configuration File For Visual Configuration Pipeline");

            LocalWindowEnabled = VisualRenderingConfiguration["LocalWindowEnabled"].as<bool>();
            WindowResolutionX = VisualRenderingConfiguration["LocalWindowResolutionX"].as<int>();
            WindowResolutionY = VisualRenderingConfiguration["LocalWindowResolutionY"].as<int>();

            WindowTitle = VisualRenderingConfiguration["LocalWindowTitle"].as<std::string>();

        }


        void InitSystem() {

            // Init Message //
            Logger.Log("Initializing Visual Rendering System");

            // If LocalWindow Is Enabled, Create A Local Window //
            if (LocalWindowEnabled) {

                // Init GLFW //
                Logger.Log("Initializing GLFW Local Window System");
                glfwInit();

                // Set GLFW Configuration Parameters //
                Logger.Log("Setting GLFW Window Parameters");
                glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
                glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

                // Create Window //
                Logger.Log("Creating GLFW Window");
                window = glfwCreateWindow(WindowResolutionX, WindowResolutionY, WindowTitle.c_str(), nullptr, nullptr);

            }


            

            // Create Vulkan Instance //
            Logger.Log("Creating Vulkan Instnace");
            //CreateVulkanInstance();
            


            // Initialize Vulkan //
            Logger.Log("Initializing Vulkan");

            VkApplicationInfo appInfo{};
            appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
            appInfo.pApplicationName = "BrainGenix ERS";
            appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.pEngineName = "ERS-CORE";
            appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
            appInfo.apiVersion = VK_API_VERSION_1_0;

            VkInstanceCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            createInfo.pApplicationInfo = &appInfo;

            // Delcare GLFW Variables //
            uint32_t glfwExtensionCount = 0;
            const char** glfwExtensions;

            // Find GLFW Extension Information //
            if (LocalWindowEnabled) {
                
                // Find Extensions //
                Logger.Log("Finding GLFW Extensions");
                glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

            } else {

                // Default To No Extensions //
                Logger.Log("Local Window System Not Enabled, Setting GLFW Window Extensions To '0'");
                glfwExtensionCount = 0;
            
            }

            // Set GLFW Extension Information //
            Logger.Log("Setting GLFW Extension Information");
            createInfo.enabledExtensionCount = glfwExtensionCount;
            createInfo.ppEnabledExtensionNames = glfwExtensions;


            createInfo.enabledLayerCount = 0;



            // Check Status Of   
            // if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            //     throw std::runtime_error("failed to create instance!");
            // }


        }

        void UpdateProgram() {
            
            // Only Run Stuff Here For GLFW (Local Window) //
            if (LocalWindowEnabled) {

                // Get Local Window Events //    
                glfwPollEvents();
            
            };        
        

        }

        void Cleanup() {

            // Cleanup Local Window, If Used //
            if (LocalWindowEnabled) {
            
                // Cleanup System //
                glfwDestroyWindow(window);
                glfwTerminate();
            
            };

        }

};