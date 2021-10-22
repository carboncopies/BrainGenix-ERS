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
void LocalWindowDisplaySystem::InitWindow(LoggerClass sERSLogger, YAML::Node sERSConfig, bool* SystemShutdownState) {

    // Create Local References
    Logger_ = sERSLogger;
    SystemConfiguration_ = sERSConfig;
    SystemShutdownInvoked_ = SystemShutdownState;

    // Log Initialization
    Logger_.Log("Initializing GLFW", 1);

    // Initialize GLFW
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    //glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    // Log Initialization
    Logger_.Log("Initialized GLFW", 0);


    // Read Window Configuration Parameters
    Logger_.Log("Creating GLFWWindow Surface", 3);
    Logger_.Log("Reading System Configuration For 'INT': 'WindowWidth'", 2);
    WindowX_ = SystemConfiguration_["WindowWidth"].as<int>();
    Logger_.Log("Reading System Configuration For 'INT': 'WindowHeight'", 2);
    WindowY_ = SystemConfiguration_["WindowHeight"].as<int>();
    Logger_.Log("Reading System Configuration For 'STD::STRING': 'WindowTitle'", 2);
    WindowTitle_ = SystemConfiguration_["WindowTitle"].as<std::string>();
    
    // Create Window
    Window_ = glfwCreateWindow(WindowX_, WindowY_, WindowTitle_.c_str(), nullptr, nullptr);
    glfwSetWindowUserPointer(Window_, this);
    glfwSetFramebufferSizeCallback(Window_, FrameBufferResizeCallback);
    Logger_.Log("Created GLFWWindow Surface", 2);

}

// Define LocalWindowDisplaySystem::FrameBufferResizeCallback
static void FrameBufferResizeCallback(GLFWwindow* Window, int Width, int Height) {

    auto App = reinterpret_cast<LocalWindowDisplaySystem*>(glfwGetWindowUserPointer(Window_));
    App->FramebufferResized = true;

}

// Define LocalWindowDisplaySystem::GetVulkanInitExtensions
VkInstanceCreateInfo LocalWindowDisplaySystem::GetVulkanInitExtensions(VkInstanceCreateInfo VkCreateInfo) {

    // Generate GLFW Required Vulkan Extensions Info
    Logger_.Log("Getting GLFW Required Vulkan Extensions", 3);
    uint32_t GLFWExtensionCount = 0;
    const char** GLFWExtensions;

    GLFWExtensions = glfwGetRequiredInstanceExtensions(&GLFWExtensionCount);

    VkCreateInfo.enabledExtensionCount = GLFWExtensionCount;
    VkCreateInfo.ppEnabledExtensionNames = GLFWExtensions;

    // Return VkCreateInfo
    return VkCreateInfo;

}

// Define LocalWindowDisplaySystem::CreateSurface
void LocalWindowDisplaySystem::CreateSurface(VkInstance VulkanInstance) {

    // Create Window Surface
    Logger_.Log("Creating Window Display Surface", 5);

    HasSurfaceBeenInitialized_ = true;
    VulkanInstance_ = VulkanInstance;

    if (glfwCreateWindowSurface(VulkanInstance_, Window_, nullptr, &Surface_) != VK_SUCCESS) {
        Logger_.Log("Failed To Create Window Display Surface", 10);
        // Shutdown system here.
    }

}

// Define LocalWindowDisplaySystem::FetchEvents
void LocalWindowDisplaySystem::FetchEvents() {

    // Poll Events
    glfwPollEvents();

    if (glfwWindowShouldClose(Window_)) {
        Logger_.Log("System Shutdown Invoked By LOCALWINDOW", 7);
        *SystemShutdownInvoked_ = true;
    }

}

// Define LocalWindowDisplaySystem::CleanUp
void LocalWindowDisplaySystem::CleanUp() {

    // Cleanup System
    if (HasSurfaceBeenInitialized_) {
        Logger_.Log("Destroying VK Display Surface", 4);
        vkDestroySurfaceKHR(VulkanInstance_, Surface_, nullptr);
    }

    Logger_.Log("Tearing Down GLFW Window", 4);
    glfwDestroyWindow(Window_);

    Logger_.Log("Terminating GLFW", 3);
    glfwTerminate();

}