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

        // Declare Logger
        LoggerClass Logger_;
        YAML::Node SystemConfiguration_;

        // Declare Config Vars
        bool LocalWindowEnabled_;
        bool SystemShutdownInvoked_;

        // Delcare Class Instances
        LocalWindowDisplaySystem sERSLocalWindowDisplaySystem_;
        VkInstance VulkanInstance_;


        // Initialize Vulkan API
        void InitVulkan();

        // Create Vulkan Instance
        void CreateVulkanInstance();


    public:

        // Initialize VisualRendering Subsystem
        void InitializeSystem(LoggerClass sERSLogger, YAML::Node sERSConfig, bool ShutdownToggle);

        // Main Loop For Visual Renderer
        void RenderLoop();

        // Destructor
        void CleanUp();



};