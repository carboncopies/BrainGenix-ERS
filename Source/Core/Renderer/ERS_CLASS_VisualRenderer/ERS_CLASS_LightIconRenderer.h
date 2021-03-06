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
#include <ERS_STRUCT_OpenGLDefaults.h>
#include <ERS_STRUCT_Camera.h>

#include <ERS_SceneManager.h>



class ERS_CLASS_LightIconRenderer {

private:

    ERS_STRUCT_SystemUtils* SystemUtils_; /**<Shared Pointer To System Utils*/
    ERS_STRUCT_OpenGLDefaults* OpenGLDefaults_; /**<Pointer acquired from renderermanager*/
    ERS_STRUCT_Shader* LightIconRendererShader_; /**<Pointer To Shader With LightIconRenderer*/
    glm::mat4 LightIconRendererModelArray_; /**<LightIconRenderer Model Mat4*/

    unsigned int LightIconRendererVBO_; /**<OpenGL ID To LightIconRenderer Vertex Buffer Object*/
    unsigned int LightIconRendererVAO_; /**<OpenGL ID To LightIconRenderer Vertex Array Object*/
    float LightIconRendererScale_ = 0.1f; /**<Scale of editor icons*/


public:

    /**
     * @brief Construct a new ers class grid object
     * 
     * @param SystemUtils 
     */
    ERS_CLASS_LightIconRenderer(ERS_STRUCT_OpenGLDefaults* Defaults, ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_Shader* LightIconRendererShader);

    /**
     * @brief Destroy the ers class grid object
     * 
     */
    ~ERS_CLASS_LightIconRenderer();


    /**
     * @brief Draw Command
     * 
     */
    void Draw(ERS_STRUCT_Camera* Camera, ERS_CLASS_SceneManager* SceneManager);

};