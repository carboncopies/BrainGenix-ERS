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
#include <cstdint>
#include <algorithm>
#include <glm/glm.hpp>
#include <array>

#include "Core/Renderer/Visual/LocalWindowDisplaySystem.cpp"
#include "Core/Loader/Shaders/ShaderLoader.cpp"

#include "Core/Renderer/Visual/VisualRenderer.h"



// Define VisualRenderer::InitializeSystem
void VisualRenderer::InitializeSystem(LoggerClass sERSLogger, YAML::Node sERSConfig, bool* ShutdownToggle) {

    // Create Local References
    Logger_ = sERSLogger;
    SystemConfiguration_ = sERSConfig;
    SystemShutdownInvoked_ = ShutdownToggle;

    // Grab Configuration Parameters
    Logger_.Log("Reading System Configuration for 'INT': 'MaxFramesInFlight'", 2);
    MaxFramesInFlight_ = SystemConfiguration_["MaxFramesInFlight"].as<int>();

    // Initialize GLFW
    Logger_.Log("Reading System Configuration For 'BOOL': 'WindowEnabled'", 2);
    LocalWindowEnabled_ = SystemConfiguration_["WindowEnabled"].as<bool>();
    if (LocalWindowEnabled_) {
        Logger_.Log("Initializing 'Core::Renderer::Visual::LocalWindowDisplaySystem'", 4);
        sERSLocalWindowDisplaySystem_.InitWindow(Logger_, SystemConfiguration_, SystemShutdownInvoked_);
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
    Logger_.Log("Initialized 'Core::Renderer::Visual::VisualRenderer::CreateLogicalDevice", 2);


    // Create Swapchain
    if (LocalWindowEnabled_) {
        Logger_.Log("INIT [ START] Creating Swap Chain", 3);
        CreateSwapChain();
        Logger_.Log("INIT [FINISH] Created Swap Chain", 2);
    } else {
        Logger_.Log("INIT [  SKIP] [CONFIGURATION DISABLE] Skipping Swapchain Initialization", 3);
    }

    // Create Image Views
    if (LocalWindowEnabled_) {
        Logger_.Log("Initialization [ START] Creating Image Views", 3);
        CreateImageViews();
        Logger_.Log("Initialization [FINISH] Created Image Views", 2);
    } else {
        Logger_.Log("Initialization [  SKIP] [CONFIGURATION DISABLE] Skipping Image View Creation", 3);
    }

    // Setup Render Passes
    Logger_.Log("Initialization [ START] Creating Render Passes", 3);
    CreateRenderPass();
    Logger_.Log("Initialization [FINISH] Created Render Passes", 2);


    // Create Graphics Pipeline
    Logger_.Log("Initialization [ START] Creating Graphics Pipeline", 3);
    CreateGraphicsPipeline();
    Logger_.Log("Initialization [FINISH] Created Graphics Pipeline", 2);


    // Setup Framebuffers
    if (LocalWindowEnabled_) {
        Logger_.Log("Initialization [ START] Creating Framebuffer", 3);
        CreateFramebuffers();
        Logger_.Log("Initialization [FINISH] Created Framebuffer", 2);
    } else {
        Logger_.Log("Initialization [  SKIP] [CONFIGURATION DISABLE] Skipping Framebuffer Creation", 3);
    }


    // Create Command Pool
    Logger_.Log("Initialization [ START] Creating Command Pool", 3);
    CreateCommandPool();
    Logger_.Log("Initialization [FINISH] Created Command Pool", 2);

    // Create Vertex Buffer
    Logger_.Log("Initialization [ START] Creating Vertex Buffer", 3);
    CreateVertexBuffer();
    Logger_.Log("Initialization [FINISH] Created Vertex Buffer", 2);

    // Create Vertex Buffer
    Logger_.Log("Initialization [ START] Creating Index Buffer", 3);
    CreateIndexBuffer();
    Logger_.Log("Initialization [FINISH] Created Index Buffer", 2);



    // Create Command Buffers
    Logger_.Log("Initialization [ START] Creating Command Buffers", 3);
    CreateCommandBuffers();
    Logger_.Log("Initialization [FINISH] Created Command Buffers", 2);


    // Create Semaphores
    Logger_.Log("Initialization [ START] Creating Semaphores", 3);
    CreateSyncObjects();
    Logger_.Log("Initialization [FINISH] Created Semaphores", 2);


}

// Define VisualRenderer::CreateIndexBuffer
void VisualRenderer::CreateIndexBuffer() {

    // Setup Structs
    VkDeviceSize BufferSize = sizeof(Indices_[0]) * Indices_.size();

    VkBuffer StagingBuffer;
    VkDeviceMemory StagingBufferMemory;

    // Setup Staging Buffer
    Logger_.Log("Setting Up Staging Buffer", 3);
    CreateBuffer(BufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, StagingBuffer, StagingBufferMemory);
    
    // Fill Staging Buffer
    void* Data;
    vkMapMemory(LogicalDevice_, StagingBufferMemory, 0, BufferSize, 0, &Data);
    memcpy(Data, Vertices_.data(), (size_t) BufferSize);
    vkUnmapMemory(LogicalDevice_, StagingBufferMemory);

    // Setup Vertex Buffer
    Logger_.Log("Setting Up Index Buffer", 3);
    CreateBuffer(BufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, IndexBuffer_, IndexBufferMemory_);


    // Copy Contents
    Logger_.Log("Copying Data Into Vertex Buffer", 3);
    CopyBuffer(StagingBuffer, IndexBuffer_, BufferSize);

    // Cleanup Staging Buffer
    Logger_.Log("Cleaning Staging Buffer", 3);
    vkDestroyBuffer(LogicalDevice_, StagingBuffer, nullptr);
    vkFreeMemory(LogicalDevice_, StagingBufferMemory, nullptr);


}

// Define VisualRenderer::CreateBuffer
void VisualRenderer::CreateBuffer(VkDeviceSize Size, VkBufferUsageFlags Usage, VkMemoryPropertyFlags Properties, VkBuffer& Buffer, VkDeviceMemory& BufferMemory) {

    // Setup Buffer
    VkBufferCreateInfo BufferInfo{};
    BufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    BufferInfo.size = Size;
    BufferInfo.usage = Usage;
    BufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if (vkCreateBuffer(LogicalDevice_, &BufferInfo, nullptr, &Buffer) != VK_SUCCESS) {
        Logger_.Log("Failed To Create Buffer", 10);
        *SystemShutdownInvoked_ = true;
    }

    // Get Memory Requirements
    VkMemoryRequirements MemoryRequirements;
    vkGetBufferMemoryRequirements(LogicalDevice_, Buffer, &MemoryRequirements);


    // Allocate Memory
    Logger_.Log("Allocating GPU VRAM To Buffer", 3);
    VkMemoryAllocateInfo AllocateInfo{};
    AllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    AllocateInfo.allocationSize = MemoryRequirements.size;
    AllocateInfo.memoryTypeIndex = FindMemoryType(MemoryRequirements.memoryTypeBits, Properties);

    if (vkAllocateMemory(LogicalDevice_, &AllocateInfo, nullptr, &BufferMemory) != VK_SUCCESS) {
        Logger_.Log("Failed To Allocate Buffer Memory", 10);
        *SystemShutdownInvoked_ = true;
    }

    // Bind To Memory
    vkBindBufferMemory(LogicalDevice_, Buffer, BufferMemory, 0);


}

// Define VisualRenderer::FindMemoryType
uint32_t VisualRenderer::FindMemoryType(uint32_t TypeFilter, VkMemoryPropertyFlags Properties) {

    // Get VRAM Properties
    Logger_.Log("Finding VRAM Properties", 3);
    VkPhysicalDeviceMemoryProperties MemoryProperties;
    vkGetPhysicalDeviceMemoryProperties(PhysicalDevice_, &MemoryProperties);

    // Iterate Through Memory Types
    for (uint32_t i=0; i<MemoryProperties.memoryTypeCount; i++) {
        if (TypeFilter & (1 << i) && (MemoryProperties.memoryTypes[i].propertyFlags & Properties) == Properties) {
            return i;
        }
    }

    // Failed
    Logger_.Log("Failed To Find Suitable Memory Type", 10);
    *SystemShutdownInvoked_ = true;
    return 0;

}

// Define VisualRenderer::CopyBuffer
void VisualRenderer::CopyBuffer(VkBuffer SourceBuffer, VkBuffer DestinationBuffer, VkDeviceSize Size) {

    // Create Copy Buffer
    Logger_.Log(std::string(std::string("Copying ") + std::to_string(Size) + std::string(" Bytes Between Buffers")).c_str(), 4);
    VkCommandBufferAllocateInfo AllocateInfo{};
    AllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    AllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    AllocateInfo.commandPool = CommandPool_;
    AllocateInfo.commandBufferCount = 1;

    VkCommandBuffer CommandBuffer;
    vkAllocateCommandBuffers(LogicalDevice_, &AllocateInfo, &CommandBuffer);

    // Copy Contents
    VkCommandBufferBeginInfo BeginInfo{};
    BeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    BeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    vkBeginCommandBuffer(CommandBuffer, &BeginInfo);

    VkBufferCopy CopyRegion{};
    CopyRegion.srcOffset = 0;
    CopyRegion.dstOffset = 0;
    CopyRegion.size = Size;
    vkCmdCopyBuffer(CommandBuffer, SourceBuffer, DestinationBuffer, 1, &CopyRegion);

    vkEndCommandBuffer(CommandBuffer);

    // Submit To Queue
    VkSubmitInfo SubmitInfo{};
    SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    SubmitInfo.commandBufferCount = 1;
    SubmitInfo.pCommandBuffers = &CommandBuffer;

    vkQueueSubmit(GraphicsQueue_, 1, &SubmitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(GraphicsQueue_);

    // Cleanup Command Buffer
    vkFreeCommandBuffers(LogicalDevice_, CommandPool_, 1, &CommandBuffer);

}

// Define VisualRenderer::CreateVertexBuffer
void VisualRenderer::CreateVertexBuffer() {

    // Setup Structs
    VkDeviceSize BufferSize = sizeof(Vertices_[0]) * Vertices_.size();

    VkBuffer StagingBuffer;
    VkDeviceMemory StagingBufferMemory;

    // Setup Staging Buffer
    Logger_.Log("Setting Up Staging Buffer", 3);
    CreateBuffer(BufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, StagingBuffer, StagingBufferMemory);
    
    // Fill Staging Buffer
    void* Data;
    vkMapMemory(LogicalDevice_, StagingBufferMemory, 0, BufferSize, 0, &Data);
    memcpy(Data, Vertices_.data(), (size_t) BufferSize);
    vkUnmapMemory(LogicalDevice_, StagingBufferMemory);

    // Setup Vertex Buffer
    Logger_.Log("Setting Up Vertex Buffer", 3);
    CreateBuffer(BufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, VertexBuffer_, VertexBufferMemory_);


    // Copy Contents
    Logger_.Log("Copying Data Into Vertex Buffer", 3);
    CopyBuffer(StagingBuffer, VertexBuffer_, BufferSize);

    // Cleanup Staging Buffer
    Logger_.Log("Cleaning Staging Buffer", 3);
    vkDestroyBuffer(LogicalDevice_, StagingBuffer, nullptr);
    vkFreeMemory(LogicalDevice_, StagingBufferMemory, nullptr);


}

// Define VisualRenderer::CreateSemaphores
void VisualRenderer::CreateSyncObjects() {

    // Create Semaphores
    ImageAvailableSemaphores_.resize(MaxFramesInFlight_);
    RenderFinishedSemaphores_.resize(MaxFramesInFlight_);
    InFlightFences_.resize(MaxFramesInFlight_);
    ImagesInFlight_.resize(MaxFramesInFlight_);

    // Set Current Frame
    CurrentFrame_ = 0;

    VkSemaphoreCreateInfo SemaphoreInfo{};
    SemaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo FenceInfo{};
    FenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    FenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for (size_t i=0; i<MaxFramesInFlight_; i++) {


        if (vkCreateSemaphore(LogicalDevice_, &SemaphoreInfo, nullptr, &ImageAvailableSemaphores_[i]) != VK_SUCCESS) {
            Logger_.Log("Failed To Create ImageAvailable Semaphore Snyc Object", 10);
            *SystemShutdownInvoked_ = true;
        }

        if (vkCreateSemaphore(LogicalDevice_, &SemaphoreInfo, nullptr, &RenderFinishedSemaphores_[i]) != VK_SUCCESS) {
            Logger_.Log("Failed To Create RenderFinished Semaphore Snyc Object", 10);
            *SystemShutdownInvoked_ = true;
        }

        if (vkCreateFence(LogicalDevice_, &FenceInfo, nullptr, &InFlightFences_[i]) != VK_SUCCESS) {
            Logger_.Log("Failed To Create InFlight Fence Snyc Object", 10);
            *SystemShutdownInvoked_ = true;
        }

    }

}

// Define VisualRenderer::CreateCommandBuffers
void VisualRenderer::CreateCommandBuffers() {

    // Set Command Buffer Size
    CommandBuffers_.resize(SwapChainFramebuffers_.size());

    // Setup Command Buffer
    VkCommandBufferAllocateInfo AllocInfo{};
    AllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    AllocInfo.commandPool = CommandPool_;
    AllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    AllocInfo.commandBufferCount = (uint32_t) CommandBuffers_.size();


    // Create Command Buffer
    if (vkAllocateCommandBuffers(LogicalDevice_, &AllocInfo, CommandBuffers_.data()) != VK_SUCCESS) {
        Logger_.Log("Failed To Create Command Buffer", 10);
        *SystemShutdownInvoked_ = true;
    }


    // Record Command Buffer
    for (size_t i = 0; i < CommandBuffers_.size(); i++) {
        VkCommandBufferBeginInfo BeginInfo{};
        BeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        BeginInfo.flags = 0;
        BeginInfo.pInheritanceInfo = nullptr;

        if (vkBeginCommandBuffer(CommandBuffers_[i], &BeginInfo) != VK_SUCCESS) {
            Logger_.Log("Failed To Begin Recording Command Buffer", 10);
            *SystemShutdownInvoked_ = true;
        }


        // Create Renderpass Begin Info
        VkRenderPassBeginInfo RenderPassInfo{};
        RenderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        RenderPassInfo.renderPass = RenderPass_;
        RenderPassInfo.framebuffer = SwapChainFramebuffers_[i];

        RenderPassInfo.renderArea.offset = {0, 0};
        RenderPassInfo.renderArea.extent = SwapChainExtent_; // COME BACK AND FIX THIS LATER FOR OFFSCREEN RENDERING!

        // Setup Clear Color
        VkClearValue ClearColor = {{0.0f, 0.0f, 0.0f, 1.0f}};
        RenderPassInfo.clearValueCount = 1;
        RenderPassInfo.pClearValues = &ClearColor;

        // Render Pass Definition
        vkCmdBeginRenderPass(CommandBuffers_[i], &RenderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
        vkCmdBindPipeline(CommandBuffers_[i], VK_PIPELINE_BIND_POINT_GRAPHICS, GraphicsPipeline_);

        VkBuffer VertexBuffers[] = {VertexBuffer_};
        VkDeviceSize Offsets[] = {0};
        vkCmdBindVertexBuffers(CommandBuffers_[i], 0, 1, VertexBuffers, Offsets);
        vkCmdBindIndexBuffer(CommandBuffers_[i], IndexBuffer_, 0, VK_INDEX_TYPE_UINT16);

        vkCmdDrawIndexed(CommandBuffers_[i], static_cast<uint32_t>(Indices_.size()), 1, 0, 0, 0);

        // vkCmdDraw(CommandBuffers_[i], static_cast<uint32_t>(Vertices_.size()), 1, 0, 0);
        vkCmdEndRenderPass(CommandBuffers_[i]);

        if (vkEndCommandBuffer(CommandBuffers_[i]) != VK_SUCCESS) {
            Logger_.Log("Failed To Record Command Buffer", 10);
            *SystemShutdownInvoked_ = true;
        }

    }

}

// Define VisualRenderer::CreateCommandPool
void VisualRenderer::CreateCommandPool() {

    // Find Queue Families
    QueueFamilyIndices QueueFamilyIndices = FindQueueFamilies(PhysicalDevice_, false);

    VkCommandPoolCreateInfo PoolInfo{};
    PoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    PoolInfo.queueFamilyIndex = QueueFamilyIndices.GraphicsFamily.value();
    PoolInfo.flags = 0;

    // Create Command Pool
    if (vkCreateCommandPool(LogicalDevice_, &PoolInfo, nullptr, &CommandPool_) != VK_SUCCESS) {
        Logger_.Log("Failed To Create Command Pool", 10);
        *SystemShutdownInvoked_ = true;
    }

}

// Define VisualRenderer::CreateFramebuffers
void VisualRenderer::CreateFramebuffers() {

    // Setup Framebuffer
    SwapChainFramebuffers_.resize(SwapChainImageViews_.size());

    // Iterate Through Image Views To Create Framebuffers
    for (size_t i=0; i < SwapChainImageViews_.size(); i++) {
        VkImageView Attachments[] = {
            SwapChainImageViews_[i]
        };

        VkFramebufferCreateInfo FrameBufferInfo{};
        FrameBufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        FrameBufferInfo.renderPass = RenderPass_;
        FrameBufferInfo.attachmentCount = 1;
        FrameBufferInfo.pAttachments = Attachments;
        FrameBufferInfo.width = SwapChainExtent_.width;
        FrameBufferInfo.height = SwapChainExtent_.height;
        FrameBufferInfo.layers = 1;

        if (vkCreateFramebuffer(LogicalDevice_, &FrameBufferInfo, nullptr, &SwapChainFramebuffers_[i]) != VK_SUCCESS) {
            Logger_.Log("Failed To Create Framebuffer", 10);
            *SystemShutdownInvoked_ = true;
        }
    
    
    }

}

// Define VisualRenderer::CreateRenderPass
void VisualRenderer::CreateRenderPass() {

    // Log Render Pass Setup
    Logger_.Log("Setting Up Render Passes", 3);

    // Create Color Attachment
    VkAttachmentDescription ColorAttachment{};
    ColorAttachment.format = SwapChainImageFormat_;
    ColorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    ColorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    ColorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    ColorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    ColorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    ColorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    ColorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    // Rendering Subpasses
    VkAttachmentReference ColorAttachmentRef{};
    ColorAttachmentRef.attachment = 0;
    ColorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription Subpass{};
    Subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    Subpass.colorAttachmentCount = 1;
    Subpass.pColorAttachments = &ColorAttachmentRef;

    // Subpass Dependencies
    VkSubpassDependency Dependency{};
    Dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    Dependency.dstSubpass = 0;

    Dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    Dependency.srcAccessMask = 0;

    Dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    Dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;


    // Create Render Pass
    VkRenderPassCreateInfo RenderPassInfo{};
    RenderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    RenderPassInfo.attachmentCount = 1;
    RenderPassInfo.pAttachments = &ColorAttachment;
    RenderPassInfo.subpassCount = 1;
    RenderPassInfo.pSubpasses = &Subpass;

    // Add Dependency To Renderpass
    RenderPassInfo.dependencyCount = 1;
    RenderPassInfo.pDependencies = &Dependency;

    if (vkCreateRenderPass(LogicalDevice_, &RenderPassInfo, nullptr, &RenderPass_) != VK_SUCCESS) {
        Logger_.Log("Failed To Create Render Pass", 10);
        *SystemShutdownInvoked_ = true;
    }



}

// Define VisualRenderer::CreateGraphicsPipeline
void VisualRenderer::CreateGraphicsPipeline() {
    
    // Load Shaders From File
    Logger_.Log("Loading Shaders From Disk", 3);
    auto VertexShaderCode = ReadFile("Shaders/SPIR-V/Vertex/main.spv", Logger_);
    auto FragmentShaderCode = ReadFile("Shaders/SPIR-V/Fragment/main.spv", Logger_);
    Logger_.Log("Finished Loading Shaders", 2);
    
    // Create Shader Modules
    Logger_.Log("Creating Shader Modules", 3);
    VkShaderModule VertexShaderModule = CreateShaderModule(VertexShaderCode);
    VkShaderModule FragmentShaderModule = CreateShaderModule(FragmentShaderCode);
    Logger_.Log("Created Shader Modules", 2);


    // Setup Vertex Shader Stages
    Logger_.Log("Creating Shader Stages", 3);
    VkPipelineShaderStageCreateInfo VertexShaderStageInfo{};
    VertexShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    VertexShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    VertexShaderStageInfo.module = VertexShaderModule;
    VertexShaderStageInfo.pName = "main";

    // Setup Fragment Shader Stages
    VkPipelineShaderStageCreateInfo FragmentShaderStageInfo{};
    FragmentShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    FragmentShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    FragmentShaderStageInfo.module = FragmentShaderModule;
    FragmentShaderStageInfo.pName = "main";

    // Create Array To Hold Shader Stages
    VkPipelineShaderStageCreateInfo ShaderStages[] = {
        VertexShaderStageInfo,
        FragmentShaderStageInfo
    };

    Logger_.Log("Created Shader Stages", 2);

    
    // Setup Vertex Input
    Logger_.Log("Setting Up Vertex Input", 3);
    auto BindingDescription = Vertex::GetBindingDescription();
    auto AttributeDescriptions = Vertex::GetAttributeDescriptions();

    // Set Fixed Functions
    Logger_.Log("Creating Fixed Functions", 3);
    VkPipelineVertexInputStateCreateInfo VertexInputInfo{};
    VertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    VertexInputInfo.vertexBindingDescriptionCount = 1;
    VertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(AttributeDescriptions.size());
    VertexInputInfo.pVertexBindingDescriptions = &BindingDescription;
    VertexInputInfo.pVertexAttributeDescriptions = AttributeDescriptions.data();

    VkPipelineInputAssemblyStateCreateInfo InputAssembly{};
    InputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    InputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    InputAssembly.primitiveRestartEnable = VK_FALSE;


    // Setup Viewport
    Logger_.Log("Setting Up Viewport", 3);
    VkViewport Viewport{};
    Viewport.x = 0.0f;
    Viewport.y = 0.0f;

    if (LocalWindowEnabled_) {
        Viewport.width = (float) SwapChainExtent_.width; // ADJUST THESE LATER !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        Viewport.height = (float) SwapChainExtent_.height;
    } else {
        Viewport.width = (float) SystemConfiguration_["RenderWidthPixels"].as<int>();
        Viewport.height = (float) SystemConfiguration_["RenderHeightPixels"].as<int>();
        
    }
    
    Viewport.minDepth = 0.0f;
    Viewport.maxDepth = 1.0f; 


    // Setup Scissor Rectangle
    VkRect2D Scissor{};
    Scissor.offset = {0, 0};
    Scissor.extent = SwapChainExtent_; // FILL THIS In LATER !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    // Setup Viewport State
    VkPipelineViewportStateCreateInfo ViewportState{};
    ViewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    ViewportState.viewportCount = 1;
    ViewportState.pViewports = &Viewport;
    ViewportState.scissorCount = 1;
    ViewportState.pScissors = &Scissor;


    // Setup Rasterizer
    Logger_.Log("Setting Up Rasterizer", 3);
    VkPipelineRasterizationStateCreateInfo Rasterizer{};
    Rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    Rasterizer.depthClampEnable = VK_FALSE;
    Rasterizer.rasterizerDiscardEnable = VK_FALSE;
    Rasterizer.polygonMode = VK_POLYGON_MODE_FILL; // Can set this to VK_POLYGON_MODE_ FILL, LINE, POINT (any other than fill require gpu feature to be enabled)
    Rasterizer.lineWidth = 1.0f; // can set this to larger, but requires the "wideLines" gpu feature
    Rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    Rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
    
    Rasterizer.depthBiasEnable = VK_FALSE;
    Rasterizer.depthBiasConstantFactor = 0.0f;
    Rasterizer.depthBiasClamp = 0.0f;
    Rasterizer.depthBiasSlopeFactor = 0.0f;

    // Setup Multisampling
    Logger_.Log("Setting Up Multisampling", 3);
    VkPipelineMultisampleStateCreateInfo Multisampling{};
    Multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    Multisampling.sampleShadingEnable = VK_FALSE;
    Multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
    Multisampling.minSampleShading = 1.0f;
    Multisampling.pSampleMask = nullptr;
    Multisampling.alphaToCoverageEnable = VK_FALSE;
    Multisampling.alphaToOneEnable = VK_FALSE;

    // Setup Color Blending
    Logger_.Log("Setting Up Color Blending", 3);
    VkPipelineColorBlendAttachmentState ColorBlendAttachment{};
    ColorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    ColorBlendAttachment.blendEnable = VK_TRUE;  // set to false in tutorial
    ColorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
    ColorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
    ColorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
    ColorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    ColorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    ColorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

    VkPipelineColorBlendStateCreateInfo ColorBlending{};
    ColorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    ColorBlending.logicOpEnable = VK_FALSE;
    ColorBlending.logicOp = VK_LOGIC_OP_COPY;
    ColorBlending.attachmentCount = 1;
    ColorBlending.pAttachments = &ColorBlendAttachment;
    ColorBlending.blendConstants[0] = 0.0f;
    ColorBlending.blendConstants[1] = 0.0f;
    ColorBlending.blendConstants[2] = 0.0f;
    ColorBlending.blendConstants[3] = 0.0f;

    // Setup Dynamic State (NOTE, THESE WILL NEED TO BE SET LATER.... WHEN DRAWING!)
    VkDynamicState DynamicStates[] = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_LINE_WIDTH
    };

    VkPipelineDynamicStateCreateInfo DynamicState{};
    DynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    DynamicState.dynamicStateCount = 2;
    DynamicState.pDynamicStates = DynamicStates;


    // Pipeline Layout
    Logger_.Log("Setting Up Pipeline", 3);

    VkPipelineLayoutCreateInfo PipelineLayoutInfo{};
    PipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    PipelineLayoutInfo.setLayoutCount = 0;
    PipelineLayoutInfo.pSetLayouts = nullptr;
    PipelineLayoutInfo.pushConstantRangeCount = 0;
    PipelineLayoutInfo.pPushConstantRanges = nullptr;

    if (vkCreatePipelineLayout(LogicalDevice_, &PipelineLayoutInfo, nullptr, &PipelineLayout_) != VK_SUCCESS) {
        Logger_.Log("Failed To Create Pipeline Layout", 10);
        *SystemShutdownInvoked_ = true;
    }


    // Create Pipeline Object
    Logger_.Log("Creating Graphics Pipeline Object", 3);
    VkGraphicsPipelineCreateInfo PipelineInfo{};
    PipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    PipelineInfo.stageCount = 2;
    PipelineInfo.pStages = ShaderStages;

    PipelineInfo.pVertexInputState = &VertexInputInfo;
    PipelineInfo.pInputAssemblyState = &InputAssembly;
    PipelineInfo.pViewportState = &ViewportState;
    PipelineInfo.pRasterizationState = &Rasterizer;
    PipelineInfo.pMultisampleState = &Multisampling;
    PipelineInfo.pDepthStencilState = nullptr; // Optional
    PipelineInfo.pColorBlendState = &ColorBlending;
    PipelineInfo.pDynamicState = nullptr; // Optional


    PipelineInfo.layout = PipelineLayout_;
    PipelineInfo.renderPass = RenderPass_;
    PipelineInfo.subpass = 0;

    PipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
    PipelineInfo.basePipelineIndex = -1;


    if (vkCreateGraphicsPipelines(LogicalDevice_, VK_NULL_HANDLE, 1, &PipelineInfo, nullptr, &GraphicsPipeline_) != VK_SUCCESS) {
        Logger_.Log("Failed To Create Graphics Pipeline", 10);
        *SystemShutdownInvoked_ = true;
    }

    // Cleanup Shader Modules
    vkDestroyShaderModule(LogicalDevice_, FragmentShaderModule, nullptr);
    vkDestroyShaderModule(LogicalDevice_, VertexShaderModule, nullptr);


}

// Define VisualRenderer::CreateShaderModule
VkShaderModule VisualRenderer::CreateShaderModule(const std::vector<char>& Code) {

    // Configure Shader Module
    VkShaderModuleCreateInfo CreateInfo{};

    CreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    CreateInfo.codeSize = Code.size();
    CreateInfo.pCode = reinterpret_cast<const uint32_t*>(Code.data());

    // Create Shader
    VkShaderModule ShaderModule;
    if (vkCreateShaderModule(LogicalDevice_, &CreateInfo, nullptr, &ShaderModule) != VK_SUCCESS) {
        Logger_.Log("Failed To Create Shader Module Instance", 10);
        *SystemShutdownInvoked_ = true;
    }

    // Return Shader Module
    return ShaderModule;

}

// Define VisualRenderer::CreateImageViews
void VisualRenderer::CreateImageViews() {

    // Create Image View
    SwapChainImageViews_.resize(SwapChainImages_.size());

    // Iterate Through Image Views
    for (size_t i = 0; i < SwapChainImages_.size(); i++) {

        // Populate ImageViewCreateInfo Struct
        VkImageViewCreateInfo CreateInfo{};

        CreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        CreateInfo.image = SwapChainImages_[i];
        CreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        CreateInfo.format = SwapChainImageFormat_;

        CreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
        CreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
        CreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
        CreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

        CreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        CreateInfo.subresourceRange.baseMipLevel = 0;
        CreateInfo.subresourceRange.levelCount = 1;
        CreateInfo.subresourceRange.baseArrayLayer = 0;
        CreateInfo.subresourceRange.layerCount = 1; // For stereoscopic 3d application, make more layers

        // Create Image View
        if (vkCreateImageView(LogicalDevice_, &CreateInfo, nullptr, &SwapChainImageViews_[i]) != VK_SUCCESS) {
            Logger_.Log("Failed To Create Image Views", 10);
            *SystemShutdownInvoked_ = true;
        }


    }

}

// Define VisualRenderer::CreateSwapChain
void VisualRenderer::CreateSwapChain() {

    // Get Swapchain Support Info
    Logger_.Log("INIT [ START] Querying Swap Chain Support Information", 3);
    SwapChainSupportDetails SwapChainSupport = QuerySwapChainSupport(PhysicalDevice_, false);
    Logger_.Log("INIT [FINISH] Fetched Swap Chain Support Information", 2);

    // Setup Swap Chain
    Logger_.Log("INIT [ START] Setting Up Swap Chain Surface Formats", 3);
    VkSurfaceFormatKHR SurfaceFormat = ChooseSwapChainSurfaceFormat(SwapChainSupport.Formats);
    Logger_.Log("INIT [FINISH] Set Up Swap Chain Surface Formats", 2);

    Logger_.Log("INIT [ START] Setting Up Swap Chain Present Modes", 3);
    VkPresentModeKHR PresentMode = ChooseSwapPresentMode(SwapChainSupport.PresentModes);
    Logger_.Log("INIT [FINISH] Setting Up Swap Chain Present Modes", 2);
    
    Logger_.Log("INIT [ START] Setting Up Swap Chain Extent Capabilities", 3);
    VkExtent2D Extent = ChooseSwapExtent(SwapChainSupport.Capabilities);
    Logger_.Log("INIT [FINISH] Setting Up Swap Chain Extent Capabilities", 2);


    // Set Number Of Images In SwapChain
    Logger_.Log("INIT [ START] Setting Up Swap Chain Image Count", 3);
    uint32_t ImageCount = SwapChainSupport.Capabilities.minImageCount + 1;
    
    if (SwapChainSupport.Capabilities.maxImageCount > 0 && ImageCount > SwapChainSupport.Capabilities.maxImageCount) {
        ImageCount = SwapChainSupport.Capabilities.maxImageCount;
    }

    Logger_.Log(std::string(std::string("INIT [FINISH] Set Swap Chain Image Count To: ") + std::to_string(ImageCount)).c_str(), 2);


    // Configure Swap Chain
    Logger_.Log("INIT [ START] Populating Swap Chain CreateInfo Struct", 3);
    VkSwapchainCreateInfoKHR CreateInfo{};

    CreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    CreateInfo.surface = sERSLocalWindowDisplaySystem_.Surface_;

    CreateInfo.minImageCount = ImageCount;
    CreateInfo.imageFormat = SurfaceFormat.format;
    CreateInfo.imageColorSpace = SurfaceFormat.colorSpace;
    CreateInfo.imageExtent = Extent;
    CreateInfo.imageArrayLayers = 1;
    CreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamilyIndices Indices = FindQueueFamilies(PhysicalDevice_, false);
    uint32_t QueueFamilyIndices[] = {Indices.GraphicsFamily.value(), Indices.PresentFamily.value()};

    if (Indices.GraphicsFamily != Indices.PresentFamily) {
        CreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        CreateInfo.queueFamilyIndexCount = 2;
        CreateInfo.pQueueFamilyIndices = QueueFamilyIndices;
    } else {
        CreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        CreateInfo.queueFamilyIndexCount = 0;
        CreateInfo.pQueueFamilyIndices = nullptr;

    }

    CreateInfo.preTransform = SwapChainSupport.Capabilities.currentTransform;
    CreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    CreateInfo.presentMode = PresentMode;
    CreateInfo.clipped = VK_TRUE;

    CreateInfo.oldSwapchain = VK_NULL_HANDLE;

    Logger_.Log("INIT [FINISH] Populated Swap Chain CreateInfo Struct", 2);


    // Create Swap Chain
    Logger_.Log("INIT [ START] Creating Swap Chain Object", 3);
    if (vkCreateSwapchainKHR(LogicalDevice_, &CreateInfo, nullptr, &SwapChain_) != VK_SUCCESS) {
        Logger_.Log("INIT [ERROR] Failed To Create Swap Chain", 10);
        *SystemShutdownInvoked_ = true;
    }
    Logger_.Log("INIT [FINISH] Created Swap Chain Object", 2);


    // Assign To Member Variables
    Logger_.Log("INIT [ START] Assigning Swapchain Info To Member Variables", 3);
    vkGetSwapchainImagesKHR(LogicalDevice_, SwapChain_, &ImageCount, nullptr);
    SwapChainImages_.resize(ImageCount);
    vkGetSwapchainImagesKHR(LogicalDevice_, SwapChain_, &ImageCount, SwapChainImages_.data());

    SwapChainImageFormat_ = SurfaceFormat.format;
    SwapChainExtent_ = Extent;
    Logger_.Log("INIT [ START] Assigned Swapchain Info To Member Variables", 2);


}

// Define VisualRenderer::SwapchainPresentMode
VkPresentModeKHR VisualRenderer::ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& AvailablePresentModes) {

    // Iterate Through Presentation Modes
    for (const auto& AvailablePresentMode : AvailablePresentModes) {
        if (AvailablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
            return AvailablePresentMode;
        }
    }
    
    // Fallback Mode
    return VK_PRESENT_MODE_FIFO_KHR;

}

// Define VisualRenderer::Swap Extent
VkExtent2D VisualRenderer::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& Capabilities) {

    // Get Framebuffer MaxSize Requirements
    if (Capabilities.currentExtent.width != UINT32_MAX) {
        return Capabilities.currentExtent;
    } else {
            int Width, Height;
            glfwGetFramebufferSize(sERSLocalWindowDisplaySystem_.Window_, &sERSLocalWindowDisplaySystem_.WindowX_, &sERSLocalWindowDisplaySystem_.WindowY_);

            VkExtent2D ActualExtent = {
                static_cast<uint32_t>(sERSLocalWindowDisplaySystem_.WindowX_),
                static_cast<uint32_t>(sERSLocalWindowDisplaySystem_.WindowY_)
            };

            ActualExtent.width = std::clamp(ActualExtent.width, Capabilities.minImageExtent.width, Capabilities.maxImageExtent.width);
            ActualExtent.height = std::clamp(ActualExtent.height, Capabilities.minImageExtent.height, Capabilities.maxImageExtent.height);

            return ActualExtent;
    }    

}

// Define VisualRenderer::ChooseSwapChainSurfaceFormat
VkSurfaceFormatKHR VisualRenderer::ChooseSwapChainSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& AvailableFormats) {

    // Iterate Through Formats
    for (const auto& AvailableFormat : AvailableFormats) {

        // Check Format
        if (AvailableFormat.format == VK_FORMAT_B8G8R8A8_SRGB && AvailableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {

            return AvailableFormat;

        }


    }

    // If Target Format Not Available, Use Whatever Is
    return AvailableFormats[0];


}

// Define VisualRenderer::QuerySwapChainSupport
SwapChainSupportDetails VisualRenderer::QuerySwapChainSupport(VkPhysicalDevice Device, bool IndentLogs) {

    // Get Swap Chain Support Information
    if (IndentLogs) {
        Logger_.Log("        Querying Number Of Swap Chain Formats", 3);
    } else {
        Logger_.Log("Querying Number Of Swap Chain Formats", 3);
    }
    SwapChainSupportDetails Details;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(Device, sERSLocalWindowDisplaySystem_.Surface_, &Details.Capabilities);

    // Get Number Of Formats
    uint32_t FormatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(Device, sERSLocalWindowDisplaySystem_.Surface_, &FormatCount, nullptr);


    if (FormatCount != 0) {
        Details.Formats.resize(FormatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(Device, sERSLocalWindowDisplaySystem_.Surface_, &FormatCount, Details.Formats.data());
    }

    // Log Formats
    if (IndentLogs) {
        Logger_.Log(std::string(std::string("        Found ") + std::to_string(FormatCount) + std::string(" Formats")).c_str(), 2);
    } else {
        Logger_.Log(std::string(std::string("Found ") + std::to_string(FormatCount) + std::string(" Formats")).c_str(), 2);
    }


    // Get Number Of Present Modes
    if (IndentLogs) {
        Logger_.Log("        Querying Number Of Presentation Modes", 3);
    } else {
        Logger_.Log("Querying Number Of Presentation Modes", 3);
    }
    uint32_t PresentModeCount;
    vkGetPhysicalDeviceSurfacePresentModesKHR(Device, sERSLocalWindowDisplaySystem_.Surface_, &PresentModeCount, nullptr);

    if (PresentModeCount != 0) {
        Details.PresentModes.resize(PresentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(Device, sERSLocalWindowDisplaySystem_.Surface_, &PresentModeCount, Details.PresentModes.data());
    }

    // Log Number Of Presentation Modes
    if (IndentLogs) {
        Logger_.Log(std::string(std::string("        Found ") + std::to_string(PresentModeCount) + std::string(" Modes")).c_str(), 2);
    } else {
        Logger_.Log(std::string(std::string("Found ") + std::to_string(PresentModeCount) + std::string(" Modes")).c_str(), 2);
    }


    // Return Results
    return Details;

}

// Define VisualRenderer::CheckDeviceExtensionSupport
bool VisualRenderer::CheckDeviceExtensionSupport(VkPhysicalDevice Device, bool IndentLogs) {

    // Check Extensions
    if (IndentLogs) {
        Logger_.Log("        Querying Number Of Device Extensions", 3);
    } else {
        Logger_.Log("Querying Number Of Device Extensions", 3);
    }
    uint32_t ExtensionCount;
    vkEnumerateDeviceExtensionProperties(Device, nullptr, &ExtensionCount, nullptr);

    std::vector<VkExtensionProperties> AvailableExtensions(ExtensionCount);
    vkEnumerateDeviceExtensionProperties(Device, nullptr, &ExtensionCount, AvailableExtensions.data());

    std::set<std::string> RequiredExtensions(DeviceExtensions_.begin(), DeviceExtensions_.end());

    for (const auto& Extension : AvailableExtensions) {

        RequiredExtensions.erase(Extension.extensionName);

    }


    // Return Data
    if (IndentLogs) {
        Logger_.Log(std::string(std::string("        Found ") + std::to_string(ExtensionCount) + std::string(" Extensions")).c_str(), 2);
    } else {
       Logger_.Log(std::string(std::string("Found ") + std::to_string(ExtensionCount) + std::string(" Extensions")).c_str(), 2);
    }

    return RequiredExtensions.empty();


}

// Define VisualRenderer::CreateLogicalDevice
void VisualRenderer::CreateLogicalDevice() {

    // Create Logical Device
    Logger_.Log("Getting Queue Families For Selected Device", 3);
    QueueFamilyIndices Indices = FindQueueFamilies(PhysicalDevice_, false);

    // Setup Creation Process
    Logger_.Log("Configuring 'VkDeviceQueueCreateInfo' Struct", 3);
    

    VkDeviceQueueCreateInfo QueueCreateInfo{};
    std::vector<VkDeviceQueueCreateInfo> QueueCreateInfos;

    if (LocalWindowEnabled_) {

        
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


    } else {
    
        QueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        QueueCreateInfo.queueFamilyIndex = Indices.GraphicsFamily.value();
        QueueCreateInfo.queueCount = 1;

        // Set Queue Priority
        float QueuePriority = 1.0f;
        QueueCreateInfo.pQueuePriorities = &QueuePriority;
    
    }



    // Set Device Features
    Logger_.Log("Setting Required Device Features", 2);
    VkPhysicalDeviceFeatures DeviceFeatures{};

    // Configure Logical Device
    Logger_.Log("Configuring 'VkDeviceCreateInfo' Struct", 5);
    VkDeviceCreateInfo CreateInfo{};
    CreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

    if (LocalWindowEnabled_) {
        CreateInfo.queueCreateInfoCount = static_cast<uint32_t>(QueueCreateInfos.size());
        CreateInfo.pQueueCreateInfos = QueueCreateInfos.data();

        CreateInfo.enabledExtensionCount = static_cast<uint32_t>(DeviceExtensions_.size());
        CreateInfo.ppEnabledExtensionNames = DeviceExtensions_.data();
    } else {
        CreateInfo.pQueueCreateInfos = &QueueCreateInfo;
        CreateInfo.queueCreateInfoCount = 1;
        CreateInfo.enabledExtensionCount = 0;
    }
    
    CreateInfo.pEnabledFeatures = &DeviceFeatures;


    if (ValidationLayersToBeUsed_) {
        CreateInfo.enabledLayerCount = static_cast<uint32_t>(ValidationLayers_.size());
        CreateInfo.ppEnabledLayerNames = ValidationLayers_.data();
    } else {
        CreateInfo.enabledLayerCount = 0;
    }




    // Creating Logical Device
    Logger_.Log("Creating Logical Device Instance", 3);
    if (vkCreateDevice(PhysicalDevice_, &CreateInfo, nullptr, &LogicalDevice_) != VK_SUCCESS) {

        // Logical Device Creation Failure
        Logger_.Log("Failed To Create Logical Device, System Shutting Down", 10);
        *SystemShutdownInvoked_ = true;
    }

    // Setup Graphics Queue
    Logger_.Log("INIT [ START] Setting Up Graphics Queue", 3);
    vkGetDeviceQueue(LogicalDevice_, Indices.GraphicsFamily.value(), 0, &GraphicsQueue_);
    Logger_.Log("INIT [FINISH] Set Up Graphics Queue", 2);

    // Setup Presentation Queue
    if (LocalWindowEnabled_) {
        Logger_.Log("INIT [ START] Creating Presentation Queue", 3);
        vkGetDeviceQueue(LogicalDevice_, Indices.PresentFamily.value(), 0, &PresentationQueue_);
        Logger_.Log("INIT [FINISH] Created Presentation Queue", 2);
    } else {
        Logger_.Log("INIT [  SKIP] [Configuration: 'DISABLE'] Skipping Presentation Queue Creation", 4);
    }
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
        *SystemShutdownInvoked_ = true;
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

    // Check If Device Supports The Needed Extensions
    bool DeviceSupportsExtensions = CheckDeviceExtensionSupport(Device);
    if (!DeviceSupportsExtensions) {
        return 0;
    }

    // Check If Device Has Needed Swap Chain Features
    bool SwapChainAdequate = false;
    if (DeviceSupportsExtensions && LocalWindowEnabled_) {
        SwapChainSupportDetails SwapChainSupport = QuerySwapChainSupport(Device);
        SwapChainAdequate = !SwapChainSupport.Formats.empty() && !SwapChainSupport.PresentModes.empty();
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
        *SystemShutdownInvoked_ = true;
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

// Define VisualRenderer::CleanupSwapChain
void VisualRenderer::CleanupSwapChain() {

    // Cleanup Framebuffers
    for (auto Framebuffer : SwapChainFramebuffers_) {
        vkDestroyFramebuffer(LogicalDevice_, Framebuffer, nullptr);

    }

    // Clean Commandbuffers
    vkFreeCommandBuffers(LogicalDevice_, CommandPool_, static_cast<uint32_t>(CommandBuffers_.size()), CommandBuffers_.data());

    // Destroy Pipeline
    vkDestroyPipeline(LogicalDevice_, GraphicsPipeline_, nullptr);
    vkDestroyPipelineLayout(LogicalDevice_, PipelineLayout_, nullptr);
    vkDestroyRenderPass(LogicalDevice_, RenderPass_, nullptr);

    // Cleanup Image Views
    for (auto ImageView : SwapChainImageViews_) {
        vkDestroyImageView(LogicalDevice_, ImageView, nullptr);
    }

    // Destroy Swapchain
    vkDestroySwapchainKHR(LogicalDevice_, SwapChain_, nullptr);

}

// Define VisualRenderer::RecreateSwapChain
void VisualRenderer::RecreateSwapChain() {

    // Wait For Device To Finish Operations
    vkDeviceWaitIdle(LogicalDevice_);


    // Cleanup Old Swapchain
    CleanupSwapChain();

    // Recreate Swapchain
    CreateSwapChain();
    CreateImageViews();
    CreateRenderPass();
    CreateGraphicsPipeline();
    CreateFramebuffers();
    CreateCommandBuffers();

    // Resize Frames To Correct Size
    ImagesInFlight_.resize(SwapChainImages_.size(), VK_NULL_HANDLE);


}

// Define VisualRenderer::RenderLoop
void VisualRenderer::RenderLoop() {

    // GLFW Poll Events
    sERSLocalWindowDisplaySystem_.FetchEvents();


    // Draw The Frame
    DrawFrame();



}

// Define VisualRenderer::DrawFrame
void VisualRenderer::DrawFrame() {

    // Wait For Fence
    vkWaitForFences(LogicalDevice_, 1, &InFlightFences_[CurrentFrame_], VK_TRUE, UINT64_MAX);

    // Acquire Image From Swap Chain
    uint32_t ImageIndex;
    VkResult Result = vkAcquireNextImageKHR(LogicalDevice_, SwapChain_, UINT64_MAX, ImageAvailableSemaphores_[CurrentFrame_], VK_NULL_HANDLE, &ImageIndex);

    // Check If SwapChain Is Out Of Date
    if (Result == VK_ERROR_OUT_OF_DATE_KHR || Result == VK_SUBOPTIMAL_KHR) {
        *FramebufferResized_ = true;
        RecreateSwapChain();
        return;
    } else if (Result != VK_SUCCESS) {
        Logger_.Log("Failed To Recreate SwapChain", 10);
        *SystemShutdownInvoked_ = true;
    }

    // Check Fences
    if (ImagesInFlight_[ImageIndex] != VK_NULL_HANDLE) {
        vkWaitForFences(LogicalDevice_, 1, &ImagesInFlight_[ImageIndex], VK_TRUE, UINT64_MAX);
    }
    ImagesInFlight_[ImageIndex] = InFlightFences_[CurrentFrame_];

    // Get Semaphores
    VkSemaphore WaitSemaphores[] = {ImageAvailableSemaphores_[CurrentFrame_]};
    VkSemaphore SignalSemaphores[] = {RenderFinishedSemaphores_[CurrentFrame_]};

    // Submit To Command Buffer
    VkSubmitInfo SubmitInfo{};
    SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    
    VkPipelineStageFlags WaitStates[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    SubmitInfo.waitSemaphoreCount = 1;
    SubmitInfo.pWaitSemaphores = WaitSemaphores;
    SubmitInfo.pWaitDstStageMask = WaitStates;

    SubmitInfo.commandBufferCount = 1;
    SubmitInfo.pCommandBuffers = &CommandBuffers_[ImageIndex];

    SubmitInfo.signalSemaphoreCount = 1;
    SubmitInfo.pSignalSemaphores = SignalSemaphores;

    // Reset Fence
    vkResetFences(LogicalDevice_, 1, &InFlightFences_[CurrentFrame_]);

    // Submit To Queue
    if (vkQueueSubmit(GraphicsQueue_, 1, &SubmitInfo, InFlightFences_[CurrentFrame_]) != VK_SUCCESS) {
        Logger_.Log("Failed To Submit Draw Command Buffer", 10);
        *SystemShutdownInvoked_ = true;
    }


    // Presentation
    VkPresentInfoKHR PresentInfo{};
    PresentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    PresentInfo.waitSemaphoreCount = 1;
    PresentInfo.pWaitSemaphores = SignalSemaphores;

    VkSwapchainKHR SwapChains[] = {SwapChain_};
    PresentInfo.swapchainCount = 1;
    PresentInfo.pSwapchains = SwapChains;
    PresentInfo.pImageIndices = &ImageIndex;

    PresentInfo.pResults = nullptr;


    // Update Current Frame
    CurrentFrame_ = (CurrentFrame_ + 1) % MaxFramesInFlight_;

    // Present
    vkQueuePresentKHR(PresentationQueue_, &PresentInfo);
    vkQueueWaitIdle(PresentationQueue_);

}

// Define VisualRenderer::CleanUp
void VisualRenderer::CleanUp() {

    // Log Shutdown Called
    Logger_.Log("Shutting Down 'Core::Renderer::Visual::VisualRenderer'", 5);

    // Cleanup Swapchain
    vkDeviceWaitIdle(LogicalDevice_);
    CleanupSwapChain();

    // Free VRAM
    vkDestroyBuffer(LogicalDevice_, VertexBuffer_, nullptr);
    vkFreeMemory(LogicalDevice_, VertexBufferMemory_, nullptr);
    vkDestroyBuffer(LogicalDevice_, IndexBuffer_, nullptr);
    vkFreeMemory(LogicalDevice_, IndexBufferMemory_, nullptr);
    

    // Cleanup Semaphores
    for (size_t i=0; i < MaxFramesInFlight_; i++ ) {
        vkDestroySemaphore(LogicalDevice_, RenderFinishedSemaphores_[i], nullptr);
        vkDestroySemaphore(LogicalDevice_, ImageAvailableSemaphores_[i], nullptr);
        vkDestroyFence(LogicalDevice_, InFlightFences_[i], nullptr);
    }

    // Destroy Command Pool
    vkDestroyCommandPool(LogicalDevice_, CommandPool_, nullptr);

    // Destroy LogicalDevice
    vkDestroyDevice(LogicalDevice_, nullptr);

    // Call Subclass's Destructors
    sERSLocalWindowDisplaySystem_.CleanUp();

    // Destroy Vulkan Instance
    vkDestroyInstance(VulkanInstance_, nullptr);

}