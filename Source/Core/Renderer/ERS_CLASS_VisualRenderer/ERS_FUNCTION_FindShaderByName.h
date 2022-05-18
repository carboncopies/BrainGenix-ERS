//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <iostream>
#include <string>
#include <map>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_Shader.h>


/**
 * @brief Returns the index of a shader with a name that matches the input name.
 * Will re
 * 
 * @param Name 
 * @param Shaders 
 */
void ERS_FUNCTION_FindShaderByName(std::string Name, std::map<int, std::shared_ptr<ERS_STRUCT_Shader>>* Shaders);