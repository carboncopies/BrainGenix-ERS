//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <iostream>
#include <string>
#include <chrono>
#include <memory>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>
#include <ShaderLoader.h>
#include <InputProcessor.h>
#include <Grid.h>

#include <CheckForMeshTransparency.h>
#include <MeshTransparencySort.h>
#include <MeshTransparencySortNoTextures.h>
#include <DrawMesh.h>
#include <DrawMeshNoTextures.h>
#include <SetShaderUniformData.h>

#include <SceneManager.h>
#include <SceneLoader.h>

#include <3DCursor.h>

#include <LocRotScale.h>
#include <SystemUtils.h>
#include <Viewport.h>
#include <Shader.h>
#include <Model.h>
#include <Camera.h>
#include <OpenGLDefaults.h>



/**
 * @brief This class handles extracting, sorting, and rendering all meshes in a scene.
 * 
 */
class ERS_CLASS_MeshRenderer {

private:

    ERS_STRUCT_SystemUtils* SystemUtils_; /**<Pointer to system utils struct*/
    

public:

    /**
     * @brief Construct a new ers class meshrenderer object
     * 
     * @param SystemUtils 
     */
    ERS_CLASS_MeshRenderer(ERS_STRUCT_SystemUtils* SystemUtils);

    /**
     * @brief Destroy the ers class meshrenderer object
     * 
     */
    ~ERS_CLASS_MeshRenderer();

    /**
     * @brief Render the given scene with the given parameters.
     * 
     * @param Scene 
     * @param OpenGLDefaults 
     * @param Shader 
     */
    void RenderScene(ERS_STRUCT_Scene* Scene, ERS_STRUCT_OpenGLDefaults* OpenGLDefaults, std::vector<ERS_STRUCT_Shader*> Shaders, int DefaultShaderIndex, ERS_STRUCT_ShaderUniformData ShaderUniformInfo);

    /**
     * @brief Render the scene without textures (used to generate depth maps)
     * 
     * @param Scene 
     */
    void RenderSceneNoTextures(ERS_STRUCT_Scene* Scene, ERS_STRUCT_Shader* Shader);


};