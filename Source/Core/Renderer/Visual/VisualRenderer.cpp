//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing the main renderer system.
    Additonal Notes: None
    Date Created: 2021-10-13
*/ 

#include <vulkan/vulkan.h>

#include "Core/Renderer/Visual/LocalWindowDisplaySystem.cpp"

#include "Core/Renderer/Visual/VisualRenderer.h"



// Define VisualRenderer::InitializeSystem
void VisualRenderer::InitializeSystem(LoggerClass sERSLogger, YAML::Node sERSConfig) {

    // Create Local References
    Logger = sERSLogger;
    SystemConfiguration = sERSConfig;

    // Initialize GLFW
    Logger.Log("Reading System Configuration For 'BOOL': 'WindowEnabled'", 2);
    LocalWindowEnabled = SystemConfiguration["WindowEnabled"].as<bool>();
    if (LocalWindowEnabled) {
        Logger.Log("Initializing 'Core::Renderer::Visual::LocalWindowDisplaySystem'", 4);
        sERSLocalWindowDisplaySystem.InitWindow(Logger, SystemConfiguration);
        Logger.Log("Initialized 'Core::Renderer::Visual::LocalWindowDisplaySystem'", 3);
    } else {
        Logger.Log("Initialization Skip 'Core::Renderer::Visual::LocalWindowDisplaySystem' Due To Config Param", 3);
    };

    // Initialize Vulkan
    Logger.Log("Initializing 'Core::Renderer::Visual::VisualRenderer::Vulkan'", 4);
    InitVulkan();
    Logger.Log("Initialized 'Core::Renderer::Visual::VisualRenderer::Vulkan'", 3);

}

// Define VisualRenderer::InitVulakn
void VisualRenderer::InitVulkan() {

    // Log Vulkan Init Creation
    Logger.Log("Initializng Vulkan API", 4);

    // Create Vulkan Instance
    Logger.Log("Initializng 'Core::Renderer::Visual::VisualRenderer::CreateVulkanInstance'", 3);
    CreateVulkanInstance();
    Logger.Log("Initializng 'Core::Renderer::Visual::VisualRenderer::CreateVulkanInstance'", 2);

}

// Define VisualRenderer::CreateVulkanInstance
void VisualRenderer::CreateVulkanInstance() {

    // Fill AppInfo Struct
    Logger.Log("Populating Vulkan 'appInfo' Struct", 3);

    VkApplicationInfo AppInfo{};
    AppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    AppInfo.pApplicationName = "BrainGenix::ERS (Environment Rendering System)";
    AppInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    AppInfo.pEngineName = "BrainGenix::ERS";
    AppInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    AppInfo.apiVersion = VK_API_VERSION_1_0;

    // Vulkan Instance Creation Information
    Logger.Log("Generating VKInstanceCreateInfo", 3);
    VkInstanceCreateInfo VkCreateInfo{};
    VkCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    VkCreateInfo.pApplicationInfo = &AppInfo;

    // If GLFW Enabled
    if (LocalWindowEnabled) {
        VkCreateInfo = sERSLocalWindowDisplaySystem.GetVulkanInitExtensions(VkCreateInfo);
    }


}


// Define VisualRenderer::RenderLoop
void VisualRenderer::RenderLoop() {

    // GLFW Poll Events
    sERSLocalWindowDisplaySystem.FetchEvents();

}

// Define VisualRenderer::CleanUp
void VisualRenderer::CleanUp() {

    // Log Shutdown Called
    Logger.Log("Shutting Down 'Core::Renderer::Visual::VisualRenderer'", 5);

    // Call Subclass's Destructors
    sERSLocalWindowDisplaySystem.CleanUp();

}