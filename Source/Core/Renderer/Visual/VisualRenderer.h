//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing the main renderer system.
    Additonal Notes: None
    Date Created: 2021-10-13
*/ 

#pragma once

 
// Define Visual Renderer Class
class VisualRenderer {

    private:

        // Declare Params
        LoggerClass Logger_;
        YAML::Node SystemConfiguration_;

        // Define Validation Later
        const std::vector<const char*> ValidationLayers_ = {
            "VK_LAYER_KHRONOS_validation"
        };

        // Declare Config Vars
        bool LocalWindowEnabled_;
        bool SystemShutdownInvoked_;
        bool ValidationLayersToBeUsed_;

        // Delcare Class Instances
        LocalWindowDisplaySystem sERSLocalWindowDisplaySystem_;
        VkInstance VulkanInstance_;
        VkPhysicalDevice PhysicalDevice_;


        // Initialize Vulkan API
        void InitVulkan();

        // Create Vulkan Instance
        void CreateVulkanInstance();

        // Check Validation Layer Support
        bool CheckValidationLayerSupport();

        // Select Physical Device
        void PickPhysicalDevice();

        // Rate Device Suitability
        int RateDeviceSuitability(VkPhysicalDevice Device);


    public:

        // Initialize VisualRendering Subsystem
        void InitializeSystem(LoggerClass sERSLogger, YAML::Node sERSConfig, bool ShutdownToggle);

        // Main Loop For Visual Renderer
        void RenderLoop();

        // Destructor
        void CleanUp();



};