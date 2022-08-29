//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_ControllerSettings.h>
#include <ERS_STRUCT_ShaderProgramAssetIDs.h>
#include <ERS_STRUCT_Script.h>


/**
 * @brief Struct to store model import settings
 * 
 */
struct ERS_STRUCT_ModelImportOptions {

    bool FlipTextures = true; /**<Inverts the textures when loading - default to on*/

};
