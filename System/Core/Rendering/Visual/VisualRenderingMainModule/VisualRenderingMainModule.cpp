//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing the main pipeline for the 3D visual rendering system.
    Additonal Notes: Makes use of the Vulkan API by the Khronos Group, make sure to have the SDK Installed.
    Date Created: 2021-06-01
*/ 


#include <vulkan/vulkan.h>

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



    // Define Externally Accessible Objects //
    public:

        void InitializeConfiguration(LoggerClass Logger, const YAML::Node VisualRenderingConfiguration) {

            // TODO: CONFIGURATION DICTIONARY TELLING IT WHAT TO DO ABOUT LOCAL WINDOWS AND OTHER STUFF LIKE THAT.
            // Initialization Message //
            Logger.Log("Initializing Visual Rendering Pipeline");

            // Decode Configuration Dictionary //
            Logger.Log("Loading Configuration File For Visual Configuration Pipeline");

            LocalWindowEnabled = VisualRenderingConfiguration["LocalWindowEnabled"].as<bool>();
            WindowResolutionX = VisualRenderingConfiguration["WindowResolutionX"].as<int>();
            WindowResolutionY = VisualRenderingConfiguration["WindowResolutionY"].as<int>();


            // IS THERE A WAY TO FIX THIS???!?!?!?!? //
            // Log Config Params //
            //Logger.Log("Local Window Configuration:", 0);
            //Logger.Log("CONFIG: LocalWindowEnabled" + std::string(LocalWindowEnabled).c_str(), 0);
            //Logger.Log("CONFIG: LocalWindowResolutionX" + std::to_string(WindowResolutionX), 0);
            //Logger.Log("CONFIG: LocalWindowResolutionY" + std::to_string(WindowResolutionY), 0);
            

            // If LocalWindow Is Enabled, Create A Local Window //
            if (LocalWindowEnabled) {
                
            }

        }


        void InitVulkan() {

        }

        void MainLoop() {

        }

        void Cleanup() {

        }

    // public:
    //     void run() {
    //         GatherParameters();
    //         InitVulkan();
    //         MainLoop();
    //         Cleanup();
    //     }




};