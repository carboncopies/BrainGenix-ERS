//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

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
#include <ERS_CLASS_ShaderLoader.h>
#include <ERS_CLASS_InputProcessor.h>
#include <ERS_CLASS_Framebuffer.h>
#include <ERS_CLASS_Grid.h>
#include <ERS_CLASS_LightIconRenderer.h>
#include <ERS_CLASS_MeshRenderer.h>

#include <ERS_SceneManager.h>
#include <ERS_SceneLoader.h>

#include <ERS_Editor_3DCursor.h>

#include <ERS_STRUCT_LocRotScale.h>
#include <ERS_STRUCT_SystemUtils.h>
#include <ERS_STRUCT_Viewport.h>
#include <ERS_STRUCT_Shader.h>
#include <ERS_STRUCT_Model.h>
#include <ERS_STRUCT_Camera.h>
#include <ERS_STRUCT_OpenGLDefaults.h>
#include <ERS_STRUCT_ProjectUtils.h>


/**
 * @brief Handles viewport creation/deletion/rendering/updating.
 * 
 */
class ERS_CLASS_VisualRenderer {

private:

    GLFWwindow *Window_; /**<GLFW Window Instance For Window Input To Viewports*/
    Cursors3D* Cursors3D_; /**<Setup 3D Cursor Class*/
    long int FrameNumber_ = 0; /**<Frame counter, starts at 0*/
    int ActiveViewportCursorIndex_; /**<The index of the viewport which the gizmo is being interacted with*/
    ERS_STRUCT_OpenGLDefaults* OpenGLDefaults_; /**<Pointer acquired from renderermanager*/
    ERS_STRUCT_ProjectUtils* ProjectUtils_; /**<Project Utils pointer, used to get info about scripts*/

    std::unique_ptr<ERS_CLASS_MeshRenderer> MeshRenderer_; /**<Instance Of The Mesh Renderer Class Used To Hancle The Actual Rendering Of All Meshes In The Given Scene*/

public:
    
    std::vector<std::shared_ptr<ERS_STRUCT_Viewport>> Viewports_; /**Pointer to struct of viewports*/

    std::map<int, std::shared_ptr<ERS_STRUCT_Shader>> Shaders_; /**<Map of shader pointers and shader program ids*/
    int DefaultShader_ = 0; /**<Index of default shader program to be used*/

    ERS_STRUCT_SystemUtils* SystemUtils_; /**<System Utils Struct Containing Pointers To Important Info*/


    bool CaptureCursor_ = false; /**<Indicate if cursor should be captured*/
    int CaptureIndex_ = 0; /**<Index where cursor was captured*/
    
    int SelectedScript_ = -1; /**<Set the selected script index*/
    std::vector<std::string>* DebugLog_; /**<Script Debug Log Pointer, Sends Script Traceback/Error Info Here*/

    double RunTime_; /**<Number of seconds since start of "play" mode. (other mode is editor mode)*/
    double GameStartTime_; /**<Time when the game entered "play" mode, used to calc the runtime variable*/
    bool IsEditorMode_; /**<Sets if in editor or play mode*/


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
     * @param SceneManager
     */
    void UpdateShader(int ShaderIndex, float DeltaTime, int RenderWidth, int RenderHeight, ERS_CLASS_SceneManager*SceneManager, ERS_STRUCT_Camera* Camera);


    /**
     * @brief Updates a specific vieport of given index (should be used in update viepowrts function)
     * 
     * @param Index 
     * @param SceneManager 
     * @param DeltaTime 
     */
    void UpdateViewport(int Index, ERS_CLASS_SceneManager* SceneManager, float DeltaTime, bool DrawCursor = true);


    /**
     * @brief Draws the viewport's menu (enable/disable handled internally in this function)
     * 
     * @param Index 
     */
    void DrawViewportMenu(int Index, ERS_CLASS_SceneManager* SceneManager);

    /**
     * @brief Returns the index of the shader with name that matches the name given. Will return 0 if the shader is not found.
     * 
     * @param Name 
     * @return long 
     */
    long FindShaderIndex(std::string Name);

    /**
     * @brief Tell the visual renderer what script the scripteditor window is working on, provide pointer to debug log used by the window.
     * 
     * @param ScriptIndex 
     * @param DebugLog 
     */
    void SetScriptDebug(int ScriptIndex, std::vector<std::string>* DebugLog);


public:

    /**
     * @brief Construct a new Visual Renderer object
     * 
     * @param SystemUtils 
     * @param Window 
     * @param Cursors3D 
     */
    ERS_CLASS_VisualRenderer(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils, GLFWwindow* Window, Cursors3D* Cursors3D);

    /**
     * @brief Destroy the Visual Renderer object
     * 
     */
    ~ERS_CLASS_VisualRenderer();


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
    void UpdateViewports(float DeltaTime, ERS_CLASS_SceneManager* SceneManager);

    /**
     * @brief Delete a veiwport of specified index
     * 
     * @param Index 
     */
    void DeleteViewport(int Index);
    
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
     * @brief Set the OpenGL Defaults object
     * 
     * @param Defaults 
     */
    void SetOpenGLDefaults(ERS_STRUCT_OpenGLDefaults* Defaults);

};
