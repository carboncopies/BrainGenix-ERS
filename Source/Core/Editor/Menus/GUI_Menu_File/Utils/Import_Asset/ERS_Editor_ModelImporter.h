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