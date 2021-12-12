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

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <Mesh.h>
#include <2DTexture.h>
#include <Vertex.h>
#include <FileIO.h>
#include <TextureLoader.h>
#include <Model.h>


/**
 * @brief Class for loading models (fbx, gltx, etc.) based on the ASSIMP library
 * 
 */
class ModelLoader {


    private:

        // Internal Model Instance For Processing
        ERS_OBJECT_MODEL* Model_; /**<Model Instance for processing.*/
        std::string ModelDirectory_; /**<Current model directory being processed.*/
        bool FlipTextures_; /**<Flip Textures For current Model Being Loaded.*/

        // Logger
        std::shared_ptr<LoggerClass> Logger_; /**<Pointer to Logging System.*/
        std::shared_ptr<TextureLoader> TextureLoader_; /**<Pointer To Texture Loader Instance.*/

        /**
         * @brief Function Used To Process Subnodes Of SceneFiles.
         * 
         * @param Node 
         * @param Scene 
         */
        void ProcessNode(aiNode *Node, const aiScene *Scene);

        /**
         * @brief Process Meshes From Model.
         * 
         * @param Mesh 
         * @param Scene 
         * @return ERS_OBJECT_MESH 
         */
        ERS_OBJECT_MESH ProcessMesh(aiMesh *Mesh, const aiScene *Scene);

        /**
         * @brief Load Textures From Model.
         * 
         * @param Mat 
         * @param Type 
         * @param TypeName 
         * @return std::vector<ERS_OBJECT_TEXTURE_2D> 
         */
        std::vector<ERS_OBJECT_TEXTURE_2D> LoadMaterialTextures(aiMaterial *Mat, aiTextureType Type, std::string TypeName);


    public:



        /**
         * @brief Construct a new Model Loader object
         * 
         * @param Logger 
         * @param TextureLoader 
         */
        ModelLoader(std::shared_ptr<LoggerClass> Logger, std::shared_ptr<TextureLoader> TextureLoader);

        /**
         * @brief Destroy the Model Loader object
         * 
         */
        ~ModelLoader();


        /**
         * @brief Load Model From Given File.
         * 
         * @param AssetPath 
         * @param FlipTextures 
         * @return ERS_OBJECT_MODEL 
         */
        ERS_OBJECT_MODEL LoadModelFromFile(const char* AssetPath, bool FlipTextures = false);







};

