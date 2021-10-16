//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing the main renderer system.
    Additonal Notes: None
    Date Created: 2021-10-13
*/ 

#include <vulkan/vulkan.h>
#include <vector>
#include <cstring>
#include <optional>
#include <set>

#include "Core/Renderer/Visual/LocalWindowDisplaySystem.cpp"

#include "Core/Renderer/Visual/VisualRenderer.h"



// Define VisualRenderer::InitializeSystem
void VisualRenderer::InitializeSystem(LoggerClass sERSLogger, YAML::Node sERSConfig, bool ShutdownToggle) {

    // Create Local References
    Logger_ = sERSLogger;
    SystemConfiguration_ = sERSConfig;
    SystemShutdownInvoked_ = ShutdownToggle;

    // Initialize GLFW
    Logger_.Log("Reading System Configuration For 'BOOL': 'WindowEnabled'", 2);
    LocalWindowEnabled_ = SystemConfiguration_["WindowEnabled"].as<bool>();
    if (LocalWindowEnabled_) {
        Logger_.Log("Initializing 'Core::Renderer::Visual::LocalWindowDisplaySystem'", 4);
        sERSLocalWindowDisplaySystem_.InitWindow(Logger_, SystemConfiguration_);
        Logger_.Log("Initialized 'Core::Renderer::Visual::LocalWindowDisplaySystem'", 3);
    } else {
        Logger_.Log("Initialization Skip 'Core::Renderer::Visual::LocalWindowDisplaySystem' Due To Config Param", 3);
    };

    // Initialize Vulkan
    Logger_.Log("Initializing 'Core::Renderer::Visual::VisualRenderer::Vulkan'", 4);
    InitVulkan();
    Logger_.Log("Initialized 'Core::Renderer::Visual::VisualRenderer::Vulkan'", 3);

}

// Define VisualRenderer::InitVulakn
void VisualRenderer::InitVulkan() {

    // Log Vulkan Init Creation
    Logger_.Log("Initializing Vulkan API", 4);

    // Create Vulkan Instance
    Logger_.Log("Initializing 'Core::Renderer::Visual::VisualRenderer::CreateVulkanInstance'", 3);
    CreateVulkanInstance();
    Logger_.Log("Initialized 'Core::Renderer::Visual::VisualRenderer::CreateVulkanInstance'", 2);

    // Create Display Surface
    if (LocalWindowEnabled_) {
        Logger_.Log("Initialization [ START] 'Core::Renderer::Visual::LocalWindowDisplaySystem::CreateSurface'", 3);
        sERSLocalWindowDisplaySystem_.CreateSurface(VulkanInstance_);
        Logger_.Log("Initialization [FINISH] 'Core::Renderer::Visual::LocalWindowDisplaySystem::CreateSurface'", 2);
    } else {
        Logger_.Log("Initialization [SKIP] [Configuration DISABLED] 'Core::Renderer::Visual::LocalWindowDisplaySystem::CreateSurface'", 2);
    }

    // Pick Physical Device
    Logger_.Log("Initializing 'Core::Renderer::Visual::VisualRenderer::PickPhysicalDevice", 3);
    PickPhysicalDevice();
    Logger_.Log("Initialized 'Core::Renderer::Visual::VisualRenderer::PickPhysicalDevice", 2);

    // Create Logical Device
    Logger_.Log("Initializing 'Core::Renderer::Visual::VisualRenderer::CreateLogicalDevice", 3);
    CreateLogicalDevice();
    Logger_.Log("Initializing 'Core::Renderer::Visual::VisualRenderer::CreateLogicalDevice", 2);


}

// Define VisualRenderer::CreateLogicalDevice
void VisualRenderer::CreateLogicalDevice() {

    // Create Logical Device
    Logger_.Log("Getting Queue Families For Selected Device", 3);
    QueueFamilyIndices Indices = FindQueueFamilies(PhysicalDevice_, false);

    // Setup Creation Process
    Logger_.Log("Configuring 'VkDeviceQueueCreateInfo' Struct", 3);
    std::vector<VkDeviceQueueCreateInfo> QueueCreateInfos;
    std::set<uint32_t> UniqueQueueFamilies = {Indices.GraphicsFamily.value(), Indices.PresentFamily.value()};

    float QueuePriority = 1.0f;
    for (uint32_t QueueFamily : UniqueQueueFamilies) {

        VkDeviceQueueCreateInfo QueueCreateInfo{};
        QueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        QueueCreateInfo.queueFamilyIndex = QueueFamily;
        QueueCreateInfo.queueCount = 1;
        QueueCreateInfo.pQueuePriorities = &QueuePriority;
        QueueCreateInfos.push_back(QueueCreateInfo);

    }



    // Set Device Features
    Logger_.Log("Setting Required Device Features", 2);
    VkPhysicalDeviceFeatures DeviceFeatures{};

    // Configure Logical Device
    Logger_.Log("Configuring 'VkDeviceCreateInfo' Struct", 5);
    VkDeviceCreateInfo CreateInfo{};

    CreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    CreateInfo.queueCreateInfoCount = static_cast<uint32_t>(QueueCreateInfos.size());
    CreateInfo.pQueueCreateInfos = QueueCreateInfos.data();

    CreateInfo.pEnabledFeatures = &DeviceFeatures;
    CreateInfo.enabledExtensionCount = 0;

    if (ValidationLayersToBeUsed_) {
        CreateInfo.enabledLayerCount = static_cast<uint32_t>(ValidationLayers_.size());
        CreateInfo.ppEnabledLayerNames = ValidationLayers_.data();
    } else {
        CreateInfo.enabledLayerCount = 0;
    }

    // Create 



    // Creating Logical Device
    Logger_.Log("Creating Logical Device Instance", 3);
    if (vkCreateDevice(PhysicalDevice_, &CreateInfo, nullptr, &LogicalDevice_) != VK_SUCCESS) {

        // Logical Device Creation Failure
        Logger_.Log("Failed To Create Logical Device, System Shutting Down", 10);
        SystemShutdownInvoked_ = true;
    }

    // Setup Graphics Queue
    Logger_.Log("Setting Up Graphics Queue", 2);
    vkGetDeviceQueue(LogicalDevice_, Indices.GraphicsFamily.value(), 0, &GraphicsQueue_);


}

// Define VisualRenderer::FindQueueFamilies
QueueFamilyIndices VisualRenderer::FindQueueFamilies(VkPhysicalDevice Device, bool IndentLogs) {

    // Initialize Struct
    QueueFamilyIndices Indices;

    // Find Graphics Queue Family
    if (IndentLogs) {
        Logger_.Log("        Querying Number Of Queue Families", 3);
    } else {
        Logger_.Log("Querying Number Of Queue Families", 3);
    }

    uint32_t QueueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(Device, &QueueFamilyCount, nullptr);

    // Check Log Indentation Level
    if (IndentLogs) {
        Logger_.Log(std::string(std::string("        Found ") + std::to_string(QueueFamilyCount) + std::string(" Queue Families")).c_str(), 2);
    } else {
        Logger_.Log(std::string(std::string("Found ") + std::to_string(QueueFamilyCount) + std::string(" Queue Families")).c_str(), 2);
    }
    
    std::vector<VkQueueFamilyProperties> QueueFamilies(QueueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(Device, &QueueFamilyCount, QueueFamilies.data());

    // Iterate Through Queues
    int Index = 0;
    for (const auto& QueueFamily : QueueFamilies) {

        // Check If Queue Family Has Requred Features
        if (QueueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            Indices.GraphicsFamily = Index;
        }

        // Check For Present Support If Required
        if (LocalWindowEnabled_) {
            VkBool32 PresentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(Device, Index, sERSLocalWindowDisplaySystem_.Surface_, &PresentSupport);

            if (PresentSupport) {
                Indices.PresentFamily = Index;
            }
        }

        Index++;


    }

    // Return Results
    return Indices;

}

// Define VisualRenderer::PickPhysicalDevice
void VisualRenderer::PickPhysicalDevice() {

    // Log Selection Process
    Logger_.Log("Querying Available Graphics Processers", 5);

    // Get List Of GPUS
    uint32_t DeviceCount = 0;
    vkEnumeratePhysicalDevices(VulkanInstance_, &DeviceCount, nullptr);
    Logger_.Log(std::string(std::string("Found ") + std::to_string(DeviceCount) + std::string(" Physical Devices")).c_str(), 4);

    std::vector<VkPhysicalDevice> Devices(DeviceCount);
    vkEnumeratePhysicalDevices(VulkanInstance_, &DeviceCount, Devices.data());

    // Create Map Of Device Suitabillity
    std::multimap<int, VkPhysicalDevice> DeviceCandidates;

    // Identify And Score Physical Devices
    PhysicalDevice_ = VK_NULL_HANDLE;
    for (const auto& Device : Devices) {
        int Score = RateDeviceSuitability(Device);
        DeviceCandidates.insert(std::make_pair(Score, Device));
    }

    // Pick Best Device Candidate
    if (DeviceCandidates.rbegin()->first > 0) {
        PhysicalDevice_ = DeviceCandidates.rbegin()->second;
        Logger_.Log("Identified Suitable Physical Device", 4);
    } else {
        Logger_.Log("No Suitable Physical Device Found, Exiting", 10);
        SystemShutdownInvoked_ = true;
    }

}

// Define VisualRenderer::RateDeviceSuitability
int VisualRenderer::RateDeviceSuitability(VkPhysicalDevice Device) {

    // Get Device Properties
    VkPhysicalDeviceProperties DeviceProperties;
    VkPhysicalDeviceFeatures DeviceFeatures;

    vkGetPhysicalDeviceProperties(Device, &DeviceProperties);
    vkGetPhysicalDeviceFeatures(Device, &DeviceFeatures);


    // Score Device -- Success Cases
    int Score = 0;

    // Check GPU Descrete Or Integrated
    if (DeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
        Score += 1000;
    };

    // Get Max Texture Size
    Score += DeviceProperties.limits.maxImageDimension2D;
    

    // Log Device + Score
    Logger_.Log(std::string("    Found Physical Device With Name: " + std::string(DeviceProperties.deviceName) + std::string(", Score ") + std::to_string(Score)).c_str(), 4);



    // Score Device -- Failure Cases
        
    // Check If Device Supports Geometry Shaders
    if (!DeviceFeatures.geometryShader) {
        return 0;
    }

    // Check If Device Supports Queue Families
    QueueFamilyIndices Indices = FindQueueFamilies(Device);
    if (!Indices.GraphicsFamily.has_value()) {
        return 0;
    }




    // Return Device Score
    return Score;

}

// Define VisualRenderer::CreateVulkanInstance
void VisualRenderer::CreateVulkanInstance() {

    // Fill AppInfo Struct
    Logger_.Log("Populating Vulkan 'appInfo' Struct", 3);

    VkApplicationInfo AppInfo{};
    AppInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    AppInfo.pApplicationName = "BrainGenix::ERS (Environment Rendering System)";
    AppInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    AppInfo.pEngineName = "BrainGenix::ERS";
    AppInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    AppInfo.apiVersion = VK_API_VERSION_1_0;

    // Vulkan Instance Creation Information
    Logger_.Log("Generating VKInstanceCreateInfo", 3);
    VkInstanceCreateInfo VkCreateInfo{};
    VkCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    VkCreateInfo.pApplicationInfo = &AppInfo;

    // If GLFW Enabled
    if (LocalWindowEnabled_) 
        VkCreateInfo = sERSLocalWindowDisplaySystem_.GetVulkanInitExtensions(VkCreateInfo);




    // Check For Validation Layers
    Logger_.Log("Reading System Configuration For 'BOOL': 'EnableValidationLayers'", 2);
    bool ValidationLayersRequested = SystemConfiguration_["EnableValidationLayers"].as<bool>();

    if (ValidationLayersRequested) {
        
        // Check For Validation Layer Support
        Logger_.Log("Validation Layers Requested", 2);
        ValidationLayersToBeUsed_ = CheckValidationLayerSupport();

    } else {

        // Validation Layers Not Requested
        Logger_.Log("Validation Layers Disabled In Configuration File", 2);

    }

    // Enable Validation Layers If To Be Used
    if (ValidationLayersToBeUsed_) {

        // Add Validation Layers To Create Info
        Logger_.Log("Adding Enabled Validation Layers To Vulkan Instance Creation Information", 4);
        VkCreateInfo.enabledLayerCount = static_cast<uint32_t>(ValidationLayers_.size());
        VkCreateInfo.ppEnabledLayerNames = ValidationLayers_.data();
    } else {

        // Disable Validation Layers
        Logger_.Log("Disabling Validation Layers In Vulkan Creation Information", 4);
        VkCreateInfo.enabledLayerCount = 0;
    }




    // Create Vulkan Instance
    Logger_.Log("Creating Vulkan Instance", 3);
    VkResult Result = vkCreateInstance(&VkCreateInfo, nullptr, &VulkanInstance_);

    // Check State Of Vulkan Instance Creation
    if (Result != VK_SUCCESS) {
        Logger_.Log("Failed To Create Vulkan Instance", 10);

        // Invoke System Shutdown
        SystemShutdownInvoked_ = true;
    } else {
        Logger_.Log("Created Vulkan Instance", 3);
    }


    // Extension Support
    Logger_.Log("Checking For Vulkan Extension Support", 4);
    
    // Get Number Of Extensions
    Logger_.Log("Querying Number Of Supported Extensions", 3);
    uint32_t ExtensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &ExtensionCount, nullptr);

    std::vector<VkExtensionProperties> Extensions(ExtensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &ExtensionCount, Extensions.data());
    Logger_.Log(std::string(std::string("Found ") + std::to_string(ExtensionCount) + std::string(" Vulkan Extensions")).c_str(), 2);

    // Query Extension Information
    Logger_.Log("Enumerating Available Vulkan Extensions:", 4);
    for (auto& Extension : Extensions) {
        Logger_.Log(std::string(std::string("\t Found Vulkan Extension: ") + std::string(Extension.extensionName)).c_str(), 1);
    }

}

// Define VisualRenderer::CheckValidationLayerSupport
bool VisualRenderer::CheckValidationLayerSupport() {

    // Check For Validation Layer Support
    Logger_.Log("Checking For Validation Layer Support", 4);

    uint32_t ValidationLayerCount;
    vkEnumerateInstanceLayerProperties(&ValidationLayerCount, nullptr);

    std::vector<VkLayerProperties> AvailableValidationLayers(ValidationLayerCount);
    vkEnumerateInstanceLayerProperties(&ValidationLayerCount, AvailableValidationLayers.data());

    // Iterate Through Required Layers
    for (const char* LayerName : ValidationLayers_) {

        bool ValidationLayerFound = false;
        Logger_.Log(std::string(std::string("Checking Available Layers For Validation Layer: ") + std::string(LayerName)).c_str(), 2);

        // Check If Layer In Available Layers
        for (const auto& LayerProperties : AvailableValidationLayers) {
            if (strcmp(LayerName, LayerProperties.layerName) == 0) {
                
                // Layer Found
                Logger_.Log(std::string(std::string("Found Validation Layer: ") + std::string(LayerName)).c_str(), 1);
                ValidationLayerFound = true;
                break;
            }
        }

        // If Layer Not Found
        if (!ValidationLayerFound) {
            
            // Layer NOT Found
            Logger_.Log(std::string(std::string("Failed To Find Validation Layer: ") + std::string(LayerName)).c_str(), 6);
            Logger_.Log("Validation Layers Disabled Due To Missing Layer(s), Please Check Your Installation Of The Vulkan SDK", 6);
            return false;
        }


    }

    // If All Layers Were Found, Return True
    return true;

}

// Define VisualRenderer::RenderLoop
void VisualRenderer::RenderLoop() {

    // GLFW Poll Events
    sERSLocalWindowDisplaySystem_.FetchEvents();

}

// Define VisualRenderer::CleanUp
void VisualRenderer::CleanUp() {

    // Log Shutdown Called
    Logger_.Log("Shutting Down 'Core::Renderer::Visual::VisualRenderer'", 5);

    // Call Subclass's Destructors
    sERSLocalWindowDisplaySystem_.CleanUp();

    // Destroy LogicalDevice
    vkDestroyDevice(LogicalDevice_, nullptr);

    // Destroy Vulkan Instance
    vkDestroyInstance(VulkanInstance_, nullptr);

}