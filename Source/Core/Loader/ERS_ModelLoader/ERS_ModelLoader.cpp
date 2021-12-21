//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the model loader.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-11-13
*/

#include <ERS_ModelLoader.h>


// Constructor
ERS_CLASS_ModelLoader::ERS_CLASS_ModelLoader(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, int MaxModelLoadingThreads) {

    // Create Local Pointer
    SystemUtils_ = SystemUtils;

    // Log Initialization
    SystemUtils_->Logger_->Log("Initializing Model Loader", 5);


    // Set Max Threads
    SystemUtils_->Logger_->Log(std::string(std::string("Setting Maximum Concurrent Model Loading Threads To: ") + std::to_string(MaxModelLoadingThreads)).c_str(), 4);

}

// Destructor
ERS_CLASS_ModelLoader::~ERS_CLASS_ModelLoader() {

    // Log Destructor Call
    SystemUtils_->Logger_->Log("ERS_CLASS_ModelLoader Destructor Called", 6);

}


// Updates The Current Scene, Loads In Models
void ERS_CLASS_ModelLoader::ProcessNewModels(std::shared_ptr<ERS_OBJECT_SCENE> ActiveScene) {

    // Check List Of Models Currently Loading
    std::unique_ptr<std::vector<std::shared_ptr<ERS_OBJECT_MODEL>>> ModelsCurrentlyLoading = std::make_unique<std::vector<std::shared_ptr<ERS_OBJECT_MODEL>>>(ActiveScene->ModelsLoading);
    for (int i = 0; i < ModelsCurrentlyLoading->size(); i++) {
        if ((*ModelsCurrentlyLoading)[i]->IsReadyForGPU) {
            ProcessGPU((*ModelsCurrentlyLoading)[i]);
        }
    }

}

void ERS_CLASS_ModelLoader::ProcessGPU(std::shared_ptr<ERS_OBJECT_MODEL> Model) {

}





// Load Model From File
void ERS_CLASS_ModelLoader::LoadModel(long AssetID, std::shared_ptr<ERS_OBJECT_MODEL> Model, bool FlipTextures) {

    // Clear Model Instance
    Model->FlipTextures = FlipTextures;

    std::map<std::string, ERS_OBJECT_TEXTURE_2D> PreloadedTextures_; // Stores Relative Path Of Texture As Key And Textures?
    

    // Read File
    Assimp::Importer Importer;
    SystemUtils_->Logger_->Log(std::string(std::string("Loading Model With ID: ") + std::to_string(AssetID)).c_str(), 3);

    std::shared_ptr<ERS_STRUCT_IOData> ModelData = std::make_shared<ERS_STRUCT_IOData>();
    SystemUtils_->ERS_IOSubsystem_->ReadAsset(AssetID, ModelData);
    const aiScene* Scene = Importer.ReadFileFromMemory(static_cast<const void*>(ModelData->Data.get()), ModelData->Size_B, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace, "gltf");


    //const aiScene* Scene = Importer.ReadFile(AssetPath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    // // Log Errors
    // if (!Scene || Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode) {
    //     SystemUtils_->Logger_->Log(std::string(std::string("Model Loading Error: ") + std::string(Importer.GetErrorString())).c_str(), 10);
    //     return;
    // }

    // // Process Root Node Recursively
    // ProcessNode(&(*Model), Scene->mRootNode, Scene, ModelDirectory, false);



}



// Process Nodes
void ERS_CLASS_ModelLoader::ProcessNode(ERS_OBJECT_MODEL* Model, aiNode *Node, const aiScene *Scene, std::string ModelDirectory, bool IsThread) {

    // Process Meshes In Current Node
    for (unsigned int i = 0; i < Node->mNumMeshes; i++) {
        aiMesh* Mesh = Scene->mMeshes[Node->mMeshes[i]];
        Model->Meshes.push_back(ProcessMesh(Model, Mesh, Scene, ModelDirectory, IsThread));
    }

    // Process Children Nodes
    for (unsigned int i = 0; i < Node->mNumChildren; i++) {
        ProcessNode(Model, Node->mChildren[i], Scene, ModelDirectory, IsThread);
    }


}

// Process Mesh
ERS_OBJECT_MESH ERS_CLASS_ModelLoader::ProcessMesh(ERS_OBJECT_MODEL* Model, aiMesh *Mesh, const aiScene *Scene, std::string ModelDirectory, bool IsThread) {

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


    std::vector<ERS_OBJECT_TEXTURE_2D> DiffuseMaps = LoadMaterialTextures(Model, Material, aiTextureType_DIFFUSE, "texture_diffuse", ModelDirectory, IsThread);
    Textures.insert(Textures.end(), DiffuseMaps.begin(), DiffuseMaps.end());

    std::vector<ERS_OBJECT_TEXTURE_2D> SpecularMaps = LoadMaterialTextures(Model, Material, aiTextureType_SPECULAR, "texture_specular", ModelDirectory, IsThread);
    Textures.insert(Textures.end(), SpecularMaps.begin(), SpecularMaps.end());

    std::vector<ERS_OBJECT_TEXTURE_2D> NormalMaps = LoadMaterialTextures(Model, Material, aiTextureType_NORMALS, "texture_normal", ModelDirectory, IsThread);
    Textures.insert(Textures.end(), NormalMaps.begin(), NormalMaps.end());

    std::vector<ERS_OBJECT_TEXTURE_2D> HeightMaps = LoadMaterialTextures(Model, Material, aiTextureType_AMBIENT, "texture_height", ModelDirectory, IsThread);
    Textures.insert(Textures.end(), HeightMaps.begin(), HeightMaps.end());

    // Setup Mesh And Return
    ERS_OBJECT_MESH OutputMesh;
    OutputMesh.Vertices = Vertices;
    OutputMesh.Textures = Textures;
    OutputMesh.Indices = Indices;

    if (!IsThread) { // This Calls OpenGL Parameters, Is Not Thread Safe. Must be deferred for multithreaded loading
        OutputMesh.SetupMesh();
    }
    return OutputMesh;

}

// Check Material Textures
std::vector<ERS_OBJECT_TEXTURE_2D> ERS_CLASS_ModelLoader::LoadMaterialTextures(ERS_OBJECT_MODEL* Model, aiMaterial *Mat, aiTextureType Type, std::string TypeName, std::string ModelDirectory, bool IsThread) {

    std::vector<ERS_OBJECT_TEXTURE_2D> Textures;
    for (unsigned int i=0; i< Mat->GetTextureCount(Type); i++) {

        aiString Str;
        Mat->GetTexture(Type, i, &Str);

        bool Skip = false;
        

        // Calculate Texture Path
        std::string FilePath = std::string(ModelDirectory + std::string(Model->Directory)  + std::string("/") + std::string(Str.C_Str()));

        // Check If Texture Already Loaded
        if (!IsThread) {
            for (unsigned int j = 0; j < Model->Textures_Loaded.size(); j++) {

                if (std::strcmp(Model->Textures_Loaded[j].Path.data(), FilePath.c_str()) == 0) {
                    Textures.push_back(Model->Textures_Loaded[j]);
                    Skip = true;
                    break;
                }
            }
        }

        // If Texture Not Already Loaded
        if (!Skip) {

            // ERS_OBJECT_TEXTURE_2D Texture = TextureLoader_->LoadTexture(FilePath.c_str(), FlipTextures_, !IsThread);

            // // Set Texture Type
            // Texture.Type = TypeName;

            // Textures.push_back(Texture);
            // Model->Textures_Loaded.push_back(Texture);


        }

        

    }
    return Textures;

}

