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
#include <ERS_CLASS_Grid.h>
#include <ERS_CLASS_LightIconRenderer.h>
#include <ERS_CLASS_MeshRenderer.h>
#include <ERS_CLASS_ViewportOverlay.h>
#include <ERS_CLASS_ViewportMenu.h>
#include <ERS_CLASS_ShadowMaps.h>

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

#include <ERS_FUNCTION_FindShaderByName.h>
#include <ERS_FUNCTION_ConvertRotationToFrontVector.h>

#include <ERS_ENUM_ShadowFilteringType.h>

/**
 * @brief Handles viewport creation/deletion/rendering/updating.
 * 
 */
class ERS_CLASS_VisualRenderer {

private:

    GLFWwindow *Window_; /**<GLFW Window Instance For Window Input To Viewports*/
    Cursors3D* Cursors3D_; /**<Setup 3D Cursor Class*/

    ERS_STRUCT_OpenGLDefaults* OpenGLDefaults_; /**<Pointer acquired from renderermanager*/
    ERS_STRUCT_ProjectUtils* ProjectUtils_; /**<Project Utils pointer, used to get info about scripts*/
    ERS_STRUCT_Shader* DepthMapShader_; /**<Depth Map Shader Pointer*/
    ERS_STRUCT_Shader* CubemapDepthShader_; /**<Cubemap Depth Shader*/
    
    std::unique_ptr<ERS_CLASS_ShadowMaps> ShadowMaps_; /**<Instance of shadow mapping class used to provide system wide shadows*/
    std::unique_ptr<ERS_CLASS_MeshRenderer> MeshRenderer_; /**<Instance Of The Mesh Renderer Class Used To Hancle The Actual Rendering Of All Meshes In The Given Scene*/
    std::unique_ptr<ERS_CLASS_ViewportOverlay> ViewportOverlay_; /**<Class that handles overlaying ui elements and text onto the viewport when requested by the viewporr struct*/
    std::unique_ptr<ERS_CLASS_ViewportMenu> ViewportMenu_; /**<Class that provides the viewport menu functionality in a convenient manner to the visualrenderer system*/

    long int FrameNumber_ = 0; /**<Frame counter, starts at 0*/
    int ActiveViewportCursorIndex_; /**<The index of the viewport which the gizmo is being interacted with*/


public:
    
    std::vector<std::shared_ptr<ERS_STRUCT_Viewport>> Viewports_; /**Pointer to struct of viewports*/

    std::vector<std::unique_ptr<ERS_STRUCT_Shader>> Shaders_; /**<Vector of shaders to be used in the system*/
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

    /**
     * @brief Tell the visual renderer what script the scripteditor window is working on, provide pointer to debug log used by the window.
     * 
     * @param ScriptIndex 
     * @param DebugLog 
     */
    void SetScriptDebug(int ScriptIndex, std::vector<std::string>* DebugLog);

};
