//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <memory>


// Third-Party Libraries (BG convention: use <> instead of "")
#include <glad/glad.h>

#include <GLFW/glfw3.h>


// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_SystemUtils.h>
#include <ERS_STRUCT_Shader.h>
#include <ERS_STRUCT_Camera.h>
#include <ERS_STRUCT_Scene.h>




class ERS_CLASS_BoundingBoxRenderer {

private:

    ERS_STRUCT_SystemUtils* SystemUtils_; /**<Shared Pointer To System Utils*/
    ERS_STRUCT_Shader* BoundingBoxRendererShader_; /**<Pointer To Shader With BoundingBoxRenderer*/
    glm::mat4 BoundingBoxRendererModelArray_; /**<BoundingBoxRenderer Model Mat4*/

    unsigned int BoundingBoxRendererVBO_; /**<OpenGL ID To BoundingBoxRenderer Vertex Buffer Object*/
    unsigned int BoundingBoxRendererVAO_; /**<OpenGL ID To BoundingBoxRenderer Vertex Array Object*/
    float BoundingBoxRendererScale_ = 0.1f; /**<Scale of editor icons*/


    bool DisableDepthTest_ = true; /**<Tell the renderer to disable the depth test prior to drawing the boxes*/
    bool DrawWireframe_ = true; /**<Tell the system to enable or disable wireframe mode*/

public:

    /**
     * @brief Construct a new ers class grid object
     * 
     * @param SystemUtils 
     */
    ERS_CLASS_BoundingBoxRenderer(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_Shader* BoundingBoxRendererShader);

    /**
     * @brief Destroy the ers class grid object
     * 
     */
    ~ERS_CLASS_BoundingBoxRenderer();


    /**
     * @brief Renders the bounding boxes in the target scene from the camera's perspective
     * 
     */
    void Draw(ERS_STRUCT_Camera* Camera, ERS_STRUCT_Scene* Scene);

    /**
     * @brief Enable or disable depth testing
     * 
     * @param DepthTestEnabled 
     */
    void SetDepthTest(bool DepthTestEnabled);

    /**
     * @brief Set the draw mode to be wireframe or solid
     * 
     * @param WireframeEnabled 
     */
    void SetDrawMode(bool WireframeEnabled);


};