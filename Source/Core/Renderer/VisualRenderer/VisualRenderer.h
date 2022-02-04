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
#include <chrono>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_CLASS_LoggingSystem.h>
#include <ERS_STRUCT_Shader.h>
#include <Model.h>
#include <NoClip.h>
#include <ERS_SceneManager.h>
#include <ERS_SceneLoader.h>
#include <ERS_CLASS_ShaderLoader.h>
#include <InputProcessor.h>
#include <Framebuffer.h>
#include <ERS_Editor_3DCursor.h>

#include <ERS_STRUCT_LocRotScale.h>
#include <ERS_STRUCT_SystemUtils.h>


class VisualRenderer {

private:

    // Member Variables
    GLFWwindow *Window_; /**<GLFW Window Instance For Window Input To Viewports*/
    std::shared_ptr<Cursors3D> Cursors3D_; /**<Setup 3D Cursor Class*/
    long int FrameNumber_ = 0; /**<Frame counter, starts at 0*/

public:

    std::vector<std::shared_ptr<ERS_OBJECT_CAMERA_NOCLIP>> Cameras_; /**<List Of Pointers To Camera Instances*/
    
    std::map<int, std::shared_ptr<ERS_STRUCT_Shader>> Shaders_; /**<Map of shader pointers and shader program ids*/
    std::vector<int> ActiveShaders_; /**<Index of shader program used by each viewport*/
    int DefaultShader_ = 0; /**<Index of default shader program to be used*/

    std::vector<std::string> ViewportNames_; /**<List Of Names For Viewports*/
    std::vector<std::shared_ptr<InputProcessor>> InputProcessors_; /**<Vector Of InputProcessors*/
    std::vector<bool> WasSelected_; /**<List of true/false for was viewport selected last frame*/
    std::vector<std::shared_ptr<bool>> ViewportEnabled_; /**<List of bool value pointers indicating if viewport should stay open*/

    std::vector<unsigned int> FramebufferObjects_; /**<Framebuffer Objects For Each Viewport*/
    std::vector<unsigned int> FramebufferColorObjects_; /**<Render Texture For Displaying Color*/
    std::vector<unsigned int> RenderbufferObjects_; /**<Render buffer Objects For Depth*/

    std::vector<int> ViewportWidths_; /**<Vector Containing Viewport Widths In Pixels*/
    std::vector<int> ViewportHeights_; /**<Vector Containing Viewport Heights In Pixels*/

    std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<System Utils Struct Containing Pointers To Important Info*/


    bool CaptureCursor_ = false; /**<Indicate if cursor should be captured*/
    int CaptureIndex_ = 0; /**<Index where cursor was captured*/

private:

    /**
     * @brief Initialize an opengl context for the viewport
     * 
     */
    void InitializeOpenGL();

    /**
     * @brief Resize a viewport of specified index to the set width and height
     * 
     * @param Index 
     * @param Width 
     * @param Height 
     */
    void ResizeViewport(int Index, int Width, int Height);

    /**
     * @brief Update the shader used
     * 
     * @param ShaderIndex 
     * @param DeltaTime 
     * @param RenderWidth 
     * @param RenderHeight 
     */
    void UpdateShader(int ShaderIndex, float DeltaTime, int RenderWidth, int RenderHeight);

    /**
     * @brief Set the Shader object
     * 
     * @param Shader 
     * @param ID 
     */
    void SetShader(std::shared_ptr<ERS_STRUCT_Shader> Shader, int ID);

    /**
     * @brief Set the Default Shader by index
     * 
     * @param ShaderID 
     */
    void SetDefaultShader(int ShaderID);

    /**
     * @brief Updates a specific vieport of given index (should be used in update viepowrts function)
     * 
     * @param Index 
     * @param SceneManager 
     * @param DeltaTime 
     */
    void UpdateViewport(int Index, std::shared_ptr<ERS_CLASS_SceneManager> SceneManager, float DeltaTime);


public:

    /**
     * @brief Construct a new Visual Renderer object
     * 
     * @param SystemUtils 
     * @param Window 
     * @param Cursors3D 
     */
    VisualRenderer(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, GLFWwindow* Window, std::shared_ptr<Cursors3D> Cursors3D);

    /**
     * @brief Destroy the Visual Renderer object
     * 
     */
    ~VisualRenderer();


    /**
     * @brief Create a Viewport object
     * 
     * @param ViewportName 
     */
    void CreateViewport(std::string ViewportName);

    /**
     * @brief Create a Viewport object (automatically set name of viewport)
     * 
     */
    void CreateViewport();

    /**
     * @brief Draw the contents of all active viewports
     * 
     * @param DeltaTime 
     * @param SceneManager 
     */
    void UpdateViewports(float DeltaTime, std::shared_ptr<ERS_CLASS_SceneManager> SceneManager);

    /**
     * @brief Delete a veiwport of specified index
     * 
     * @param Index 
     */
    void DeleteViewport(int Index);
    
 
        

};
