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
#include <BG/Common/Logger/Logger.h>
#include <Shader.h>


/**
 * @brief Returns the index of a shader with a name that matches the input name.
 * 
 * The renderer hard-requires projects to define shaders named '_DepthMap',
 * '_DepthCubeMap', '_Grid', '_LightIcon' and '_BoundingBox'. If the requested
 * shader cannot be found, this returns index 0 as a last resort (preserving the
 * existing calling contract) and logs an error once per distinct missing name,
 * since some callers invoke this every frame.
 * 
 * @param Name 
 * @param Shaders 
 * @param Logger Optional logger used to report missing shaders.
 */
unsigned int ERS_FUNCTION_FindShaderByName(std::string Name, std::vector<std::unique_ptr<ERS_STRUCT_Shader>>* Shaders, BG::Common::Logger::LoggingSystem* Logger = nullptr);