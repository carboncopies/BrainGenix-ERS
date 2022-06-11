//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <iostream>
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_SceneManager.h>

#include <ERS_STRUCT_Shader.h>
#include <ERS_STRUCT_Model.h>


/**
 * @brief Converts the passed in rotation to the front vector.
 * 
 * @param Rotation 
 * @return glm::vec3 
 */
glm::vec3 ERS_FUNCTION_ConvertRotationToFrontVector(glm::vec3 Rotation);