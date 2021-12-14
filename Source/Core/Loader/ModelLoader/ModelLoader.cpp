//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the model loader.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-11-13
*/

#include <ModelLoader.h>


// Constructor
ModelLoader::ModelLoader(std::shared_ptr<LoggerClass> Logger, std::shared_ptr<TextureLoader> TexLoader, int MaxModelLoadingThreads) {

    // Create Local Pointer
    Logger_ = Logger;
    TextureLoader_ = TexLoader;

    // Log Initialization
    Logger_->Log("Initializing Model Loader", 5);
    ActiveThreadCount_ = 0;


    // Set Max Threads
    Logger_->Log(std::string(std::string("Setting Maximum Concurrent Model Loading Threads To: ") + std::to_string(MaxModelLoadingThreads)).c_str(), 4);
    MaxThreadCount_ = MaxModelLoadingThreads;

}

// Destructor
ModelLoader::~ModelLoader() {

    // Log Destructor Call
    Logger_->Log("ModelLoader Destructor Called", 6);

}

// Batch Load Models
std::map<std::string, ERS_OBJECT_MODEL> ModelLoader::BatchLoadModels(std::vector<std::string> FilePaths, std::vector<bool> FlipTextures){

    // Init
    int TotalModelCount = FilePaths.size();

    // Log Batch Load Call
    Logger_->Log(std::string(std::string("Multithreaded Model Loader BatchLoad Called With ") + std::to_string(TotalModelCount) + std::string(" Models")).c_str(), 4);

    // Vector Of Future Objects
    std::vector<std::future<ERS_OBJECT_MODEL>> Models;

    
    // Load While Respecting Active Thread Count
    int CurrentModelIndex = 0;
    while (CurrentModelIndex != TotalModelCount) {
        
        // Lock And Check Active Thread Count
        LockActiveThreadCount_->lock();
        if (ActiveThreadCount_ < MaxThreadCount_) {
            LockActiveThreadCount_->unlock();

            // Async Load Model
            std::string ModelAssetPath = FilePaths[CurrentModelIndex];
            bool FlipModelTextures = FlipTextures[CurrentModelIndex];
            Models.push_back(AsyncLoadModel(ModelAssetPath.c_str(), FlipModelTextures)); // Automatically Updates Active Thread Count

            CurrentModelIndex++;

        } else {
            LockActiveThreadCount_->unlock();
        }

    }

    
    // Create Dictionary Of Loaded Models
    std::map<std::string, ERS_OBJECT_MODEL> OutputMap;

    for (int i = 0; i < TotalModelCount; i++) {

        // Log Retrieval, Then Add To Output Dict
        Logger_->Log(std::string(std::string("Getting Model From Loading Queue With Path ") + std::string(FilePaths[i])).c_str(), 3);
        OutputMap.emplace(FilePaths[i], Models[i].get());

    }


    // Return
    return OutputMap;

}


// Async Load Model
std::future<ERS_OBJECT_MODEL> ModelLoader::AsyncLoadModel(const char* AssetPath, bool FlipTextures) {

    // Log Loading
    Logger_->Log(std::string(std::string("Creating Thread To Load Model At Path: ") + std::string(AssetPath)).c_str(), 3);

    // Lock Count
    LockActiveThreadCount_->lock();
    ActiveThreadCount_++;
    LockActiveThreadCount_->unlock();

    // Create And Return Future Object
    std::future<ERS_OBJECT_MODEL> FutureModel = std::async(&ModelLoader::LoadModelFromFile, this, std::string(AssetPath), FlipTextures, true);
    return FutureModel;
}



// Load Model From File
ERS_OBJECT_MODEL ModelLoader::LoadModelFromFile(std::string AssetPath, bool FlipTextures, bool IsThread) {

    // Clear Model Instance
    ERS_OBJECT_MODEL Model;

    // Set Texture Flip
    FlipTextures_ = FlipTextures;
    Model.FlipTextures = FlipTextures;

    // Copy AssetPath
    Model.AssetPath_ = AssetPath;

    // Get Model Path
    ModelDirectory_ = AssetPath.substr(0, std::string(AssetPath).find_last_of("/"));

    // Read File
    Assimp::Importer Importer;
    Logger_->Log(std::string(std::string("Loading Model At File Path: ") + std::string(AssetPath)).c_str(), 3);
    const aiScene* Scene = Importer.ReadFile(AssetPath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    // Log Errors
    if (!Scene || Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode) {
        Logger_->Log(std::string(std::string("Model Loading Error: ") + std::string(Importer.GetErrorString())).c_str(), 10);
        return Model;
    }

    // Process Root Node Recursively
    ProcessNode(&Model, Scene->mRootNode, Scene, IsThread);

    // If In Other Thread
    if (IsThread) {
        LockActiveThreadCount_->lock();
        ActiveThreadCount_--;
        LockActiveThreadCount_->unlock();
    }

    // Return Model Instance
    return Model;

}



// Process Nodes
void ModelLoader::ProcessNode(ERS_OBJECT_MODEL* Model, aiNode *Node, const aiScene *Scene, bool IsThread) {

    // Process Meshes In Current Node
    for (unsigned int i = 0; i < Node->mNumMeshes; i++) {
        aiMesh* Mesh = Scene->mMeshes[Node->mMeshes[i]];
        Model->Meshes.push_back(ProcessMesh(Model, Mesh, Scene, IsThread));
    }

    // Process Children Nodes
    for (unsigned int i = 0; i < Node->mNumChildren; i++) {
        ProcessNode(Model, Node->mChildren[i], Scene, IsThread);
    }


}

// Process Mesh
ERS_OBJECT_MESH ModelLoader::ProcessMesh(ERS_OBJECT_MODEL* Model, aiMesh *Mesh, const aiScene *Scene, bool IsThread) {

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


    std::vector<ERS_OBJECT_TEXTURE_2D> DiffuseMaps = LoadMaterialTextures(Model, Material, aiTextureType_DIFFUSE, "texture_diffuse", IsThread);
    Textures.insert(Textures.end(), DiffuseMaps.begin(), DiffuseMaps.end());

    std::vector<ERS_OBJECT_TEXTURE_2D> SpecularMaps = LoadMaterialTextures(Model, Material, aiTextureType_SPECULAR, "texture_specular", IsThread);
    Textures.insert(Textures.end(), SpecularMaps.begin(), SpecularMaps.end());

    std::vector<ERS_OBJECT_TEXTURE_2D> NormalMaps = LoadMaterialTextures(Model, Material, aiTextureType_NORMALS, "texture_normal", IsThread);
    Textures.insert(Textures.end(), NormalMaps.begin(), NormalMaps.end());

    std::vector<ERS_OBJECT_TEXTURE_2D> HeightMaps = LoadMaterialTextures(Model, Material, aiTextureType_AMBIENT, "texture_height", IsThread);
    Textures.insert(Textures.end(), HeightMaps.begin(), HeightMaps.end());

    // Mesh Object
    return ERS_OBJECT_MESH(Vertices, Indices, Textures);

}

// Check Material Textures
std::vector<ERS_OBJECT_TEXTURE_2D> ModelLoader::LoadMaterialTextures(ERS_OBJECT_MODEL* Model, aiMaterial *Mat, aiTextureType Type, std::string TypeName, bool IsThread) {

    std::vector<ERS_OBJECT_TEXTURE_2D> Textures;
    for (unsigned int i=0; i< Mat->GetTextureCount(Type); i++) {

        aiString Str;
        Mat->GetTexture(Type, i, &Str);

        bool Skip = false;
        

        // Calculate Texture Path
        std::string FilePath = std::string(ModelDirectory_ + std::string(Model->Directory)  + std::string("/") + std::string(Str.C_Str()));

        // Check If Texture Already Loaded
        for (unsigned int j = 0; j < Model->Textures_Loaded.size(); j++) {

            if (std::strcmp(Model->Textures_Loaded[j].Path.data(), FilePath.c_str()) == 0) {
                Textures.push_back(Model->Textures_Loaded[j]);
                Skip = true;
                break;
            }

        }
        // If Texture Not Already Loaded
        if (!Skip) {

            ERS_OBJECT_TEXTURE_2D Texture = TextureLoader_->LoadTexture(FilePath.c_str(), FlipTextures_, !IsThread);

            // Set Texture Type
            Texture.Type = TypeName;

            Textures.push_back(Texture);
            Model->Textures_Loaded.push_back(Texture);


        }

        

    }
    return Textures;

}


