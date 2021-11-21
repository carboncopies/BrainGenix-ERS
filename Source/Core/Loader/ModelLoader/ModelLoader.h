//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the model loader.
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

        // Logger
        LoggerClass *Logger_;
        TextureLoader *TextureLoader_;

        // Internal Functions
        void ProcessNode(aiNode *Node, const aiScene *Scene);
        ERS_OBJECT_MESH ProcessMesh(aiMesh *Mesh, const aiScene *Scene);
        std::vector<ERS_OBJECT_TEXTURE_2D> LoadMaterialTextures(aiMaterial *Mat, aiTextureType Type, std::string TypeName);


    public:



        /**
         * @brief Construct a new Model Loader object
         * 
         * @param Logger 
         * @param TextureLoader 
         */
        ModelLoader(LoggerClass* Logger, TextureLoader *TextureLoader);

        /**
         * @brief Destroy the Model Loader object
         * 
         */
        ~ModelLoader();


        // Load Model From File
        ERS_OBJECT_MODEL LoadModelFromFile(const char* AssetPath);







};

