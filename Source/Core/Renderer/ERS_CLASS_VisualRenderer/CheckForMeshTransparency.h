//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <iostream>
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <SceneManager.h>

#include <Shader.h>
#include <Model.h>
#include <Scene.h>


/**
 * @brief Updates the transparency bool in each mesh, allowing for sorting to take place
 * 
 * @param Scene 
 */
void ERS_FUNCTION_UpdateMeshTransparency(ERS_STRUCT_Scene* Scene);