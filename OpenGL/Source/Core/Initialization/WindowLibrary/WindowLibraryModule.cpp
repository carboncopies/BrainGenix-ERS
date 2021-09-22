//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing GLFW features.
    Additonal Notes: None
    Date Created: 2021-09-21
*/ 

#include <iostream>
#include <yaml-cpp/yaml.h>

void InitializeGLFW (YAML::Node ConfigFile, LoggerClass LoggingSystem) {
    
    // Check GLFW Configuration Status //
    LoggingSystem.Log("Checking Config File For 'WindowEnabled' Parameter");
    const bool WindowEnabled = ConfigFile["WindowEnabled"].as<bool>();

    if (WindowEnabled) {

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


        GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);


        if (window == NULL)
        {

            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();

        }

        glfwMakeContextCurrent(window);

    }

}