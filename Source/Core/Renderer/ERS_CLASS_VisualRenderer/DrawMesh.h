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

#include <ResetMeshTexture.h>

#include <Shader.h>
#include <Model.h>




/**
 * @brief Draws the mesh passed in.
 * 
 * @param Mesh 
 * @param OpenGLDefaults 
 * @param Shader 
 */
void ERS_FUNCTION_DrawMesh(ERS_STRUCT_Mesh* Mesh, ERS_STRUCT_OpenGLDefaults* OpenGLDefaults, ERS_STRUCT_Shader* Shader);