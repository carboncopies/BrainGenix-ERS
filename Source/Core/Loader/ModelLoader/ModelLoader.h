//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the model loader.
    Additonal Notes: None
    Date Created: 2021-11-13
*/

#pragma once


/**
 * @brief Class for loading models (fbx, gltx, etc.) based on the ASSIMP library
 * 
 */
class ModelLoader {


    public:



        // Logger
        LoggerClass *Logger_;
        TextureLoader *TextureLoader_;

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
        void LoadModelFromFile(const char* AssetPath);

        // Draw Model
        void Draw(ERS_OBJECT_SHADER &Shader);


    private:

        void ProcessNode(aiNode *Node, const aiScene *Scene);

        ERS_OBJECT_MESH ProcessMesh(aiMesh *Mesh, const aiScene *Scene);

        std::vector<ERS_OBJECT_TEXTURE_2D> LoadMaterialTextures(aiMaterial *Mat, aiTextureType Type, std::string TypeName);



};

