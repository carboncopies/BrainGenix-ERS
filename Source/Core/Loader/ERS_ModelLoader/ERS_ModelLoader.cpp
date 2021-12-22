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

// FIXME:
// Cleanup Doxygen, fix headers, etc.
// optionally optimize processgpu function to provide least amount of lag as possible
// Add Placeholder meshes during loading

// Constructor
ERS_CLASS_ModelLoader::ERS_CLASS_ModelLoader(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, int MaxModelLoadingThreads) {

    // Create Local Pointer
    SystemUtils_ = SystemUtils;

    // Log Initialization
    SystemUtils_->Logger_->Log("Initializing Model Loader", 5);
    FreeImage_Initialise();

    // Create Worker Threads
    if (MaxModelLoadingThreads == -1) {
        SystemUtils_->Logger_->Log("Identifying Number Of CPU Cores", 4);
        MaxModelLoadingThreads = std::thread::hardware_concurrency();
    SystemUtils_->Logger_->Log(std::string(std::string("Identified ") + std::to_string(MaxModelLoadingThreads) + std::string(" Cores")).c_str(), 4);

        
    }
    SystemUtils_->Logger_->Log(std::string(std::string("Creating ") + std::to_string(MaxModelLoadingThreads) + std::string("Model Loading Threads")).c_str(), 4);
    for (int i = 0; i < MaxModelLoadingThreads; i++) {
        SystemUtils_->Logger_->Log(std::string(std::string("Creating Worker Thread ") + std::to_string(i)).c_str(), 3);
        WorkerThreads_.push_back(std::thread(&ERS_CLASS_ModelLoader::WorkerThread, this));
    }

}

// Destructor
ERS_CLASS_ModelLoader::~ERS_CLASS_ModelLoader() {

    // Log Destructor Call
    SystemUtils_->Logger_->Log("ERS_CLASS_ModelLoader Destructor Called", 6);
    FreeImage_DeInitialise();

    // Shutdown Threads
    SystemUtils_->Logger_->Log("Sending Join Command To Worker Threads", 5);
    BlockThread_.lock();
    ExitThreads_ = true;
    BlockThread_.unlock();

    SystemUtils_->Logger_->Log("Joining Worker Threads", 6);
    for (int i = 0; i < WorkerThreads_.size(); i++) {
        SystemUtils_->Logger_->Log(std::string(std::string("Joining Worker Thread ") + std::to_string(i)).c_str(), 3);
        WorkerThreads_[i].join();
    }
    SystemUtils_->Logger_->Log("Finished Joining Worker Threads", 6);

}

// Worker Thread
void ERS_CLASS_ModelLoader::WorkerThread() {


    // Enter Loop
    bool ThreadShouldRun = true;
    while (ThreadShouldRun) {

        // Acquire Check Lock
        BlockThread_.lock();
        if (ExitThreads_) {
            ThreadShouldRun = false;
            BlockThread_.unlock();
        } else {

            // Check If Items In Work Queue
            int Size = WorkItems_.size();
            if (Size > 0) {

                // Get Item, Remove From Queue, Unlock
                std::shared_ptr<ERS_OBJECT_MODEL> WorkItem = WorkItems_[0];
                long WorkID = WorkIDs_[0];
                bool FlipTexture = FlipTextures_[0];

                WorkItems_.erase(WorkItems_.begin());
                WorkIDs_.erase(WorkIDs_.begin());
                FlipTextures_.erase(FlipTextures_.begin());

                BlockThread_.unlock();

                // Process Item
                LoadModel(WorkID, WorkItem, FlipTexture);

            } else {
                
                // No Work Items, Unlock Mutex, Sleep Thread
                BlockThread_.unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(20));

            }
        }


    }

}

// Updates The Current Scene, Loads In Models
void ERS_CLASS_ModelLoader::ProcessNewModels(std::shared_ptr<ERS_OBJECT_SCENE> ActiveScene) {

    // Check List Of Models
    std::unique_ptr<std::vector<std::shared_ptr<ERS_OBJECT_MODEL>>> Models = std::make_unique<std::vector<std::shared_ptr<ERS_OBJECT_MODEL>>>(ActiveScene->Models);

    for (int i = 0; i < Models->size(); i++) {

        if ( ((*Models)[i]->IsReadyForGPU) && !((*Models)[i]->FullyReady) ) {

            SystemUtils_->Logger_->Log(std::string(std::string("Pushing Material Information To GPU For Asset: ") + std::to_string((*Models)[i]->AssetID)).c_str(), 4);

            ProcessGPU((*Models)[i]);
            (*Models)[i]->FullyReady = true;

        }

    }

}

// Add Model To Load Queue
void ERS_CLASS_ModelLoader::AddModelToLoadingQueue(long AssetID, std::shared_ptr<ERS_OBJECT_MODEL> Model, bool FlipTextures) {

    // Log Addition
    SystemUtils_->Logger_->Log(std::string(std::string("Adding Model '") + std::to_string(AssetID) + std::string("' To Load Queue")).c_str(), 4);

    // Add To Queue
    BlockThread_.lock();

    WorkIDs_.push_back(AssetID);
    WorkItems_.push_back(Model);
    FlipTextures_.push_back(FlipTextures);

    BlockThread_.unlock();

}

// Process GPU Data (Must Be Done In Thread With OPENGL Context (should be main thread))
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

        // Unload Image Data
        FreeImage_Unload(Model->TexturesToPushToGPU_[i].ImageData);

        // Append To Texture Index
        Model->OpenGLTextureIDs_.push_back(TextureID);
    }

    // Erase List To Save Memory
    Model->TexturesToPushToGPU_.erase(Model->TexturesToPushToGPU_.begin(), Model->TexturesToPushToGPU_.end());

    // Process Texture References, Setup Meshes
    for (int i = 0; i < Model->Meshes.size(); i++) {
        for (int Index = 0; Index < Model->Meshes[i].TextureReferences_.size(); Index++) { // IF TEXTURES DONT WORK, CHECK HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

            int TextureIndex = Model->Meshes[i].TextureReferences_[Index];
        
            if (TextureIndex == -1) {
                SystemUtils_->Logger_->Log("Failed To Find Corresponding Texture", 8);
                Model->Meshes[i].TextureIDs.push_back(-1);
            } else {
                Model->Meshes[i].TextureIDs.push_back(Model->OpenGLTextureIDs_[TextureIndex]);
            }
    

        }
        Model->Meshes[i].UseNewSystem = true;
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

    // Log Loading For Debugging Purposes
    SystemUtils_->Logger_->Log(std::string(std::string("Loading Model '") + std::to_string(AssetID) + std::string("'")).c_str(), 4);


    // Read Metadata From Asset
    std::shared_ptr<ERS_STRUCT_IOData> ModelMetadata = std::make_shared<ERS_STRUCT_IOData>();
    SystemUtils_->ERS_IOSubsystem_->ReadAsset(AssetID, ModelMetadata);
    std::string ModelMetadataString = std::string((const char*)ModelMetadata->Data.get());
    YAML::Node Metadata = YAML::Load(ModelMetadataString.substr(0, ModelMetadataString.size()-1));

    std::cout<<Metadata<<std::endl;
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
            std::cout<<"ModelID: "<<ModelID<<" Texid: "<<it->second.as<long>()<<std::endl;
        }
    } catch(YAML::BadSubscript) {
        SystemUtils_->Logger_->Log(std::string(std::string("Error Loading Model '") + std::to_string(AssetID) + std::string("', Asset Metadata Corrupt")).c_str(), 9);
        return;
    } catch(YAML::TypedBadConversion<long>) {
        SystemUtils_->Logger_->Log(std::string(std::string("Error Loading Model '") + std::to_string(AssetID) + std::string("', ModelID/TextureIDs Corrupt")).c_str(), 9);
        return;        
    } catch(YAML::TypedBadConversion<std::string>) {
        SystemUtils_->Logger_->Log(std::string(std::string("Error Loading Model '") + std::to_string(AssetID) + std::string("', Model Name Corrupt")).c_str(), 9);
        return;        
    } 


    // Spawn Threads To Load Textures
    std::vector<std::future<ERS_OBJECT_TEXTURE_2D>> DecodedTextures;
    for (int i = 0; i < TexturePaths.size(); i++) {
        SystemUtils_->Logger_->Log(std::string(std::string("Starting Thread To Load Texture With ID: ") + std::to_string(TextureIDs[i])).c_str(), 4);
        DecodedTextures.push_back(std::async(&ERS_CLASS_ModelLoader::LoadTexture, this, TextureIDs[i], FlipTextures));
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
        Model->IsReadyForGPU = false;
        return;
    }

    // Decode Mesh, Create Texture Pointers
    ProcessNode(&(*Model), Scene->mRootNode, Scene, TexturePaths);

    // Get Texture Images From Loader, Push Into Vector
    for (int i = 0; i < DecodedTextures.size(); i++) {
        SystemUtils_->Logger_->Log(std::string(std::string("Getting Texture With ID: ") + std::to_string(TextureIDs[i])).c_str(), 4);
        Model->TexturesToPushToGPU_.push_back(DecodedTextures[i].get());
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
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Model, Material, aiTextureType_DIFFUSE, "texture_diffuse");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Model, Material, aiTextureType_SPECULAR, "texture_specular");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Model, Material, aiTextureType_NORMALS, "texture_normal");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Model, Material, aiTextureType_AMBIENT, "texture_height");

    // Return Populated Mesh
    return OutputMesh;

}

// Check Material Textures
void ERS_CLASS_ModelLoader::LoadMaterialTextures(std::vector<int>* IDs, std::vector<std::string>* Types, std::vector<std::string> TextureList, ERS_OBJECT_MODEL* Model, aiMaterial *Mat, aiTextureType Type, std::string TypeName) {

    // Iterate Through Textures
    for (unsigned int i=0; i< Mat->GetTextureCount(Type); i++) {


        // Calculate Texture Path
        aiString TextureString;
        Mat->GetTexture(Type, i, &TextureString);
        std::string TextureIdentifier = std::string(std::string(TextureString.C_Str()));

        // Search Texture List For Index Of Same Match, Add -1 If Not Found
        int Index = -1;
        for (int x = 0; x < TextureList.size(); x++) {
            if (TextureList[x] == TextureIdentifier) {
                Index = x;
                break;
            }
        }

        // Add To Output Vert
        IDs->push_back(Index);
        Types->push_back(TypeName);
    }


}

