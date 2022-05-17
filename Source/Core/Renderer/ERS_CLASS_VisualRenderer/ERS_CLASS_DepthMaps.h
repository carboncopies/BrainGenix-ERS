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


    /**
     * @brief Generates a depth map with the given resolution.
     * This is usually used for shadows later on in the rendering process.
     * Will also default to a 2048x2048 depth map by default. 
     * 
     * @param ResolutionX 
     * @param ResolutionY 
     * @return unsigned int 
     */
    unsigned int GenerateDepthMap(int ResolutionX = 2048, int ResolutionY = 2048);


public:

    /**
     * @brief Construct a new ers class DepthMaps object
     * 
     * @param SystemUtils 
     */
    ERS_CLASS_DepthMaps(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils);

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
     */
    void UpdateDepthMaps();


};