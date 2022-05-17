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



/**
 * @brief This class renders any ui/Menu info onto the viewport as requested by the viewport struct.
 * 
 */
class ERS_CLASS_ViewportMenu {

private:

    ERS_STRUCT_SystemUtils* SystemUtils_; /**<Pointer to systemtuils resource*/
    ERS_STRUCT_ProjectUtils* ProjectUtils_; /**<Pointer to project utils instance*/

    std::map<int, std::shared_ptr<ERS_STRUCT_Shader>>* Shaders_; /**<Pointer to map containing shader information*/

    bool* IsEditorMode_; /**<Pointer to bool setting editor mode to enabled or disablewd*/
    float* GamestartTime_; /**<Pointer to float setting the glfw time when the game clock started*/


public:

    /**
     * @brief Construct a new ers class viewportMenu object
     * 
     * @param SystemUtils 
     */
    ERS_CLASS_ViewportMenu(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils, float* GameStartTime, bool* IsEditorMode, std::map<int, std::shared_ptr<ERS_STRUCT_Shader>>* Shaders);

    /**
     * @brief Destroy the ers class viewportMenu object
     * 
     */
    ~ERS_CLASS_ViewportMenu();

    /**
     * @brief Draw the Menu on the viewport pointer passed in.
     * 
     * @param Viewport 
     */
    void DrawMenu(ERS_STRUCT_Viewport* Viewport);

};