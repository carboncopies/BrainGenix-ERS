//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing GLFW features.
    Additonal Notes: None
    Date Created: 2021-09-21
*/ 

#include <iostream>
#include <string>

#include <yaml-cpp/yaml.h>


class GLFWWindow {

    private:


    public:

        int RenderWidth;
        int RenderHeight;
        bool AllowRenderResize;

        // Initialization Function for GLFWWindow Class //
        GLFWwindow* InitializeGLFW (YAML::Node ConfigFile, LoggerClass LoggingSystem) {
            
            // Check GLFW Configuration Status //
            LoggingSystem.Log("Checking Config File For 'WindowEnabled' Parameter", 3);
            const bool WindowEnabled = ConfigFile["WindowEnabled"].as<bool>();

            // Check Render Window Resize Config Parameter //
            LoggingSystem.Log("Checking Config File For 'AllowRenderResize' Parameter", 2);
            AllowRenderResize = ConfigFile["WindowEnabled"].as<bool>();

            if (WindowEnabled) {

                // Log State of WindowEnabled Configuration //
                LoggingSystem.Log("Configuration Term 'WindowEnabled' Set To True", 1);


                // Log GLFW Init //
                LoggingSystem.Log("Initializing GLFW", 2);
                glfwInit();

                // Set Window Hints //
                LoggingSystem.Log("Setting GLFW Context Versions", 1);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

                LoggingSystem.Log("Setting OpenGL Profiles", 1);
                glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


                // Read Window Configuration Parameters //
                LoggingSystem.Log("Checking Config File For 'WindowWidth' Parameter", 2);
                const int WindowWidth = ConfigFile["WindowWidth"].as<int>();
                LoggingSystem.Log("Checking Config File For 'WindowHeight' Parameter", 2);
                const int WindowHeight = ConfigFile["WindowHeight"].as<int>();
                LoggingSystem.Log("Checking Config File For 'WindowTitle' Parameter", 2);
                const char* WindowTitle = ConfigFile["WindowTitle"].as<std::string>().c_str();
                        
                LoggingSystem.Log("Creating GLFW Window", 4);
                GLFWwindow* Window = glfwCreateWindow(WindowWidth, WindowHeight, WindowTitle, NULL, NULL);

                // Validate Window Creation Success
                LoggingSystem.Log("Checking State of GLFW Window Object", 3);
                if (Window == NULL) {

                    LoggingSystem.Log("Failed To Create GLFW Window Object, System Will Run Headless", 7); 
                    glfwTerminate();

                    // Indicate That A Window Has Not Been Created //
                    return nullptr;

                }
                else {
                    LoggingSystem.Log("Successfully Created GLFW Window Object", 3);

                    // Make Current Window Context //
                    LoggingSystem.Log("Setting Context To Window", 2);
                    glfwMakeContextCurrent(Window);



                    // Indicate That A Window Has Been Created //
                    return Window;
                }
            }

            // Indicate That A Window Has Not Been Created //
            return nullptr;

        }

        // Initailizes The GL Viewport //
        void InitializeGLViewport(YAML::Node ConfigFile, LoggerClass LoggingSystem) {

            LoggingSystem.Log("Checking Config File For 'RenderWidthPixels' Parameter", 3);
            RenderWidth = ConfigFile["RenderWidthPixels"].as<int>();
            LoggingSystem.Log("Checking Config File For 'RenderHeightPixels' Parameter", 3);
            RenderHeight = ConfigFile["RenderHeightPixels"].as<int>();

            LoggingSystem.Log("Initializing OpenGL Viewport", 5);
            glViewport(0,0, RenderWidth, RenderHeight);

        }


};