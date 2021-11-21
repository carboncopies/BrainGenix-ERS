//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the model loader.
    Additonal Notes: None
    Date Created: 2021-11-13
*/

#include "ModelLoader.h"


// Constructor
ModelLoader::ModelLoader(LoggerClass *Logger, TextureLoader *TexLoader) {

    // Create Local Pointer
    Logger_ = Logger;
    TextureLoader_ = TexLoader;

    // Log Initialization
    Logger_->Log("Initializing Model Loader", 5);

}

// Destructor
ModelLoader::~ModelLoader() {

    // Log Destructor Call
    Logger_->Log("ModelLoader Destructor Called", 6);

}



// Load Model From File
ERS_OBJECT_MODEL ModelLoader::LoadModelFromFile(const char* AssetPath) {


    // Clear Model Instance
    Model_ = new ERS_OBJECT_MODEL;

    // Copy AssetPath
    Model_->AssetPath_ = AssetPath;

    // Generate File Path
    std::string FilePath = std::string(Model_->AssetPath_);

    // Read File
    Assimp::Importer Importer;
    Logger_->Log(std::string(std::string("Loading Model At File Path: ") + FilePath).c_str(), 3);
    const aiScene* Scene = Importer.ReadFile(FilePath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    // Log Errors
    if (!Scene || Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode) {
        std::cout<< "ASSET IMPORT ERROR " << Importer.GetErrorString()<<std::endl; /// FIX ME - SHOULD USE ERSLOGGER
        return;
    }

    // Retrieve Directory
    //Directory = FilePath.substr(0, Path.find_last_of("/"));

    // Process Root Node Recursively
    ProcessNode(Scene->mRootNode, Scene);


}



// Process Nodes
void ModelLoader::ProcessNode(aiNode *Node, const aiScene *Scene) {

    // Process Meshes In Current Node
    for (unsigned int i = 0; i < Node->mNumMeshes; i++) {
        aiMesh* Mesh = Scene->mMeshes[Node->mMeshes[i]];
        Model_->Meshes.push_back(ProcessMesh(Mesh, Scene));
    }

    // Process Children Nodes
    for (unsigned int i = 0; i < Node->mNumChildren; i++) {
        ProcessNode(Node->mChildren[i], Scene);
    }


}

// Process Mesh
ERS_OBJECT_MESH ModelLoader::ProcessMesh(aiMesh *Mesh, const aiScene *Scene) {

    // Create Data Holders
    std::vector<ERS_OBJECT_VERTEX> Vertices;
    std::vector<unsigned int> Indices;
    std::vector<ERS_OBJECT_TEXTURE_2D> Textures;

    // Iterate Through Meshes' Vertices
    for (unsigned int i = 0; i < Mesh->mNumVertices; i++) {

        // Hold Vertex Data
        ERS_OBJECT_VERTEX Vertex;
        glm::vec3 Vector;


        Vector.x = Mesh->mVertices[i].x;
        Vector.y = Mesh->mVertices[i].y;
        Vector.z = Mesh->mVertices[i].z;
        Vertex.Position = Vector;

        if (Mesh->HasNormals())
        {
            Vector.x = Mesh->mNormals[i].x;
            Vector.y = Mesh->mNormals[i].y;
            Vector.z = Mesh->mNormals[i].z;
            Vertex.Normal = Vector;
        }

        if (Mesh->mTextureCoords[0]) {

            glm::vec2 Vec;

            // Get Texture Coordinates
            Vec.x = Mesh->mTextureCoords[0][i].x;
            Vec.y = Mesh->mTextureCoords[0][i].y;
            Vertex.TexCoords = Vec;

            // Tangent
            Vector.x = Mesh->mTangents[i].x;
            Vector.y = Mesh->mTangents[i].y;
            Vector.z = Mesh->mTangents[i].z;
            Vertex.Tangent = Vector;

            // Bitangent
            Vector.x = Mesh->mBitangents[i].x;
            Vector.y = Mesh->mBitangents[i].y;
            Vector.z = Mesh->mBitangents[i].z;
            Vertex.Bitangent = Vector;

        } else {
            Vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        }

        Vertices.push_back(Vertex);



    }

    // Iterate Through Faces
    for (unsigned int i = 0; i < Mesh->mNumFaces; i++) {

        aiFace Face = Mesh->mFaces[i];

        // Get Face Indices
        for (unsigned int j = 0; j < Face.mNumIndices; j++) {
            Indices.push_back(Face.mIndices[j]);
        }
    }

    // Process Materials
    aiMaterial* Material = Scene->mMaterials[Mesh->mMaterialIndex];

    // Diffuse Maps
    std::vector<ERS_OBJECT_TEXTURE_2D> DiffuseMaps = LoadMaterialTextures(Material, aiTextureType_DIFFUSE, "texture_diffuse");
    Textures.insert(Textures.end(), DiffuseMaps.begin(), DiffuseMaps.end());
    // 2. specular maps
    std::vector<ERS_OBJECT_TEXTURE_2D> SpecularMaps = LoadMaterialTextures(Material, aiTextureType_SPECULAR, "texture_specular");
    Textures.insert(Textures.end(), SpecularMaps.begin(), SpecularMaps.end());
    // 3. normal maps
    std::vector<ERS_OBJECT_TEXTURE_2D> NormalMaps = LoadMaterialTextures(Material, aiTextureType_NORMALS, "texture_normal");
    Textures.insert(Textures.end(), NormalMaps.begin(), NormalMaps.end());
    // 4. height maps
    std::vector<ERS_OBJECT_TEXTURE_2D> HeightMaps = LoadMaterialTextures(Material, aiTextureType_AMBIENT, "texture_height");
    Textures.insert(Textures.end(), HeightMaps.begin(), HeightMaps.end());

    // Mesh Object
    return ERS_OBJECT_MESH(Vertices, Indices, Textures);

}

// Check Material Textures
std::vector<ERS_OBJECT_TEXTURE_2D> ModelLoader::LoadMaterialTextures(aiMaterial *Mat, aiTextureType Type, std::string TypeName) {

    std::vector<ERS_OBJECT_TEXTURE_2D> Textures;
    for (unsigned int i=0; i< Mat->GetTextureCount(Type); i++) {

        aiString Str;
        Mat->GetTexture(Type, i, &Str);

        bool Skip = false;
        

        // Calculate Texture Path
        std::string FilePath = std::string(std::string("Assets") + std::string(this->Model_->Directory)  + std::string("/") + std::string(Str.C_Str()));

        // Check If Texture Already Loaded
        for (unsigned int j = 0; j < Model_->Textures_Loaded.size(); j++) {

            if (std::strcmp(Textures_Loaded[j].Path.data(), FilePath.c_str()) == 0) {
                Textures.push_back(Textures_Loaded[j]);
                Skip = true;
                break;
            }

        }
        // If Texture Not Already Loaded
        if (!Skip) {

            ERS_OBJECT_TEXTURE_2D Texture = TextureLoader_->LoadTexture(FilePath.c_str());

            Textures.push_back(Texture);
            Model_->Textures_Loaded.push_back(Texture);


        }

        

    }
    return Textures;

}


