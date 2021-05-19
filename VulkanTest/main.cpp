#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

// Set Window Resolution //
const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 800;

// Set Error Catching Layers (I think) //
const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = true;
#endif

// Checks If Error Catching (Layer Validation) Is There //
bool checkValidationLayerSupport() {

    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLAyers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    return false;
}


class HelloTriangleApplication {
public:
    void run() {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

private:
    GLFWwindow* window;
    VkInstance instance;

    void initWindow() {
        glfwInit();

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        window = glfwCreateWindow(WIDTH, HEIGHT, "Test", nullptr, nullptr);
    }

    void initVulkan() {
        createInstance();


    }

    void createInstance() {
        // Set Application Information //
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "BrainGenix ERS";
        appInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);
        appInfo.pEngineName = "BrainGenix ERS";
        appInfo.engineVersion = VK_MAKE_VERSION(1,0,0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        // IDFK WTF This Does //
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        // Set Extensions? Also IDFK What This Does //
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions;

        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;

        // Layers ? IDFK //
        createInfo.enabledLayerCount = 0;

        // Instantiate Vulkan //
        if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
            throw std::runtime_error("Failed To Create Vulkan Instance!");
        }



    
    }


    void mainLoop() {

        while (!glfwWindowShouldClose(window)) {
            glfwPollEvents();
        }

    }

    void cleanup() {

        // Clean Up Vulkan //
        vkDestroyInstance(instance, nullptr);

        // Clean Up Windows //
        glfwDestroyWindow(window);
        glfwTerminate();

    }
};

int main() {
    HelloTriangleApplication app;

    try {
        app.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}