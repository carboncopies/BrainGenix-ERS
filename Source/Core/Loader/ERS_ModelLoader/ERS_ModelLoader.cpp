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
    FreeImage_Initialise();


    // Set Max Threads
    SystemUtils_->Logger_->Log(std::string(std::string("Setting Maximum Concurrent Model Loading Threads To: ") + std::to_string(MaxModelLoadingThreads)).c_str(), 4);

}

// Destructor
ERS_CLASS_ModelLoader::~ERS_CLASS_ModelLoader() {

    // Log Destructor Call
    SystemUtils_->Logger_->Log("ERS_CLASS_ModelLoader Destructor Called", 6);
    FreeImage_DeInitialise();

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

    // Push Textures To GPU RAM
    for (int i = 0; i < Model->TexturesToPushToGPU_.size(); i++) {

        // Generate Texture
        unsigned int TextureID;
        glGenTextures(1, &TextureID);
        glBindTexture(GL_TEXTURE_2D, TextureID);

        // Set Texture Properties
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Convert FIBITMAP* To Raw Image Bytes
        unsigned char* RawImageData = FreeImage_GetBits(Model->TexturesToPushToGPU_[i].ImageData);

        if (Model->TexturesToPushToGPU_[i].Channels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Model->TexturesToPushToGPU_[i].Width, Model->TexturesToPushToGPU_[i].Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, RawImageData);
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Model->TexturesToPushToGPU_[i].Width, Model->TexturesToPushToGPU_[i].Height, 0, GL_BGR, GL_UNSIGNED_BYTE, RawImageData);
        }
        glGenerateMipmap(GL_TEXTURE_2D);

        // Append To Texture Index
        Model->OpenGLTextureIDs_.push_back(TextureID);
    }

    // Erase List To Save Memory
    Model->TexturesToPushToGPU_.erase(Model->TexturesToPushToGPU_.begin(), Model->TexturesToPushToGPU_.end());

    // Setup Meshes
    for (int i = 0; i < Model->Meshes.size(); i++) {
        Model->Meshes[i].SetupMesh();
    }




}


// Loads A Texture With The Given ID
ERS_OBJECT_TEXTURE_2D ERS_CLASS_ModelLoader::LoadTexture(long ID, bool FlipTextures) {

    // Load Image Bytes Into Memory
    std::shared_ptr<ERS_STRUCT_IOData> ImageData = std::make_shared<ERS_STRUCT_IOData>();
    SystemUtils_->ERS_IOSubsystem_->ReadAsset(ID, ImageData);

    // Identify Image Format, Decode
    FIMEMORY* FIImageData = FreeImage_OpenMemory(ImageData->Data.get(), ImageData->Size_B);
    FREE_IMAGE_FORMAT Format = FreeImage_GetFileTypeFromMemory(FIImageData);
    FIBITMAP* Image = FreeImage_LoadFromMemory(Format, FIImageData);

    // Flip If Needed
    if (FlipTextures) {
        FreeImage_FlipVertical(Image);
    }

    // Get Metadata
    float Width = FreeImage_GetWidth(Image);
    float Height = FreeImage_GetHeight(Image);
    float Channels = FreeImage_GetLine(Image) / FreeImage_GetWidth(Image);

    // Create Texture, Populate
    ERS_OBJECT_TEXTURE_2D Texture;
    Texture.Channels = Channels;
    Texture.Height = Height;
    Texture.Width = Width;
    Texture.ImageData = Image;
    Texture.HasImageData = true;

    // Deallocate FIImageData (ImageData IOData Struct Should Be Automatically Destroyed When Out Of Scope)
    FreeImage_CloseMemory(FIImageData);

    // Return Value
    return Texture;

}


// Load Model From File
void ERS_CLASS_ModelLoader::LoadModel(long AssetID, std::shared_ptr<ERS_OBJECT_MODEL> Model, bool FlipTextures) {


    // Read Metadata From Asset
    std::shared_ptr<ERS_STRUCT_IOData> ModelMetadata = std::make_shared<ERS_STRUCT_IOData>();
    SystemUtils_->ERS_IOSubsystem_->ReadAsset(AssetID, ModelMetadata);
    YAML::Node Metadata = YAML::Load((const char*)ModelMetadata->Data.get());

    // Process Metadata
    std::string Name;
    long ModelID;
    std::vector<std::string> TexturePaths;
    std::vector<long> TextureIDs;
    try {
        Name = Metadata["Name"].as<std::string>();
        ModelID = Metadata["ModelID"].as<long>();
        YAML::Node TexturePathNode = Metadata["TextureIDs"];
        for (YAML::const_iterator it=TexturePathNode.begin(); it!=TexturePathNode.end(); ++it) {
            TexturePaths.push_back(it->first.as<std::string>());
            TextureIDs.push_back(it->second.as<long>());
        }
    } catch(YAML::BadSubscript) {
        SystemUtils_->Logger_->Log(std::string(std::string("Error Loading Model '") + std::to_string(AssetID) + std::string("', Asset Metadata Corrupt")).c_str(), 9);
        return;
    }


    // Spawn Threads To Load Textures
    std::vector<std::future<ERS_OBJECT_TEXTURE_2D>> DecodedTextures_;
    for (int i = 0; i < TexturePaths.size(); i++) {
        SystemUtils_->Logger_->Log(std::string(std::string("Starting Thread To Load Texture With ID: ") + std::to_string(TextureIDs[i])).c_str(), 4);
        DecodedTextures_.push_back(std::async(&ERS_CLASS_ModelLoader::LoadTexture, this, TextureIDs[i], FlipTextures));
    }


    // Read Mesh
    Assimp::Importer Importer;
    SystemUtils_->Logger_->Log(std::string(std::string("Loading Model With ID: ") + std::to_string(AssetID)).c_str(), 3);

    std::shared_ptr<ERS_STRUCT_IOData> ModelData = std::make_shared<ERS_STRUCT_IOData>();
    SystemUtils_->ERS_IOSubsystem_->ReadAsset(ModelID, ModelData);
    const aiScene* Scene = Importer.ReadFileFromMemory(ModelData->Data.get(), (int)ModelData->Size_B, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace, "");

    // Log Errors
    if (!Scene || Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode) {
        SystemUtils_->Logger_->Log(std::string(std::string("Model Loading Error: ") + std::string(Importer.GetErrorString())).c_str(), 10);
        return;
    }

    // Decode Mesh, Create Texture Pointers
    ProcessNode(&(*Model), Scene->mRootNode, Scene, TexturePaths);

    // Get Texture Images From Loader, Push Into Vector
    for (int i = 0; i < DecodedTextures_.size(); i++) {
        SystemUtils_->Logger_->Log(std::string(std::string("Getting Texture With ID: ") + std::to_string(TextureIDs[i])).c_str(), 4);
        Model->TexturesToPushToGPU_.push_back(DecodedTextures_[i].get());
    }


    // Set Ready For GPU
    Model->IsReadyForGPU = true;
}



// Process Nodes
void ERS_CLASS_ModelLoader::ProcessNode(ERS_OBJECT_MODEL* Model, aiNode *Node, const aiScene *Scene, std::vector<std::string> TexturePaths) {

    // Process Meshes In Current Node
    for (unsigned int i = 0; i < Node->mNumMeshes; i++) {
        aiMesh* Mesh = Scene->mMeshes[Node->mMeshes[i]];
        Model->Meshes.push_back(ProcessMesh(Model, Mesh, Scene, TexturePaths));
    }

    // Process Children Nodes
    for (unsigned int i = 0; i < Node->mNumChildren; i++) {
        ProcessNode(Model, Node->mChildren[i], Scene, TexturePaths);
    }


}

// Process Mesh
ERS_OBJECT_MESH ERS_CLASS_ModelLoader::ProcessMesh(ERS_OBJECT_MODEL* Model, aiMesh *Mesh, const aiScene *Scene, std::vector<std::string> TexturePaths) {

    // Create Data Holders
    ERS_OBJECT_MESH OutputMesh;

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

        OutputMesh.Vertices.push_back(Vertex);



    }

    // Iterate Through Faces
    for (unsigned int i = 0; i < Mesh->mNumFaces; i++) {

        aiFace Face = Mesh->mFaces[i];

        // Get Face Indices
        for (unsigned int j = 0; j < Face.mNumIndices; j++) {
            OutputMesh.Indices.push_back(Face.mIndices[j]);
        }
    }

    // Process Materials
    aiMaterial* Material = Scene->mMaterials[Mesh->mMaterialIndex];
    std::vector<int> DiffuseMaps = LoadMaterialTextures(TexturePaths, Model, Material, aiTextureType_DIFFUSE, "texture_diffuse");
    OutputMesh.TextureReferences_.insert(OutputMesh.TextureReferences_.end(), DiffuseMaps.begin(), DiffuseMaps.end());
    std::vector<int> SpecularMaps = LoadMaterialTextures(TexturePaths, Model, Material, aiTextureType_SPECULAR, "texture_specular");
    OutputMesh.TextureReferences_.insert(OutputMesh.TextureReferences_.end(), SpecularMaps.begin(), SpecularMaps.end());
    std::vector<int> NormalMaps = LoadMaterialTextures(TexturePaths, Model, Material, aiTextureType_NORMALS, "texture_normal");
    OutputMesh.TextureReferences_.insert(OutputMesh.TextureReferences_.end(), NormalMaps.begin(), NormalMaps.end());
    std::vector<int> HeightMaps = LoadMaterialTextures(TexturePaths, Model, Material, aiTextureType_AMBIENT, "texture_height");
    OutputMesh.TextureReferences_.insert(OutputMesh.TextureReferences_.end(), HeightMaps.begin(), HeightMaps.end());

    // Return Populated Mesh
    return OutputMesh;

}

// Check Material Textures
std::vector<int> ERS_CLASS_ModelLoader::LoadMaterialTextures(std::vector<std::string> TextureList, ERS_OBJECT_MODEL* Model, aiMaterial *Mat, aiTextureType Type, std::string TypeName) {

    // Output Vector
    std::vector<int> OutputVector;

    // Iterate Through Textures
    for (unsigned int i=0; i< Mat->GetTextureCount(Type); i++) {


        // Calculate Texture Path
        aiString TextureString;
        Mat->GetTexture(Type, i, &TextureString);
        std::string TextureIdentifier = std::string(std::string(Model->Directory)  + std::string("/") + std::string(TextureString.C_Str()));

        // Search Texture List For Index Of Same Match, Add -1 If Not Found
        int Index = -1;
        for (int i = 0; i < TextureList.size(); i++) {
            if (TextureList[i] == TextureIdentifier) {
                Index = i;
                break;
            }
        }

        // Add To Output Vert
        OutputVector.push_back(Index);
    }

    // Return Output
    return OutputVector;

}

