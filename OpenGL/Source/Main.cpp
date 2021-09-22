//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the main file of the system.
    Additonal Notes: None
    Date Created: 2021-09-21
*/

#include <iostream>

#include "Include/glad/glad.h"
#include "Include/KHR/khrplatform.h"
#include "Core/Initialization/GLADModule/glad.c"

#include <GLFW/glfw3.h>
#include <yaml-cpp/yaml.h>

#include "Core/Management/Logger/LoggerModule.cpp"
#include "Core/Initialization/ConfigurationLoader/ConfigurationLoaderModule.cpp"
#include "Core/Initialization/WindowLibrary/WindowLibraryModule.cpp"
#include "Core/Initialization/GLADModule/GLADModule.cpp"


void FrameBufferResizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

}

int main() {
    
    // Loading Configuration File //
    const YAML::Node SystemConfiguration = LoadConfig("Config.yaml");

    // Instantiate Logging Subsystem //
    LoggerClass sERSLogger;
    sERSLogger.InitializeLogger(SystemConfiguration);

    // Log Initialization //
    sERSLogger.Log("Initialized Logger Subsystem", 5);

    // Create GLFW Window Based On Config //
    GLFWWindow WindowManager;
    GLFWwindow* Window = WindowManager.InitializeGLFW(SystemConfiguration, sERSLogger);

    // Run GLAD Function Pointer Loader //
    GLADInitialization(sERSLogger);

    // Set GLViewPort //
    WindowManager.InitializeGLViewport(SystemConfiguration, sERSLogger);


    // Create GLFW Resize Callback //
    sERSLogger.Log("Checking If Window Resize Events Enabled", 1);
    if ((WindowManager.AllowRenderResize) && (Window != nullptr)) {

        sERSLogger.Log("Setting Window Resize Callback Function", 3);
        glfwSetFramebufferSizeCallback(Window, FrameBufferResizeCallback);

    }


    // Create System Shutdown Variable //
    bool SystemShutdownInvoked = false;

    // Main Render Loop //
    while(!SystemShutdownInvoked)
    {

        // If The GLFW Window Exists //
        if (Window != nullptr) {

            // Check For Shutdown Events //
            SystemShutdownInvoked = glfwWindowShouldClose(Window);


            // GLFW Window Update //
            glfwSwapBuffers(Window);
            glfwPollEvents(); 

        }

   
    }

    // If GLFW Is In Use, Shut It Down //
    if (Window != nullptr) {
        // Shut Down GLFW //
        sERSLogger.Log("Shutting Down GLFW", 5);
        sERSLogger.Log("Destroying Window", 4);
        glfwTerminate();
    }

    // Exit System //
    sERSLogger.Log("System Shutdown", 3);
    return 0;
}




  