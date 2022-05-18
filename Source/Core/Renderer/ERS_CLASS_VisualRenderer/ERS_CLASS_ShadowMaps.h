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
#include <ERS_CLASS_DepthMaps.h>

#include <ERS_SceneManager.h>

#include <ERS_STRUCT_ProjectUtils.h>
#include <ERS_STRUCT_SystemUtils.h>
#include <ERS_STRUCT_Viewport.h>
#include <ERS_STRUCT_DepthMap.h>



/**
 * @brief This class renders any ui/overlay info onto the viewport as requested by the viewport struct.
 * 
 */
class ERS_CLASS_ShadowMaps {

private:

    ERS_STRUCT_SystemUtils* SystemUtils_; /**<Pointer to systemtuils resource*/
    ERS_STRUCT_ProjectUtils* ProjectUtils_; /**<Pointer to project utils instance*/

    std::map<int, std::shared_ptr<ERS_STRUCT_Shader>>* Shaders_; /**<Pointer to map of shader pointers and shader program ids*/

    std::unique_ptr<ERS_CLASS_DepthMaps> ERS_CLASS_DepthMaps_; /**<Instance of the depth map class*/


public:

    /**
     * @brief Construct a new ers class ShadowMaps object
     * 
     * @param SystemUtils 
     */
    ERS_CLASS_ShadowMaps(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils);

    /**
     * @brief Destroy the ers class ShadowMaps object
     * 
     */
    ~ERS_CLASS_ShadowMaps();



    /**
     * @brief This function will update the shadow maps of all lights in the scene.
     * This function checks the scenemanger and other shared classes to get info about the scene.
     * 
     */
    void UpdateShadowMaps();


};