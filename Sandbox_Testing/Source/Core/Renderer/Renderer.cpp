//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the openGL Renderer.
    Additonal Notes: None
    Date Created: 2021-11-01
*/

#include <glad/glad.h>
#include <glad.c>

#include <GLFW/glfw3.h>

#include "Core/Renderer/Renderer.h"


void Renderer::InitializeRenderer(YAML::Node *SystemConfiguration, LoggerClass *Logger) {

    // Create Pointers
    Logger->Log("Populating Renderer Member Pointers", 5);
    SystemConfiguration_ = SystemConfiguration;
    Logger_ = Logger;

    // Initialize GLFW
    Logger_->Log("Initializing GLFW", 5);
    InitializeGLFW();

    Logger_->Log("Initializing OpenGL", 5);
    InitializeOpenGL();

}

void Renderer::InitializeGLFW() {

    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Read Out Width, Height
    Logger_->Log("Read Configuration File For 'WindowWidth' Parameter", 1);
    WindowWidth_ = (*SystemConfiguration_)["WindowWidth"].as<int>();
    Logger_->Log("Read Configuration File For 'WindowHeight' Parameter", 1);
    WindowHeight_ = (*SystemConfiguration_)["WindowHeight"].as<int>();
    Logger_->Log("Read Configuration File For 'WindowTitle' Parameter", 1);
    WindowTitle_ = (*SystemConfiguration_)["WindowTitle"].as<std::string>().c_str();


    // Create Window Object
    Window_ = glfwCreateWindow(WindowWidth_, WindowHeight_, WindowTitle_, NULL, NULL);
    if (Window_ == NULL) {
        glfwTerminate();
    }

    glfwMakeContextCurrent(Window_);

}

void Renderer::InitializeOpenGL() {

    // Setup GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        Logger_->Log("Failed To Initialize GLAD", 10);
    }

    // Setup Viewport
    Logger_->Log("Read Configuration File For 'RenderWidth' Parameter", 1);
    RenderWidth_ = (*SystemConfiguration_)["RenderWidth"].as<int>();
    Logger_->Log("Read Configuration File For 'RenderHeight' Parameter", 1);
    RenderHeight_ = (*SystemConfiguration_)["RenderHeight"].as<int>();

    glViewport(0, 0, RenderWidth_, RenderHeight_);

    // Register Callback
    glfwSetFramebufferSizeCallback(Window_, FramebufferSizeCallback);

}

bool Renderer::UpdateLoop() {

    // Process Window Input
    ProcessInput(Window_);

    // Update Window Stuff
    glfwSwapBuffers(Window_);
    glfwPollEvents();


    // Check If System Should Shutdown
    if (glfwWindowShouldClose(Window_)) {
        Logger_->Log("System Shutdown Invoked By LocalWindow", 2);
        return false;
    }

    // System Should Not Shutdown
    return true;

}

void Renderer::ProcessInput(GLFWwindow* Window) {

    if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        Logger_->Log("Window Shutdown Invoked By Keyboard [ESC]", 8);
        glfwSetWindowShouldClose(Window, true);
    }

}

void Renderer::CleanUp() {

    // Cleanup
    Logger_->Log("Cleaning Up OpenGL/GLFW", 0);
    glfwTerminate();

}