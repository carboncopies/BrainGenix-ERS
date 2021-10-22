//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing the main renderer system.
    Additonal Notes: None
    Date Created: 2021-10-13
*/ 

#pragma once



// Queue Struct
struct QueueFamilyIndices {

    // Hold Graphcis/Present Queues
    std::optional<uint32_t> GraphicsFamily;
    std::optional<uint32_t> PresentFamily;


    // Checks If Struct Populated
    bool IsComplete() {
        return GraphicsFamily.has_value() && PresentFamily.has_value();
    }
};

// SwapChain Struct
struct SwapChainSupportDetails {

    // Hold Swapchain Parameters
    VkSurfaceCapabilitiesKHR Capabilities;
    std::vector<VkSurfaceFormatKHR> Formats;
    std::vector<VkPresentModeKHR> PresentModes;

};


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

        // Define Device Extensions
        const std::vector<const char*> DeviceExtensions_ = {
            VK_KHR_SWAPCHAIN_EXTENSION_NAME
        };

        // Declare Config Vars
        bool LocalWindowEnabled_;
        bool SystemShutdownInvoked_;
        bool ValidationLayersToBeUsed_;

        // Delcare Class Instances
        LocalWindowDisplaySystem sERSLocalWindowDisplaySystem_;
        VkInstance VulkanInstance_;
        VkPhysicalDevice PhysicalDevice_;
        VkDevice LogicalDevice_;
        VkQueue GraphicsQueue_;
        VkQueue PresentationQueue_;
        VkSwapchainKHR SwapChain_;
        std::vector<VkImage> SwapChainImages_;
        VkFormat SwapChainImageFormat_;
        VkExtent2D SwapChainExtent_;
        std::vector<VkImageView> SwapChainImageViews_;
        VkPipelineLayout PipelineLayout_;
        VkRenderPass RenderPass_;
        VkPipeline GraphicsPipeline_;
        std::vector<VkFramebuffer> SwapChainFramebuffers_;
        VkCommandPool CommandPool_;
        std::vector<VkCommandBuffer> CommandBuffers_;
        int MaxFramesInFlight_;
        
        std::vector<VkSemaphore> ImageAvailableSemaphores_;
        std::vector<VkSemaphore> RenderFinishedSemaphores_;
        std::vector<VkFence> InFlightFences_;
        std::vector<VkFence> ImagesInFlight_;
        size_t CurrentFrame_;

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

        // Find Queue Familys
        QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice Device, bool IndentLogs = true);

        // Create Logical Device
        void CreateLogicalDevice();

        // Check Device Swapchain Extension Support
        bool CheckDeviceExtensionSupport(VkPhysicalDevice Device, bool IndentLogs = true);

        // Populate Swapchain Info
        SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice Device, bool IndentLogs = true);

        // Choose Swapchain Format
        VkSurfaceFormatKHR ChooseSwapChainSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& AvailableFormats);

        // Choose Swapchain Present Mode
        VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& AvailablePresentModes);

        // Choose Swap Extent
        VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& Capabilities);

        // Create Swap Chain
        void CreateSwapChain();

        // Create Image Views
        void CreateImageViews();

        // Create Graphics Pipeline
        void CreateGraphicsPipeline();

        // Create ShaderModule Function
        VkShaderModule CreateShaderModule(const std::vector<char>& Code);

        // Create Render Pass
        void CreateRenderPass();

        // Setup Framebuffers
        void CreateFramebuffers();

        // Setup Command Pool
        void CreateCommandPool();

        // Create Command Buffers
        void CreateCommandBuffers();

        // Create Sync Objects
        void CreateSyncObjects();

        // Draw Frame
        void DrawFrame();


    public:

        // Initialize VisualRendering Subsystem
        void InitializeSystem(LoggerClass sERSLogger, YAML::Node sERSConfig, bool ShutdownToggle);

        // Main Loop For Visual Renderer
        void RenderLoop();

        // Destructor
        void CleanUp();



};