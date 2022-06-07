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
#include <ERS_CLASS_MeshRenderer.h>

#include <ERS_SceneManager.h>

#include <ERS_STRUCT_ProjectUtils.h>
#include <ERS_STRUCT_SystemUtils.h>
#include <ERS_STRUCT_Viewport.h>
#include <ERS_STRUCT_DepthMap.h>



/**
 * @brief This class renders any ui/overlay info onto the viewport as requested by the viewport struct.
 * 
 */
class ERS_CLASS_DepthMaps {

private:

    ERS_STRUCT_SystemUtils* SystemUtils_; /**<Pointer to systemtuils resource*/
    ERS_STRUCT_ProjectUtils* ProjectUtils_; /**<Pointer to project utils instance*/

    ERS_CLASS_MeshRenderer* Renderer_; /**<Pointer to Mesh Renderer Class Instance*/

    unsigned int DepthMapAllocationChunkSize_ = 16; /**<Allocate Depth Map In Chunks Of 5*/


    unsigned int AllocateDepthMapIndex();


public:


    unsigned int DepthTextureArrayID_; /**<OpenGL Object ID For Depth Map Textures*/
    int DepthTextureArrayWidth_; /***<Width of the depth map texture*/
    int DepthTextureArrayHeight_; /**<Height of the depth map texutre*/
    int DepthTextureNumTextures_; /**<Number of textures that the tex array can hold*/
    std::vector<bool> DepthMapTexturesAlreadyAllocated_; /**<Use This To Check if the texture is already allocated or not*/


    /**
     * @brief Generates a depth map array (array texture), with the given width, height and number of layers.
     * 
     * @param NumberOfTextures Number of textures in the array
     * @param Width Height of the array
     * @param Height Width of the array
     * @param LogEnabled Enab;e/Disable Log Output
     * @return true 
     * @return false 
     */
    bool RegenerateDepthMapTextureArray(int NumberOfTextures, int Width = 2048, int Height = 2048, bool LogEnabled = true);


    /**
     * @brief Generates a depth map with the given resolution.
     * This is usually used for shadows later on in the rendering process.
     * Will also default to a 2048x2048 depth map by default. 
     * 
     * @param ResolutionX Width in pixels of the depth map
     * @param ResolutionY Height in pixels of the depth map
     * @param LogOutput Enable/disable logging output
     * @return ERS_STRUCT_DepthMap Struct containing the relevant opengl ids for this depth map
     */
    ERS_STRUCT_DepthMap GenerateDepthMap(int ResolutionX = 2048, int ResolutionY = 2048, bool LogOutput = true);


    /**
     * @brief Construct a new ers class DepthMaps object
     * 
     * @param SystemUtils 
     */
    ERS_CLASS_DepthMaps(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils, ERS_CLASS_MeshRenderer* Renderer);

    /**
     * @brief Destroy the ers class DepthMaps object
     * 
     */
    ~ERS_CLASS_DepthMaps();


    /**
     * @brief Checks the number of depth maps vs the number of lights and makes sure that the number of depth maps is equal to the number of lights.
     * Will generate more depth maps and remove unused ones by calling internal functions in this class.
     * 
     */
    void UpdateNumberOfDepthMaps();

    /**
     * @brief Iterates over all lights in the scene and renders all depth maps.
     * 
     * @param DepthShader 
     */
    void UpdateDepthMaps(ERS_STRUCT_Shader* DepthShader);






    /**
     * @brief This function creates a depth map from the perspective of the given position data.
     * The depth map texture is cleared, and then rendered to.
     * This function is designed to be used in shadow maps, but can be used elsewhere when appropriate.
     * 
     * @param Target 
     * @param Pos 
     * @param Rot 
     * @param Scale 
     * @param Orthogonal Use Orthogonal for directional lights and perspective for everything else
     */
    void UpdateDepthMap(ERS_STRUCT_DepthMap* Target, ERS_STRUCT_Shader* DepthShader, glm::vec3 Pos, glm::vec3 Rot, bool Orthogonal = true, glm::mat4* LightSpaceMatrix = nullptr);

};