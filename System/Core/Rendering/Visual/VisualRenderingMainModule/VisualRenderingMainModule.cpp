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

class VisualRenderingPipeline {

    // Define "Local" Variables //
    private:

        // Set Local Window Params //
        bool LocalWindowEnabled;
        int WindowResolutionX;
        int WindowResolutionY;



    // Define Externally Accessible Objects //
    public:

        void InitializeConfiguration() {

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