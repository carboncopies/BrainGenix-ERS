//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the visual renderer.
    Additonal Notes: None
    Date Created: 2021-11-20
*/

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <iostream>
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>
#include <Shader.h>
#include <Model.h>
#include <NoClip.h>
#include <TextureLoader.h>
#include <ModelLoader.h>
#include <SceneManager.h>
#include <SceneLoader.h>
#include <ShaderLoader.h>
#include <InputProcessor.h>
#include <GUI.h>
#include <Framebuffer.h>
#include <3DCursor.h>




class VisualRenderer {

    private:

        // Member Variables
        YAML::Node *SystemConfiguration_; /**<Pointer to the system configuration YAML::Node*/
        LoggerClass *Logger_; /**<Pointer to the logging system instance*/
        GLFWwindow *Window_; /**<GLFW Window Instance For Window Input To Viewports*/


        std::vector<ERS_OBJECT_CAMERA_NOCLIP*> Cameras_; /**<List Of Pointers To Camera Instances*/
        std::vector<ERS_OBJECT_SHADER*> Shaders_; /**<List Of Pointers To Shader Instances*/
        std::vector<std::string> ViewportNames_; /**<List Of Names For Viewports*/
        std::vector<InputProcessor*> InputProcessors_; /**<Vector Of InputProcessors*/

        std::vector<unsigned int> FramebufferObjects_; /**<Framebuffer Objects For Each Viewport*/
        std::vector<unsigned int> FramebufferColorObjects_; /**<Render Texture For Displaying Color*/
        std::vector<unsigned int> RenderbufferObjects_; /**<Render buffer Objects For Depth*/

        std::vector<int> ViewportWidths_; /**<Vector Containing Viewport Widths In Pixels*/
        std::vector<int> ViewportHeights_; /**<Vector Containing Viewport Heights In Pixels*/
 


        // Internal Functions
        void InitializeOpenGL();
        void ResizeViewport(int Index, int Width, int Height);



    public:

        // Constructor
        VisualRenderer(YAML::Node *SystemConfiguration, GLFWwindow* Window, LoggerClass *Logger);

        // Destructor
        ~VisualRenderer();


        void CreateViewport(ERS_OBJECT_SHADER *Shader, std::string ViewportName, GLFWwindow* Window, ERS_OBJECT_CAMERA_NOCLIP *Camera);
        void UpdateViewports(float DeltaTime, SceneManager *SceneManager);
        void UpdateViewport(int Index, SceneManager *SceneManager, float DeltaTime);

        

};
