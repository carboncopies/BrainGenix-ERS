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
#include <filesystem>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <FreeImage.h>

#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_Mesh.h>
#include <ERS_STRUCT_Texture.h>
#include <ERS_STRUCT_Vertex.h>
#include <ERS_STRUCT_Model.h>

#include <ERS_STRUCT_SystemUtils.h>
#include <ERS_STRUCT_IOData.h>



/**
 * @brief Class for importing models (fbx, gltx, etc.) based on the ASSIMP library
 * 
 */
class ERS_CLASS_ModelImporter {


private:


    ERS_STRUCT_SystemUtils* SystemUtils_; /**<System Utils Pointers*/
    std::vector<std::string> TextureList_; /**<Texture List Vector*/
    std::vector<std::string> TextureNames_; /**<List of names of the textures*/
    std::vector<std::string> TextureTypes_; /**<Types of the textures in the texture list*/


    /**
     * @brief Function Used To Process Subnodes Of SceneFiles.
     * 
     * @param Node 
     * @param Scene 
     */
    void ProcessNode(ERS_STRUCT_Model* Model, aiNode *Node, const aiScene *Scene, std::string ModelDirectory);

    /**
     * @brief Process Meshes From Model.
     * 
     * @param Mesh 
     * @param Scene 
     * @return ERS_STRUCT_Mesh 
     */
    ERS_STRUCT_Mesh ProcessMesh(ERS_STRUCT_Model* Model, aiMesh *Mesh, const aiScene *Scene, std::string ModelDirectory);

    /**
     * @brief Load Textures From Model.
     * 
     * @param Mat 
     * @param Type 
     * @param TypeName 
     */
    void AddTexture(ERS_STRUCT_Model* Model, aiMaterial *Mat, aiTextureType Type, std::string TypeName, std::string ModelDirectory);


    /**
     * @brief Load a file into an IOData Struct
     * 
     * @param Path 
     * @param IOData 
     */
    bool ReadFile(std::string Path, ERS_STRUCT_IOData* IOData);

    /**
     * @brief Decodes and writes resized textures into the ERS project file.
     * 
     * @param Model
     * @param TextureMemorySizes 
     * @param ImageAssetIDs 
     * @param ImageResolutions 
     * @param ImageChannels
     * @param AssetPath 
     * @param Format 
     * @param MipMaps 
     */
    void WriteTextures(ERS_STRUCT_Model* Model, std::vector<std::vector<int>>* TextureMemorySizes, std::vector<std::vector<long>>* ImageAssetIDs, std::vector<std::vector<std::pair<int, int>>>* ImageResolutions, std::vector<std::vector<int>>* ImageChannels, std::string AssetPath, FREE_IMAGE_FORMAT Format = FIF_PNG, int MipMaps = 10);

    /**
     * @brief Calculates the bounding box of the model and it's offset
     * 
     * @param Model
     */
    void DetectBoundingBox(ERS_STRUCT_Model* Model);

    /**
     * @brief Sets metadata parameters for number of vertices and indices in the model
     * 
     * @param Model 
     */
    void CalculateTotalVertsIndices(ERS_STRUCT_Model* Model);

    /**
     * @brief Here, we reduce the number of textures or convert into the expected ERS system
     * For example, alpha maps are baked into the diffuse map.
     * 
     * @param Model 
     */
    void MergeTextures(ERS_STRUCT_Model* Model, std::vector<std::pair<std::string, FIBITMAP*>>* LoadedTextures);

    /**
     * @brief Handles sorting out the mesh's requested materials
     * 
     * @param Model 
     * @param Material 
     * @param ModelDirectory 
     */
    void HandleMeshTextures(ERS_STRUCT_Model* Model, aiMaterial* Material, std::string ModelDirectory);

public:




    /**
     * @brief Construct a new Model Loader object
     * 
     * @param Logger 
     * @param TextureLoader 
     */
    ERS_CLASS_ModelImporter(ERS_STRUCT_SystemUtils*);

    /**
     * @brief Destroy the Model Loader object
     * 
     */
    ~ERS_CLASS_ModelImporter();


    /**
     * @brief Import model from given path, return assetID of model metadata.
     * 
     * @param AssetPath 
     * @param FlipTextures 
     * @return std::vector<long> 
     */
    long ImportModel(std::string AssetPath);

};