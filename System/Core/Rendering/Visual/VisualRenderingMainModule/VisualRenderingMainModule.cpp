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

        // Set Local Window Params //
        bool LocalWindowEnabled;
        int WindowResolutionX;
        int WindowResolutionY;

        std::string WindowTitle;

        
        // Set Private Ref To Logger //
        LoggerClass Logger;


        // Create Window Object //
        GLFWwindow* window;



    // Define Externally Accessible Objects //
    public:

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
                glfwInit();

                // Set GLFW Configuration Parameters //
                glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
                glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

                // Create Window //
                window = glfwCreateWindow(WindowResolutionX, WindowResolutionY, WindowTitle.c_str(), nullptr, nullptr);

            }

        }

        void UpdateProgram() {
            
            // Only Run Stuff Here For GLFW (Local Window) //
            if (LocalWindowEnabled) {

                // Get Local Window Events //    
                glfwPollEvents();
            
            };        
        

        }

        void Cleanup() {

        }

};