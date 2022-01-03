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
#include <glm/gtx/string_cast.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>
#include <Shader.h>
#include <Model.h>
#include <NoClip.h>
#include <SceneManager.h>
#include <ERS_SceneLoader.h>
#include <ShaderLoader.h>
#include <InputProcessor.h>
#include <GUI.h>
#include <Framebuffer.h>
#include <ERS_Editor_3DCursor.h>

#include <ERS_STRUCT_LocRotScale.h>
#include <ERS_STRUCT_SystemUtils.h>


class VisualRenderer {

    private:

        // Member Variables
        GLFWwindow *Window_; /**<GLFW Window Instance For Window Input To Viewports*/
        std::shared_ptr<Cursors3D> Cursors3D_; /**<Setup 3D Cursor Class*/

        std::vector<std::shared_ptr<ERS_OBJECT_CAMERA_NOCLIP>> Cameras_; /**<List Of Pointers To Camera Instances*/
        std::vector<std::shared_ptr<ERS_OBJECT_SHADER>> Shaders_; /**<List Of Pointers To Shader Instances*/
        std::vector<std::string> ViewportNames_; /**<List Of Names For Viewports*/
        std::vector<std::shared_ptr<InputProcessor>> InputProcessors_; /**<Vector Of InputProcessors*/

        std::vector<unsigned int> FramebufferObjects_; /**<Framebuffer Objects For Each Viewport*/
        std::vector<unsigned int> FramebufferColorObjects_; /**<Render Texture For Displaying Color*/
        std::vector<unsigned int> RenderbufferObjects_; /**<Render buffer Objects For Depth*/

        std::vector<int> ViewportWidths_; /**<Vector Containing Viewport Widths In Pixels*/
        std::vector<int> ViewportHeights_; /**<Vector Containing Viewport Heights In Pixels*/

        std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<System Utils Struct Containing Pointers To Important Info*/


        // Internal Functions
        void InitializeOpenGL();
        void ResizeViewport(int Index, int Width, int Height);



    public:

        // Constructor
        VisualRenderer(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, GLFWwindow* Window, std::shared_ptr<Cursors3D> Cursors3D);

        // Destructor
        ~VisualRenderer();


        void CreateViewport(std::shared_ptr<ERS_OBJECT_SHADER> Shader, std::string ViewportName, GLFWwindow* Window, std::shared_ptr<ERS_OBJECT_CAMERA_NOCLIP> Camera);
        void UpdateViewports(float DeltaTime, std::shared_ptr<SceneManager> SceneManager);
        void UpdateViewport(int Index, std::shared_ptr<SceneManager> SceneManager, float DeltaTime);

        

};
