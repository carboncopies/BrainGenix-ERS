//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_ModelLoader.h>

// FIXME:
// Cleanup Doxygen, fix headers, etc.
// optionally optimize processgpu function to provide least amount of lag as possible
// Add Placeholder meshes during loading

ERS_CLASS_ModelLoader::ERS_CLASS_ModelLoader(ERS_STRUCT_SystemUtils* SystemUtils, int MaxModelLoadingThreads) {

    SystemUtils_ = SystemUtils;
    SystemUtils_->Logger_->Log("Initializing Model Loader", 5);
    FreeImage_Initialise();

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

    SystemUtils_->Logger_->Log("Creating Reference Loading Thread", 5);
    ModelRefrenceThread_ = std::thread(&ERS_CLASS_ModelLoader::ReferenceThread, this);




}

ERS_CLASS_ModelLoader::~ERS_CLASS_ModelLoader() {

    SystemUtils_->Logger_->Log("ERS_CLASS_ModelLoader Destructor Called", 6);
    FreeImage_DeInitialise();



    // Shutdown Threads
    SystemUtils_->Logger_->Log("Sending Join Command To Worker Threads", 5);
    BlockThread_.lock();
    ExitThreads_ = true;
    BlockThread_.unlock();

    SystemUtils_->Logger_->Log("Joining Worker Threads", 6);
    for (int i = 0; (long)i < (long)WorkerThreads_.size(); i++) {
        SystemUtils_->Logger_->Log(std::string(std::string("Joining Worker Thread ") + std::to_string(i)).c_str(), 3);
        WorkerThreads_[i].join();
    }
    SystemUtils_->Logger_->Log("Finished Joining Worker Threads", 6);


    SystemUtils_->Logger_->Log("Sending Join Command To Reference Thread", 5);
    BlockRefThread_.lock();
    ExitRefThread_ = true;
    BlockRefThread_.unlock();

    SystemUtils_->Logger_->Log("Joining Reference Loader Thread", 5);
    ModelRefrenceThread_.join();
    SystemUtils_->Logger_->Log("Finished Joining Reference Loader Thread", 5);


}

void ERS_CLASS_ModelLoader::WorkerThread() {

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
                std::shared_ptr<ERS_STRUCT_Model> WorkItem = WorkItems_[0];
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

void ERS_CLASS_ModelLoader::ProcessNewModels(ERS_STRUCT_Scene* ActiveScene) {

    // Check List Of Models
    for (unsigned long i = 0; i <ActiveScene->Models.size(); i++) {
        
        if ( (ActiveScene->Models[i]->IsReadyForGPU) && !(ActiveScene->Models[i]->FullyReady) ) {

            SystemUtils_->Logger_->Log(std::string(std::string("Pushing Material Information To GPU For Asset: ") + std::to_string(ActiveScene->Models[i]->AssetID)).c_str(), 4);

            ProcessGPU(ActiveScene->Models[i]);
            ActiveScene->Models[i]->FullyReady = true;

        }

    }

}

void ERS_CLASS_ModelLoader::AddModelToLoadingQueue(long AssetID, std::shared_ptr<ERS_STRUCT_Model> Model, bool FlipTextures) {

    // Log Addition
    SystemUtils_->Logger_->Log(std::string(std::string("Adding Model '") + std::to_string(AssetID) + std::string("' To Load Queue")).c_str(), 4);

    // Add To Queue
    BlockThread_.lock();

    WorkIDs_.push_back(AssetID);
    WorkItems_.push_back(Model);
    FlipTextures_.push_back(FlipTextures);
    

    BlockThread_.unlock();

}

void ERS_CLASS_ModelLoader::ProcessGPU(std::shared_ptr<ERS_STRUCT_Model> Model) {

        

    // Push Textures To GPU RAM
    for (unsigned long i = 0; i < Model->TexturesToPushToGPU_.size(); i++) {

        // Generate Texture
        unsigned int TextureID;
        glGenTextures(1, &TextureID);
        std::cout << std::endl << TextureID << std::endl;
        glBindTexture(GL_TEXTURE_2D, TextureID);

        // Set Texture Properties
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Convert FIBITMAP* To Raw Image Bytes
        unsigned char* RawImageData = Model->TexturesToPushToGPU_[i].ImageBytes;

        if (RawImageData != NULL) {
            if (Model->TexturesToPushToGPU_[i].FreeImageBackend) {
                std::cout << "1\n";
                std::cout << "Channels: " << Model->TexturesToPushToGPU_[i].Channels << std::endl;
                std::cout << "Width: " << Model->TexturesToPushToGPU_[i].Width << " Height: " << Model->TexturesToPushToGPU_[i].Height << std::endl;
                if (Model->TexturesToPushToGPU_[i].Channels == 4) {
                    std::cout << "2\n";

                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Model->TexturesToPushToGPU_[i].Width, Model->TexturesToPushToGPU_[i].Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, RawImageData);
                } else if (Model->TexturesToPushToGPU_[i].Channels == 3) {
                    std::cout << "3\n";

                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, Model->TexturesToPushToGPU_[i].Width, Model->TexturesToPushToGPU_[i].Height, 0, GL_BGR, GL_UNSIGNED_BYTE, RawImageData);
                } else if (Model->TexturesToPushToGPU_[i].Channels == 2) {
                    std::cout << "4\n";

                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG8, Model->TexturesToPushToGPU_[i].Width, Model->TexturesToPushToGPU_[i].Height, 0, GL_RG, GL_UNSIGNED_BYTE, RawImageData);
                } else if (Model->TexturesToPushToGPU_[i].Channels == 1) {
                    std::cout << "4\n";

                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, Model->TexturesToPushToGPU_[i].Width, Model->TexturesToPushToGPU_[i].Height, 0, GL_RED, GL_UNSIGNED_BYTE, RawImageData);
                } else {
                    std::cout << "5\n";

                    SystemUtils_->Logger_->Log(std::string("Texture With ID '") + Model->TexturesToPushToGPU_[i].Path + std::string("' For Model '") + Model->Name + std::string("' Has Unsupported Number Of Channels: ") + std::to_string(Model->TexturesToPushToGPU_[i].Channels), 8);
                }

                std::cout << "6\n";

            } else {
                if (Model->TexturesToPushToGPU_[i].Channels == 4) {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Model->TexturesToPushToGPU_[i].Width, Model->TexturesToPushToGPU_[i].Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, RawImageData);
                } else if (Model->TexturesToPushToGPU_[i].Channels == 3) {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Model->TexturesToPushToGPU_[i].Width, Model->TexturesToPushToGPU_[i].Height, 0, GL_RGB, GL_UNSIGNED_BYTE, RawImageData);
                } else if (Model->TexturesToPushToGPU_[i].Channels == 2) {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG, Model->TexturesToPushToGPU_[i].Width, Model->TexturesToPushToGPU_[i].Height, 0, GL_RG, GL_UNSIGNED_BYTE, RawImageData);
                } else if (Model->TexturesToPushToGPU_[i].Channels == 1) {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, Model->TexturesToPushToGPU_[i].Width, Model->TexturesToPushToGPU_[i].Height, 0, GL_RED, GL_UNSIGNED_BYTE, RawImageData);
                } else {
                    SystemUtils_->Logger_->Log(std::string("Texture With ID '") + Model->TexturesToPushToGPU_[i].Path + std::string("' For Model '") + Model->Name + std::string("' Has Unsupported Number Of Channels: ") + std::to_string(Model->TexturesToPushToGPU_[i].Channels), 8);
                }  
            }

            glGenerateMipmap(GL_TEXTURE_2D);


        } else {
            SystemUtils_->Logger_->Log("Texture Failed To Load, Cannot Push To GPU", 9);
        }



        // Unload Image Data
        if (Model->TexturesToPushToGPU_[i].FreeImageBackend) {
            FreeImage_Unload(Model->TexturesToPushToGPU_[i].ImageData);
        } else {
            stbi_image_free(Model->TexturesToPushToGPU_[i].ImageBytes);
        }

        // Append To Texture Index
        Model->OpenGLTextureIDs_.push_back(TextureID);
    }



    // Erase List To Save Memory
    Model->TexturesToPushToGPU_.erase(Model->TexturesToPushToGPU_.begin(), Model->TexturesToPushToGPU_.end());



    // Collect Vertex Count Analytics
    for (unsigned long i = 0; i < Model->Meshes.size(); i++) {
        Model->TotalVertices_ += Model->Meshes[i].Vertices.size();
    }

    // Process Texture References, Setup Meshes
    for (unsigned long i = 0; i < Model->Meshes.size(); i++) {
        for (unsigned long Index = 0; Index < Model->Meshes[i].TextureReferences_.size(); Index++) { // IF TEXTURES DONT WORK, CHECK HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

            int TextureIndex = Model->Meshes[i].TextureReferences_[Index];
        
            if (TextureIndex == -1) {
                SystemUtils_->Logger_->Log("Failed To Find Corresponding Texture", 8);
                Model->Meshes[i].TextureIDs.push_back(-1);
                Model->Meshes[i].TextureColorChannels_.push_back(0);
            } else {
                Model->Meshes[i].TextureIDs.push_back(Model->OpenGLTextureIDs_[TextureIndex]);
                Model->Meshes[i].TextureColorChannels_.push_back(Model->TexturesToPushToGPU_[TextureIndex].Channels);
            }
    

        }
        Model->Meshes[i].SetupMesh();
        // Perhaps save mem by erasing the vertices after pusning? (also indices)
    }


    Model->LoadingFinishTime_ = glfwGetTime();
    Model->TotalLoadingTime_ = Model->LoadingFinishTime_ - Model->LoadingStartTime_;
    double VertsPerSec = Model->TotalVertices_ / Model->TotalLoadingTime_;
    SystemUtils_->Logger_->Log(
        std::string("Model Loading Completed In ")
        + std::to_string(Model->TotalLoadingTime_)
        + std::string(" Seconds, ")
        + std::to_string(Model->TotalVertices_)
        + std::string(" Vertices, ")
        + std::to_string(VertsPerSec)
        + std::string(" Verts/Sec")
        ,5);


}

ERS_STRUCT_Texture ERS_CLASS_ModelLoader::LoadTexture(long ID, bool FlipTextures) {

    // Load Image Bytes Into Memory
    std::unique_ptr<ERS_STRUCT_IOData> ImageData = std::make_unique<ERS_STRUCT_IOData>();
    SystemUtils_->ERS_IOSubsystem_->ReadAsset(ID, ImageData.get());

    // Identify Image Format, Decode
    bool FreeImageLoadFail = false;
    FIMEMORY* FIImageData = FreeImage_OpenMemory(ImageData->Data.get(), ImageData->Size_B);
    FREE_IMAGE_FORMAT Format = FreeImage_GetFileTypeFromMemory(FIImageData);
    FIBITMAP* Image = FreeImage_LoadFromMemory(Format, FIImageData);
    FreeImage_CloseMemory(FIImageData);

    // Flip If Needed
    if (FlipTextures) {
        FreeImage_FlipVertical(Image);
    }

    Image = FreeImage_ConvertTo8Bits(Image);

    // Get Metadata
    ERS_STRUCT_Texture Texture;
    Texture.HasImageData = false;
    Texture.ImageData = NULL;
    float Width, Height, Channels;
    if (FreeImage_GetWidth(Image) != 0) {
        Width = FreeImage_GetWidth(Image);
        Height = FreeImage_GetHeight(Image);
        Channels = FreeImage_GetLine(Image) / FreeImage_GetWidth(Image);
    } else {
        SystemUtils_->Logger_->Log(std::string("FreeImage Error Loading Texture '") + std::to_string(ID) + std::string("' , Width/Height Are Zero Falling Back To STB_Image"), 7);
        FreeImageLoadFail = true;
    }

    // Channel Sanity Check
    if ((Channels < 1) || (Channels > 4)) {
        SystemUtils_->Logger_->Log(std::string("FreeImage Failed Identify Number Of Channels On Texture '") + std::to_string(ID) + std::string("' Falling Back To STB_Image"), 7);
        FreeImageLoadFail = true;
    }


    // If FreeImage Failed, Try STB
    if (FreeImageLoadFail) {

        int SWidth, SHeight, SChannels;
        unsigned char *ImageBytes = stbi_load_from_memory(ImageData->Data.get(), ImageData->Size_B, &SWidth, &SHeight, &SChannels, 0); 
        
        // Perform Sanity Checks
        if ((SChannels < 1) || (SChannels > 4)) {
            SystemUtils_->Logger_->Log(std::string("Fallback STB_Image Library Loading Failed On Texture '") + std::to_string(ID) + std::string("' , Image Has Invalid Number Of Channels '") + std::to_string(SChannels) + std::string("'"), 8);
            return Texture;
        }
        if ((SWidth <= 0) || (SHeight <= 0)) {
            SystemUtils_->Logger_->Log(std::string("Fallback STB_Image Library Loading Failed On Texture '") + std::to_string(ID) + std::string("' , Image Has Invalid Width/Height"), 8);
            return Texture;
        }

        // Populate Texture Struct
        Texture.Channels = SChannels;
        Texture.Height = SHeight;
        Texture.Width = SWidth;
        Texture.HasImageData = true;
        Texture.Path = std::to_string(ID);
        Texture.ID = ID;
        Texture.FreeImageBackend = false;
        Texture.ImageBytes = ImageBytes;



    } else {

        // Create Texture, Populate
        Texture.Channels = Channels;
        Texture.Height = Height;
        Texture.Width = Width;
        Texture.ImageData = Image;
        Texture.HasImageData = true;
        Texture.Path = std::to_string(ID);
        Texture.ID = ID;
        Texture.FreeImageBackend = true;
        Texture.ImageBytes = FreeImage_GetBits(Image);
    
    }

    // Return Value
    return Texture;

}

void ERS_CLASS_ModelLoader::ReferenceThread() {

    while (!ExitRefThread_) {

        // Check Reference List
        BlockRefThread_.lock();
        for (unsigned long i = 0; i < ModelsToRefrence_.size(); i++) {
            unsigned long TargetID = ModelsToRefrence_[i]->AssetID;
            long MatchIndex = CheckIfModelAlreadyLoaded(TargetID);
            if (MatchIndex != -1) {
                if (LoadedModelRefrences_[MatchIndex]->FullyReady) {


                    std::shared_ptr<ERS_STRUCT_Model> Target = ModelsToRefrence_[i];
                    std::shared_ptr<ERS_STRUCT_Model> Source = LoadedModelRefrences_[MatchIndex];



                    Target->Meshes = Source->Meshes;
                    Target->OpenGLTextureIDs_ = Source->OpenGLTextureIDs_;
                    Target->TextureIDs = Source->TextureIDs;
                    Target->TotalIndices_ = Source->TotalIndices_;
                    Target->TotalVertices_ = Source->TotalVertices_;
                    Target->TotalLoadingTime_ = Source->TotalLoadingTime_;
                    Target->FullyReady = true;

                    ModelsToRefrence_.erase(ModelsToRefrence_.begin() + i);
                    BlockRefThread_.unlock();
                    break;
                }
            }

        }
        BlockRefThread_.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(2));

    }

}

void ERS_CLASS_ModelLoader::AddModelToReferenceQueue(long AssetID, std::shared_ptr<ERS_STRUCT_Model> Model) {

    Model->AssetID = AssetID;
    ModelsToRefrence_.push_back(Model);

}


void ERS_CLASS_ModelLoader::LoadModel(long AssetID, std::shared_ptr<ERS_STRUCT_Model> Model, bool FlipTextures) {

    // Check If Already In Refs
    if (EnableReferenceLoading_) {
        BlockRefThread_.lock();
        if (CheckIfModelAlreadyLoaded(AssetID) != -1) {
            AddModelToReferenceQueue(AssetID, Model);
            BlockRefThread_.unlock();
            return;
        }
        else {
            LoadedModelRefrences_.push_back(Model);
            BlockRefThread_.unlock();
        }
    }

    // Log Loading For Debugging Purposes
    SystemUtils_->Logger_->Log(std::string(std::string("Loading Model '") + std::to_string(AssetID) + std::string("'")).c_str(), 4);
    Model->LoadingStartTime_ = glfwGetTime();

    // Read Metadata From Asset
    std::unique_ptr<ERS_STRUCT_IOData> ModelMetadata = std::make_unique<ERS_STRUCT_IOData>();
    SystemUtils_->ERS_IOSubsystem_->ReadAsset(AssetID, ModelMetadata.get());
    std::string ModelMetadataString = std::string((const char*)ModelMetadata->Data.get());
    YAML::Node Metadata = YAML::Load(ModelMetadataString);

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
    } catch(YAML::BadSubscript&) {
        SystemUtils_->Logger_->Log(std::string(std::string("Error Loading Model '") + std::to_string(AssetID) + std::string("', Asset Metadata Corrupt")).c_str(), 9);
        return;
    } catch(YAML::TypedBadConversion<long>&) {
        SystemUtils_->Logger_->Log(std::string(std::string("Error Loading Model '") + std::to_string(AssetID) + std::string("', ModelID/TextureIDs Corrupt")).c_str(), 9);
        return;        
    } catch(YAML::TypedBadConversion<std::string>&) {
        SystemUtils_->Logger_->Log(std::string(std::string("Error Loading Model '") + std::to_string(AssetID) + std::string("', Model Name Corrupt")).c_str(), 9);
        return;        
    } 

    if (Model->Name == std::string("Loading...")) {
        Model->Name = Name.substr(Name.find_last_of("/") + 1, Name.length()-1);
    }

    // Spawn Threads To Load Textures
    std::vector<std::future<ERS_STRUCT_Texture>> DecodedTextures;
    for (int i = 0; (long)i < (long)TexturePaths.size(); i++) {
        SystemUtils_->Logger_->Log(std::string(std::string("Assigning Texture To Thread With ID: ") + std::to_string(TextureIDs[i])).c_str(), 4);
        DecodedTextures.push_back(std::async(&ERS_CLASS_ModelLoader::LoadTexture, this, TextureIDs[i], FlipTextures));
    }


    // FIXME: fix the loader not matching the textures to the model
    // perhaps also add a warning message to the system so that it will log when it can't find a texture?

    // Read Mesh
    Assimp::Importer Importer;
    SystemUtils_->Logger_->Log(std::string(std::string("Loading Model With ID: ") + std::to_string(AssetID)).c_str(), 3);

    std::unique_ptr<ERS_STRUCT_IOData> ModelData = std::make_unique<ERS_STRUCT_IOData>();
    SystemUtils_->ERS_IOSubsystem_->ReadAsset(ModelID, ModelData.get());
    const aiScene* Scene = Importer.ReadFileFromMemory(ModelData->Data.get(), (int)ModelData->Size_B, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_PreTransformVertices | aiProcess_JoinIdenticalVertices, "");

    // Log Errors
    if (!Scene || Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode) {
        SystemUtils_->Logger_->Log(std::string(std::string("Model Loading Error: ") + std::string(Importer.GetErrorString())).c_str(), 10);
        Model->IsReadyForGPU = false;
        return;
    }

    // Decode Mesh, Create Texture Pointers
    ProcessNode(&(*Model), Scene->mRootNode, Scene, TexturePaths);

    // Get Texture Images From Loader, Push Into Vector
    for (unsigned long i = 0; i < DecodedTextures.size(); i++) {
        SystemUtils_->Logger_->Log(std::string(std::string("Getting Texture With ID: ") + std::to_string(TextureIDs[i])).c_str(), 4);
        Model->TexturesToPushToGPU_.push_back(DecodedTextures[i].get());
    }


    // Set Ready For GPU
    Model->IsReadyForGPU = true;
}

long ERS_CLASS_ModelLoader::CheckIfModelAlreadyLoaded(long AssetID) {

    long Index = -1;    

    // Iterate Through List OF Models Aready Loading/Loaded
    for (unsigned long i = 0; i < LoadedModelRefrences_.size(); i++) {
        LoadedModelRefrences_[i]->AssetID;
        if (LoadedModelRefrences_[i]->AssetID == AssetID) {
            Index = i;
        }
    }

    return Index;

}

void ERS_CLASS_ModelLoader::ProcessNode(ERS_STRUCT_Model* Model, aiNode *Node, const aiScene *Scene, std::vector<std::string> TexturePaths) {


    // Process Meshes In Current Node
    for (unsigned int i = 0; i < Node->mNumMeshes; i++) {
        aiMesh* Mesh = Scene->mMeshes[Node->mMeshes[i]];
        Model->Meshes.push_back(
            ProcessMesh(
                (unsigned long)Mesh->mNumVertices,
                (unsigned long)Mesh->mNumFaces*3,
                Mesh,
                Scene,
                TexturePaths
            )
        );

    }

    // Process Children Nodes
    for (unsigned int i = 0; i < Node->mNumChildren; i++) {
        ProcessNode(Model, Node->mChildren[i], Scene, TexturePaths);
    }


}

ERS_STRUCT_Mesh ERS_CLASS_ModelLoader::ProcessMesh(unsigned long PreallocVertSize, unsigned long PreallocIndSize, aiMesh *Mesh, const aiScene *Scene, std::vector<std::string> TexturePaths) {

    // Create Data Holders
    ERS_STRUCT_Mesh OutputMesh;


    OutputMesh.Vertices.reserve(PreallocVertSize);
    OutputMesh.Indices.reserve(PreallocIndSize);

    // Iterate Through Meshes' Vertices
    for (unsigned int i = 0; i < Mesh->mNumVertices; i++) {

        // Hold Vertex Data
        ERS_STRUCT_Vertex Vertex;
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
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Material, aiTextureType_AMBIENT, "texture_ambient");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Material, aiTextureType_AMBIENT_OCCLUSION, "texture_ambient_occlusion");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Material, aiTextureType_BASE_COLOR, "texture_base_color");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Material, aiTextureType_DIFFUSE, "texture_diffuse");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Material, aiTextureType_DIFFUSE_ROUGHNESS, "texture_diffuse_roughness");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Material, aiTextureType_DISPLACEMENT, "texture_displacement");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Material, aiTextureType_EMISSION_COLOR, "texture_emission_color");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Material, aiTextureType_EMISSIVE, "texture_emissive");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Material, aiTextureType_HEIGHT, "texture_height");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Material, aiTextureType_LIGHTMAP, "texture_lightmap");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Material, aiTextureType_METALNESS, "texture_metalness");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Material, aiTextureType_NONE, "texture_none");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Material, aiTextureType_NORMAL_CAMERA, "texture_normal_camera");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Material, aiTextureType_NORMALS, "texture_normals");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Material, aiTextureType_OPACITY, "texture_opacity");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Material, aiTextureType_REFLECTION, "texture_reflection");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Material, aiTextureType_SHININESS, "texture_shininess");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Material, aiTextureType_SPECULAR, "texture_specular");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Material, aiTextureType_UNKNOWN, "texture_unknown");

    // Return Populated Mesh
    return OutputMesh;

}

void ERS_CLASS_ModelLoader::LoadMaterialTextures(std::vector<int>* IDs, std::vector<std::string>* Types, std::vector<std::string> TextureList, aiMaterial *Mat, aiTextureType Type, std::string TypeName) {

    // Iterate Through Textures
    for (unsigned int i=0; i< Mat->GetTextureCount(Type); i++) {


        // Calculate Texture Path
        aiString TextureString;
        Mat->GetTexture(Type, i, &TextureString);
        std::string TextureIdentifier = std::string(std::string(TextureString.C_Str()));

        std::string Message = std::string("Model Requesting Texture Of Type '") + TypeName + std::string("' With Identifier '") + TextureIdentifier + std::string("'");
        SystemUtils_->Logger_->Log(Message, 3);

        // Search Texture List For Index Of Same Match, Add -1 If Not Found
        int Index = -1;
        for (unsigned long x = 0; x < TextureList.size(); x++) {
            if (TextureList[x] == TextureIdentifier) {
                SystemUtils_->Logger_->Log(std::string("Found Matching Texture '") + TextureList[x] + std::string("'"), 3);
                Index = x;
                break;
            }
        }

        // If Initial Search Failed To Match, Try Again By Only Checking End Of Path
        if (Index == -1) {
            SystemUtils_->Logger_->Log(std::string("Initial Model-Texture Matching Failed On Texture '") + TextureIdentifier + std::string("', Attempting Check With Substring"), 4);
            for (unsigned long x = 0; x < TextureList.size(); x++) {
                if (TextureList[x].substr(TextureList[x].find_last_of("/") + 1, TextureList[x].length()) == TextureIdentifier.substr(TextureIdentifier.find_last_of("/") + 1, TextureIdentifier.length() - 1)) {
                    SystemUtils_->Logger_->Log(std::string("Found Matching Texture During Substring Match '") + TextureList[x] + std::string("'"), 4);
                    Index = x;
                    break;
                }
            }
        }

        // If None Of Those Worked, Log Failure
        if (Index == -1) { 
            SystemUtils_->Logger_->Log(std::string("Failed To Find Suitable Texture Match, Texture Will Not Load"), 8);
        }


        // Add To Output Vert
        IDs->push_back(Index);
        Types->push_back(TypeName);
    }


}

