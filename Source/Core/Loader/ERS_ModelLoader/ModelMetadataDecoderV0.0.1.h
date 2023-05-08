//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Internal Libraries (BG convention: use <> instead of "")
#include <Mesh.h>
#include <Model.h>
#include <SystemUtils.h>
#include <TextureLevel.h>


/**
 * @brief Decodes model metadata from the yaml system.
 * Handles metadata for model with version 0 - or unspecified.
 * 
 * @param Metadata 
 * @param Model 
 * @param SystemUtils
 * @param AssetID
 * @return true 
 * @return false 
 */
bool ERS_FUNCTION_DecodeModelMetadataV001(YAML::Node Metadata, ERS_STRUCT_Model* Model, ERS_STRUCT_SystemUtils* SystemUtils, long AssetID, bool LogEnable = true);