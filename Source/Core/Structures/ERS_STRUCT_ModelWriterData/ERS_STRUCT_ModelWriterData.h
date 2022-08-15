//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <assimp/scene.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_Model.h>

/**
 * @brief Stores information that is needed by the model writer such as a pointer to the model itself as well as more information such as the aiScene, etc.
 * 
 */
struct ERS_STRUCT_ModelWriterData {


    aiScene*           ModelScene;   /**<Pointer to assimp scene decoded by the importer*/
    long               ModelAssetID; /**<Asset ID of model geometry*/
    ERS_STRUCT_Model*  Model;        /**<Pointer to the model to be saved by the writer*/


};