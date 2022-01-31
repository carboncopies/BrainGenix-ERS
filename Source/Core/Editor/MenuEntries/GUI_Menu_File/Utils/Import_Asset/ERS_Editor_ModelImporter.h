//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the model loader.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-11-13
*/

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
#include <Mesh.h>
#include <2DTexture.h>
#include <Vertex.h>
#include <FileIO.h>
#include <Model.h>

#include <ERS_STRUCT_SystemUtils.h>
#include <ERS_STRUCT_IOData.h>



/**
 * @brief Class for importing models (fbx, gltx, etc.) based on the ASSIMP library
 * 
 */
class ERS_CLASS_ModelImporter {


    private:


        std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<System Utils Pointers*/
        std::vector<std::string> TextureList_; /**<Texture List Vector*/


        /**
         * @brief Function Used To Process Subnodes Of SceneFiles.
         * 
         * @param Node 
         * @param Scene 
         */
        void ProcessNode(ERS_OBJECT_MODEL* Model, aiNode *Node, const aiScene *Scene, std::string ModelDirectory);

        /**
         * @brief Process Meshes From Model.
         * 
         * @param Mesh 
         * @param Scene 
         * @return ERS_OBJECT_MESH 
         */
        void ProcessMesh(ERS_OBJECT_MODEL* Model, aiMesh *Mesh, const aiScene *Scene, std::string ModelDirectory);

        /**
         * @brief Load Textures From Model.
         * 
         * @param Mat 
         * @param Type 
         * @param TypeName 
         */
        void AddTexture(ERS_OBJECT_MODEL* Model, aiMaterial *Mat, aiTextureType Type, std::string TypeName, std::string ModelDirectory);


        /**
         * @brief Load a file into an IOData Struct
         * 
         * @param Path 
         * @param IOData 
         */
        void ReadFile(std::string Path, std::shared_ptr<ERS_STRUCT_IOData> IOData);



    public:




        /**
         * @brief Construct a new Model Loader object
         * 
         * @param Logger 
         * @param TextureLoader 
         */
        ERS_CLASS_ModelImporter(std::shared_ptr<ERS_STRUCT_SystemUtils>);

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

