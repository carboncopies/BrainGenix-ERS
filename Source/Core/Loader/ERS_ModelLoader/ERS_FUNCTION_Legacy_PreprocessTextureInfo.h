//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <future>
#include <thread>
#include <chrono>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <FreeImage.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_Mesh.h>
#include <ERS_STRUCT_Texture.h>
#include <ERS_STRUCT_Vertex.h>
#include <ERS_STRUCT_Model.h>

#include <ERS_STRUCT_SystemUtils.h>







void ERS_FUNCTION_Legacy_PreprocessTextureInfo(YAML::Node Metadata, ERS_STRUCT_Model* Model, ERS_STRUCT_SystemUtils* SystemUtils, long AssetID, bool LogEnable);




/**
 * @brief Load a texture given the id
 * 
 * @param ID 
 * @param FlipTextures 
 * @return ERS_STRUCT_Texture 
 */
ERS_STRUCT_Texture ERS_LEGACY_FUNCTION_LoadTexture(long ID, bool FlipTextures = false);

/**
 * @brief Populates Texture Request Information For The Mesh
 * 
 * @param Mat 
 * @param Mesh 
 */
void ERS_LEGACY_FUNCTION_IdentifyMeshTextures(aiMaterial* Mat, ERS_STRUCT_Mesh* Mesh);




/**
 * @brief Function Used To Process Subnodes Of SceneFiles.
 * 
 * @param Node 
 * @param Scene 
 */
void ProcessNode(ERS_STRUCT_Model* Model, aiNode *Node, const aiScene *Scene);

/**
 * @brief Process Meshes From Model.
 * 
 * @param Model
 * @param Mesh 
 * @param Scene 
 * @return ERS_STRUCT_Mesh 
 */
ERS_STRUCT_Mesh ProcessMesh(ERS_STRUCT_Model* Model, unsigned long PreallocVertSize, unsigned long PerallocIndSize, aiMesh *Mesh, const aiScene *Scene);








/**
 * @brief Creates texture pointers within the model's meshes
 * 
 * @param Model 
 */
void MatchTextures(ERS_STRUCT_Model* Model);


