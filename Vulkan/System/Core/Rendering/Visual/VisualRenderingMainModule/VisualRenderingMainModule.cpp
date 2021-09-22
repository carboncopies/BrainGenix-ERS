//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing the main pipeline for the 3D visual rendering system.
    Additonal Notes: Makes use of the Vulkan API by the Khronos Group, make sure to have the SDK Installed.
    Date Created: 2021-06-01
*/ 





// NOTE: Add Custom Debug Log Callback Later, allowing us to make use of the Logger class.




//#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>


#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <string>
#include <cstring>
#include <optional>

#include "DeviceSuitability.cpp"



// Set Const //
const std::vector<const char*> validationLayers = {"VK_LAYER_KHRONOS_validation"};

// Create Struct For Queues //
struct QueueFamilyIndices {
    std::optional<uint32_t> graphicsFamily;

    bool isComplete() {
        return graphicsFamily.has_value();
    }
};


// Define Main Class //
class VisualRenderingPipeline {

    // Define "Local" Variables //
    private:

        //// IS THERE A WAY TO PUT EVERYTHING FROM HERE INTO A HEADER FILE? (OR A BETTER WAY TO DO THIS?) ////

        // Set Local Window Params //
        bool LocalWindowEnabled;
        int WindowResolutionX;
        int WindowResolutionY;
        std::string WindowTitle;
        
        // Set Vulkan Config Params //
        bool EnableVulkanDebugging;
        
        // Set Vulkan Related Vars //
        LoggerClass Logger;
        GLFWwindow* window;
        VkInstance instance;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

        // Logical Device //
        VkDevice device;

        // Queue Stuff //
        VkQueue graphicsQueue;

        // Surface Stuff //
        //VkSurfaceKHR surface;





        // Define Functions For ERS //
        bool checkValidationLayerSupport() {
            
            // Define Layer Support Var //
            uint32_t layerCount;

            // Get Support Information //
            vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

            std::vector<VkLayerProperties> availableLayers(layerCount);
            vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

            // Check Requested Layers Exist //
            for (const char* layerName : validationLayers) {
                bool layerFound = false;

                for (const auto& layerProperties : availableLayers) {
                    if (strcmp(layerName, layerProperties.layerName) == 0) {
                        layerFound = true;
                        break;
                    }
                }

                if (!layerFound) {
                    return false;
                }
            }

            return true;

        };


        // Select The Physical GPU To Use //
        void PickPhysicalDevice() {

            // Log Start Message //
            Logger.Log("Identifying Physical GPUs");

            // Get Device Count //
            uint32_t deviceCount = 0;
            vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);

            
            // Check If No Devices Found //
            if (deviceCount == 0) {

                // Present Error Message //
                Logger.Log("Found No Devices, Please Check Your System", 9);
                std::runtime_error("Failed To Find Any GPUs");

            };

            // Create Array To Hold GPU Handles //
            std::vector<VkPhysicalDevice> devices(deviceCount);
            vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());


            // Find Suitable Device //
            Logger.Log("Iterating Through Device List To Identify Suitable Device");
            for (const auto& device : devices) {
                if (IsDeviceSuitable(device)) {

                    // Log That Device Was Found
                    Logger.Log("Identified Suitable Device");
                    physicalDevice = device;

                    // Exit Loop
                    break;
                }
            }

        };


        // Create Logical Device Function //
        void createLogicalDevice() {

            // Specifify Queue Params //
            QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
            queueCreateInfo.queueCount = 1;


            // Set Queue Scheduling Priority //
            float queuePriority = 1.0f;
            queueCreateInfo.pQueuePriorities = &queuePriority;        

            // Set Device Features Used //
            VkPhysicalDeviceFeatures deviceFeatures{};
            // NOTE: MORE TO BE FILLED IN HERE LATER, WHEN WE DO MORE STUFF

            // Create Logical Device //
            VkDeviceCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

            createInfo.pQueueCreateInfos = &queueCreateInfo;
            createInfo.queueCreateInfoCount = 1;

            createInfo.pEnabledFeatures = &deviceFeatures;

            createInfo.enabledExtensionCount = 0;

            // Validation/Debug Layer Backwards Compatibillity //
            if (EnableVulkanDebugging) {
                createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
                createInfo.ppEnabledLayerNames = validationLayers.data();
            } else {
                createInfo.enabledLayerCount = 0;
            }

            
            // Instantiate Vulkan Queue //
            if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {

                // Present Failure Message //
                Logger.Log("Logical Device Creation Failure", 9);
                throw std::runtime_error("Logical Device Creation Failure");
            }

            // Get Device Queues //
            vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
            

        };


        // Find Available Queues //
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device) {
            QueueFamilyIndices indices;

            uint32_t queueFamilyCount = 0;
            vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

            std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
            vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

            int i = 0;
            for (const auto& queueFamily : queueFamilies) {
                if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                    indices.graphicsFamily = i;
                }

                if (indices.isComplete()) {
                    break;
                }

                i++;
            }

            return indices;
        }


        // Define Required Extensions Array //
        std::vector<const char*> getRequiredExtensions() {
            uint32_t glfwExtensionCount = 0;
            const char** glfwExtensions;
            glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

            std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

            // Set Debugging Params For Queue //
            if (EnableVulkanDebugging) {
                extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            }

            return extensions;
        }



    // Define Externally Accessible Objects //
    public:


        // Config Decoding Function //
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

            
            EnableVulkanDebugging = VisualRenderingConfiguration["EnableVulkanDebugging"].as<bool>();

        }


        // Handles Video System Initialization //
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

            // Check Validation Layer Support //
            Logger.Log("Fetching Vulkan Validation Layer Support List");
            if (EnableVulkanDebugging && !checkValidationLayerSupport()) {

                // Present Issue //
                Logger.Log("Validation Layers Enabled In Config, However None Exist", 8);
                Logger.Log("Automatically Disabling Validation Layers", 7);

                // Disable Layer Validation //
                EnableVulkanDebugging = false;
                
            };
            

            // Create Vulkan Instance //
            Logger.Log("Creating Vulkan Instnace");

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



            // Set Debugging Info //
            if (EnableVulkanDebugging) {
                createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
                createInfo.ppEnabledLayerNames = validationLayers.data();
            } else {
                createInfo.enabledLayerCount = 0;
            }

            

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
            if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {

                // Present Failure Message //
                Logger.Log("Vulkan Initialization Failed, Please Check Your Drivers", 9);

                throw std::runtime_error("Vulkan Initialization Has Failed, Please Check Your Drivers");

            }

            // Pick Physical Device //
            PickPhysicalDevice();

        }


        // Called In A Loop, Updates Visuals Onscreen //
        void UpdateProgram() {
            
            // Only Run Stuff Here For GLFW (Local Window) //
            if (LocalWindowEnabled) {

                // Get Local Window Events //    
                glfwPollEvents();
            
            };        
        

        }


        // Called At System Exit, Shuts Down System //
        void Cleanup() {

            // Cleanup Local Window, If Used //
            if (LocalWindowEnabled) {
                
                // Clean Vulkan Instance //
                vkDestroyInstance(instance, nullptr);
                vkDestroyDevice(device, nullptr);


                // Cleanup System //
                glfwDestroyWindow(window);
                glfwTerminate();
            
            };

        }


};