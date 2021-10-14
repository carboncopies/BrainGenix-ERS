//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing the visual local display system.
    Additonal Notes: None
    Date Created: 2021-10-13
*/ 

#include <GLFW/glfw3.h>
#include <string>

#include "Core/Renderer/Visual/LocalWindowDisplaySystem.h"



// Define LocalWindowDisplaySystem::InitWindow
void LocalWindowDisplaySystem::InitWindow(LoggerClass sERSLogger, YAML::Node sERSConfig) {

    // Create Local References
    Logger = sERSLogger;
    SystemConfiguration = sERSConfig;

    // Log Initialization
    Logger.Log("Initializing GLFW", 1);

    // Initialize GLFW
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // Log Initialization
    Logger.Log("Initialized GLFW", 0);


    // Read Window Configuration Parameters
    Logger.Log("Creating GLFWWindow Surface", 3);
    Logger.Log("Reading System Configuration For 'INT': 'WindowWidth'", 2);
    WindowX = SystemConfiguration["WindowWidth"].as<int>();
    Logger.Log("Reading System Configuration For 'INT': 'WindowHeight'", 2);
    WindowY = SystemConfiguration["WindowHeight"].as<int>();
    Logger.Log("Reading System Configuration For 'STD::STRING': 'WindowTitle'", 2);
    WindowTitle = SystemConfiguration["WindowTitle"].as<std::string>();
    
    // Create Window
    Window = glfwCreateWindow(WindowX, WindowY, WindowTitle.c_str(), nullptr, nullptr);
    Logger.Log("Created GLFWWindow Surface", 2);

}

// Define LocalWindowDisplaySystem::GetVulkanInitExtensions
VkInstanceCreateInfo LocalWindowDisplaySystem::GetVulkanInitExtensions(VkInstanceCreateInfo VkCreateInfo) {

    // Generate GLFW Required Vulkan Extensions Info
    Logger.Log("Getting GLFW Required Vulkan Extensions", 3);
    uint32_t GLFWExtensionCount = 0;
    const char** GLFWExtensions;

    GLFWExtensions = glfwGetRequiredInstanceExtensions(&GLFWExtensionCount);

    VkCreateInfo.enabledExtnesionCount = GLFWExtensionCount;
    VkCreateInfo.ppEnabledExtensionNames = GLFWExtensions;

    // Return VkCreateInfo
    return VkCreateInfo;

}


// Define LocalWindowDisplaySystem::FetchEvents
void LocalWindowDisplaySystem::FetchEvents() {

    // Poll Events
    glfwPollEvents();

}

// Define LocalWindowDisplaySystem::CleanUp
void LocalWindowDisplaySystem::CleanUp() {

    // Cleanup System
    Logger.Log("Tearing Down GLFW Window", 4);
    glfwDestroyWindow(Window);

    Logger.Log("Terminating GLFW", 3);
    glfwTerminate();

}