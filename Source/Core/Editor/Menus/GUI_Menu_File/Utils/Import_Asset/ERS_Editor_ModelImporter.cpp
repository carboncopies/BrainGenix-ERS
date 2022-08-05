//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_Editor_ModelImporter.h>


ERS_CLASS_ModelImporter::ERS_CLASS_ModelImporter(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;

}

ERS_CLASS_ModelImporter::~ERS_CLASS_ModelImporter() {

}


void ERS_CLASS_ModelImporter::DetectBoundingBox(ERS_STRUCT_Model* Model) {

    // Calculate Bounding Box
    glm::vec3 ModelMinXYZ = Model->Meshes[0].Vertices[0].Position;
    glm::vec3 ModelMaxXYZ = Model->Meshes[0].Vertices[0].Position;
    for (unsigned int MeshIndex = 0; MeshIndex < Model->Meshes.size(); MeshIndex++) {

        for (unsigned int VertIndex = 0; VertIndex < Model->Meshes[MeshIndex].Vertices.size(); VertIndex++) {

            // Get Mesh Min/Max
            glm::vec3 VertPos = Model->Meshes[MeshIndex].Vertices[VertIndex].Position;

            // Check If Larger/Smaller Than Model Min/Max
            if (VertPos.x < ModelMinXYZ.x) {
                ModelMinXYZ.x = VertPos.x;
            }
            if (VertPos.y < ModelMinXYZ.y) {
                ModelMinXYZ.y = VertPos.y;
            }
            if (VertPos.z < ModelMinXYZ.z) {
                ModelMinXYZ.z = VertPos.z;
            }
            if (VertPos.x > ModelMaxXYZ.x) {
                ModelMaxXYZ.x = VertPos.x;
            }
            if (VertPos.y > ModelMaxXYZ.y) {
                ModelMaxXYZ.y = VertPos.y;
            }
            if (VertPos.z > ModelMaxXYZ.z) {
                ModelMaxXYZ.z = VertPos.z;
            }

        }
    }
    Model->BoxScale_ = ModelMaxXYZ - ModelMinXYZ;
    Model->BoxOffset_ = (Model->BoxScale_ / 2.0f) + ModelMinXYZ;

    std::string LogMsg = std::string("Calculated Model Bounding Box To Be '") 
    + std::to_string(Model->BoxScale_.x) + "X, "
    + std::to_string(Model->BoxScale_.y) + "Y, "
    + std::to_string(Model->BoxScale_.z) + "Z' With Offset Of '"
    + std::to_string(Model->BoxOffset_.x) + "X, "
    + std::to_string(Model->BoxOffset_.y) + "Y, "
    + std::to_string(Model->BoxOffset_.z) + "Z'";
    SystemUtils_->Logger_->Log(LogMsg, 3);

}

void ERS_CLASS_ModelImporter::CalculateTotalVertsIndices(ERS_STRUCT_Model* Model) {

    // Get Vert/Indice Metadata Info
    Model->TotalVertices_ = 0;
    Model->TotalIndices_ = 0;

    for (unsigned long i = 0; i < Model->Meshes.size(); i++) {

        unsigned long VertSize = Model->Meshes[i].Vertices.size();
        unsigned long IndSize = Model->Meshes[i].Indices.size();
        Model->TotalVertices_ += VertSize;
        Model->TotalIndices_ += IndSize;

    }

}

// Load Model From File
long ERS_CLASS_ModelImporter::ImportModel(std::string AssetPath) {

    ERS_STRUCT_Model Model;
    TextureList_ = std::vector<std::string>();

    // Get Model Path
    std::string ModelDirectory = AssetPath.substr(0, std::string(AssetPath).find_last_of("/"));
    std::string ModelFileName = AssetPath.substr(AssetPath.find_last_of("/") + 1, AssetPath.size() - 1);

    // Read File
    Assimp::Importer Importer;
    SystemUtils_->Logger_->Log(std::string(std::string("Loading Model At File Path: ") + std::string(AssetPath)).c_str(), 3);
    const aiScene* Scene = Importer.ReadFile(AssetPath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_PreTransformVertices | aiProcess_JoinIdenticalVertices);

    // Log Errors
    if (!Scene || Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode) {
        SystemUtils_->Logger_->Log(std::string(std::string("Model Loading Error: ") + std::string(Importer.GetErrorString())).c_str(), 10);
        return -1;
    }

    // Process Root Node Recursively, Identify Textures/Files
    ProcessNode(&Model, Scene->mRootNode, Scene, ModelDirectory);
    DetectBoundingBox(&Model);
    CalculateTotalVertsIndices(&Model);

    // Copy Model File
    std::unique_ptr<ERS_STRUCT_IOData> Data = std::make_unique<ERS_STRUCT_IOData>();
    ReadFile(AssetPath, Data.get());
    long ModelID = SystemUtils_->ERS_IOSubsystem_->AllocateAssetID();
    SystemUtils_->Logger_->Log(std::string(std::string("Assigning ID '") + std::to_string(ModelID) + std::string("' To Model '") + AssetPath + std::string("'")).c_str(), 4);
    SystemUtils_->ERS_IOSubsystem_->WriteAsset(ModelID, Data.get());    

    // Set Textures
    std::vector<std::vector<int>> TextureMemorySizes;
    std::vector<std::vector<long>> ImageAssetIDs;
    std::vector<std::vector<std::pair<int, int>>> ImageResolutions;
    std::vector<std::vector<int>> ImageChannels;
    WriteTextures(&Model, &TextureMemorySizes, &ImageAssetIDs, &ImageResolutions, &ImageChannels, AssetPath);

    // Generate Metadata
    YAML::Emitter MetadataEmitter;
    MetadataEmitter<<YAML::BeginMap;

    MetadataEmitter<<YAML::Key<<"Name"<<YAML::Value<<AssetPath;
    MetadataEmitter<<YAML::Key<<"FormatVersion"<<YAML::Value<<"0.0.1";
    MetadataEmitter<<YAML::Key<<"ModelID"<<YAML::Value<<ModelID;




    MetadataEmitter<<YAML::Key<<"Textures";
    MetadataEmitter<<YAML::Key<<YAML::BeginMap;

    // Iterate Over All Textures
    for (unsigned int i = 0; i < TextureList_.size(); i++) {

        // Set Path For Each Texture, Iterate OVer All Levels Of This Texture
        MetadataEmitter<<YAML::Key<<TextureList_[i].substr(TextureList_[i].find_last_of("/")+1, TextureList_[i].size()-(TextureList_[i].find_last_of("/")+1))<<YAML::Value<<YAML::BeginMap;
        for (unsigned int TextureLevel = 0; TextureLevel < TextureMemorySizes[i].size(); TextureLevel++) {
            MetadataEmitter<<YAML::Key<<(TextureMemorySizes[i].size() - 1) - TextureLevel<<YAML::Value<<YAML::BeginMap;

            MetadataEmitter<<YAML::Key<<"TextureLevelAssetID"<<YAML::Value<<ImageAssetIDs[i][TextureLevel];
            MetadataEmitter<<YAML::Key<<"TextureLevelMemorySizeBytes"<<YAML::Value<<TextureMemorySizes[i][TextureLevel];
            MetadataEmitter<<YAML::Key<<"TextureLevelResolutionX"<<YAML::Value<<ImageResolutions[i][TextureLevel].first;
            MetadataEmitter<<YAML::Key<<"TextureLevelResolutionY"<<YAML::Value<<ImageResolutions[i][TextureLevel].second;
            MetadataEmitter<<YAML::Key<<"TextureLevelNumberChannels"<<YAML::Value<<ImageChannels[i][TextureLevel];

            MetadataEmitter<<YAML::EndMap;
        }
        MetadataEmitter<<YAML::EndMap;
    }
    MetadataEmitter<<YAML::EndMap;


    // Write Vert Info
    MetadataEmitter<<YAML::Key<<"Vertices"<<YAML::Value<<Model.TotalVertices_;
    MetadataEmitter<<YAML::Key<<"Indices"<<YAML::Value<<Model.TotalIndices_;

    // Write Bounding Box + Offset Info
    MetadataEmitter<<YAML::Key<<"BoundingBoxX"<<YAML::Value<<Model.BoxScale_.x;
    MetadataEmitter<<YAML::Key<<"BoundingBoxY"<<YAML::Value<<Model.BoxScale_.y;
    MetadataEmitter<<YAML::Key<<"BoundingBoxZ"<<YAML::Value<<Model.BoxScale_.z;
    MetadataEmitter<<YAML::Key<<"OffsetX"<<YAML::Value<<Model.BoxOffset_.x;
    MetadataEmitter<<YAML::Key<<"OffsetY"<<YAML::Value<<Model.BoxOffset_.y;
    MetadataEmitter<<YAML::Key<<"OffsetZ"<<YAML::Value<<Model.BoxOffset_.z;
    
    MetadataEmitter<<YAML::EndMap;


    // Write Metadata
    std::string Metadata = std::string(MetadataEmitter.c_str());
    Data->Data.reset(new unsigned char[Metadata.size()]);
    Data->Size_B = Metadata.size();
    memcpy(Data->Data.get(), Metadata.c_str(), Metadata.size());

    // Set Metadata (FIXME: Save Modification Date + Creation Date Here!)
    Data->AssetTypeName = "Model";
    Data->AssetFileName = ModelFileName;
    Data->AssetCreationDate = SystemUtils_->ERS_IOSubsystem_->GetCurrentTime();

    long MetadataID = SystemUtils_->ERS_IOSubsystem_->AllocateAssetID();
    SystemUtils_->Logger_->Log(std::string(std::string("Assigning ID '") + std::to_string(MetadataID) + std::string("' To Model Metadata")).c_str(), 4);
    SystemUtils_->Logger_->Log("Done Importing Model", 5);
    SystemUtils_->ERS_IOSubsystem_->WriteAsset(MetadataID, Data.get());
    
    return MetadataID;
}

FIBITMAP* FindTextureBitmap(std::string TexturePath, std::vector<std::pair<std::string, FIBITMAP*>>* LoadedTextures) {

    // Iterate Over Array, Try And Find Match
    for (unsigned int LoadedTextureIndex = 0; LoadedTextureIndex < LoadedTextures->size(); LoadedTextureIndex++) {
        if ((*LoadedTextures)[LoadedTextureIndex].first == TexturePath) {
            return (*LoadedTextures)[LoadedTextureIndex].second;
        }
    }

    // Return NULL On Failure
    return NULL;
}

void DeleteTextureBitmap(std::string TexturePath, std::vector<std::pair<std::string, FIBITMAP*>>* LoadedTextures) {

    int Index = -1;

    // Iterate Over Array, Try And Find Match
    for (unsigned int LoadedTextureIndex = 0; LoadedTextureIndex < LoadedTextures->size(); LoadedTextureIndex++) {
        if ((*LoadedTextures)[LoadedTextureIndex].first == TexturePath) {
            Index = LoadedTextureIndex;
            break;
        }
    }

    // Delete
    if (Index != -1) {
        LoadedTextures->erase(LoadedTextures->begin() + Index);
    }


}

std::pair<std::string, std::string> FindTextureMatches(ERS_STRUCT_Mesh* Mesh, std::string Type1, std::string Type2) {

    // Setup Initialization Variables
    bool HasType1 = false;
    std::string Type1Name;

    bool HasType2 = false;
    std::string Type2Name;

    // Traverse Textures Array, Try And find Types
    for (unsigned int i = 0; i < Mesh->Textures_.size(); i++) {
        if (Mesh->Textures_[i]->Type == Type1) {
            HasType1 = true;
            Type1Name = Mesh->Textures_[i]->Path;
            break;
        }
    }
    for (unsigned int i = 0; i < Mesh->Textures_.size(); i++) {
        if (Mesh->Textures_[i]->Type == Type2) {
            HasType2 = true;
            Type2Name = Mesh->Textures_[i]->Path;
            break;
        }
    }

    // Check That Both Are Sorted
    if (HasType1 && HasType2) {
        return std::make_pair(Type1Name, Type2Name);
    } else {
        return std::make_pair(std::string(""), std::string(""));
    }

}

void ERS_CLASS_ModelImporter::MergeTextures(ERS_STRUCT_Model* Model, std::vector<std::pair<std::string, FIBITMAP*>>* LoadedTextures) {

    // Create Pair Of All Textures With Opacity/Alpha Maps
    std::vector<std::pair<std::string, std::string>> OpacityAlphaMaps;
    for (unsigned int i = 0; i < Model->Meshes.size(); i++) {

        // Find Matching Types For The Same Mesh
        std::pair<std::string, std::string> Match = FindTextureMatches(&Model->Meshes[i], "texture_opacity", "texture_diffuse");

        // If Not Empty (Matching Failed) And It's Not Already In The Opacity Map, Add It
        if (Match != std::make_pair(std::string(""), std::string(""))) {

            bool InArray = false;
            for (unsigned int x = 0; x < OpacityAlphaMaps.size(); x++) {
                if (OpacityAlphaMaps[x] == Match) {
                    InArray = true;
                    break;
                } 
            }
            if (!InArray) {

                SystemUtils_->Logger_->Log(std::string("Found Opacity Map For Diffuse Texture '") + Match.second + "', Adding To Merge Queue", 2);
                OpacityAlphaMaps.push_back(Match);
            }

        }
    }

    // Iterate Over All Matches, Merge The Two
    for (unsigned int i = 0; i < OpacityAlphaMaps.size(); i++) {
        
        // Get Alpha, Diffuse From Real Loaded Texture Maps
        FIBITMAP* AlphaTexture = FindTextureBitmap(OpacityAlphaMaps[i].first, LoadedTextures);
        FIBITMAP* DiffuseTexture = FindTextureBitmap(OpacityAlphaMaps[i].second, LoadedTextures);

        // Merge Together (If Images Are Not NULL)
        if (AlphaTexture != NULL && DiffuseTexture != NULL) {
            FIBITMAP* AlphaChannel = FreeImage_GetChannel(AlphaTexture, FICC_ALPHA);
            FreeImage_SetChannel(DiffuseTexture, AlphaChannel, FICC_ALPHA);
            SystemUtils_->Logger_->Log(std::string("Merging Opacity Map For Texture '") + OpacityAlphaMaps[i].second + "'", 2);

        }

        // Delete ALpha Texture
        DeleteTextureBitmap(OpacityAlphaMaps[i].first, LoadedTextures);

    }

}

void ERS_CLASS_ModelImporter::WriteTextures(ERS_STRUCT_Model* Model, std::vector<std::vector<int>>* TextureImageMemorySizes, std::vector<std::vector<long>>* TextureImageAssetIDs, std::vector<std::vector<std::pair<int, int>>>* TextureImageResolutions, std::vector<std::vector<int>>* TextureImageChannels, std::string AssetPath, FREE_IMAGE_FORMAT Format, int MipMaps) {

    // Create List Of Texture Files To Be Copied
    std::vector<std::pair<std::string, std::shared_ptr<ERS_STRUCT_IOData>>> TextureFiles;
    for (int i = 0; (long)i < (long)TextureList_.size(); i++) {

        std::shared_ptr<ERS_STRUCT_IOData> Data = std::make_shared<ERS_STRUCT_IOData>();
        std::string TexturePath = TextureList_[i];
        bool Success = ReadFile(TextureList_[i], Data.get());
        Data->AssetTypeName = "Texture";
        Data->AssetFileName = TextureList_[i].substr(AssetPath.find_last_of("/") + 1, AssetPath.size() - 1);
        Data->AssetCreationDate = SystemUtils_->ERS_IOSubsystem_->GetCurrentTime();


        bool SecondTryStatus = false;
        if (!Success) {
            SystemUtils_->Logger_->Log(std::string("Error Loading Texture From Given Path '") + AssetPath + std::string("', Will Search Current Directory For Texture"), 7);

            // Strip To Last Item In Path (With Forward Slashes And Backward Slashes)
            std::string Path = TextureList_[i];
            std::replace(Path.begin(), Path.end(), '\\', '/');
            if (Path.find("/") != std::string::npos) {
                Path = Path.substr(Path.find_last_of("/") + 1, Path.size()-1);
            }

            // Create Reference String To Be Tested Against
            std::string RefString = Path.substr(0, Path.find_first_of("."));
            size_t Pos = 0;
            while ((Pos = RefString.find(" ", Pos)) != std::string::npos) {
                RefString.replace(Pos, 1, "_");
                Pos ++;
            }

            // Check Against Filesystem
            std::replace(AssetPath.begin(), AssetPath.end(), '\\', '/');
            for (const auto &Entry : std::filesystem::recursive_directory_iterator(AssetPath.substr(0, AssetPath.find_last_of("/")))) {

                std::string FilePath{Entry.path().u8string()};
                std::replace(FilePath.begin(), FilePath.end(), '\\', '/');
                std::string FileName = FilePath.substr(FilePath.find_last_of('/') + 1, FilePath.size() - 1);
                std::string FileNameWithoutExtension = FileName.substr(0, FileName.find_first_of("."));

                // Remove Spaces From Filename And Replace With Underscores
                Pos = 0;
                while ((Pos = FileNameWithoutExtension.find(" ", Pos)) != std::string::npos) {
                    FileNameWithoutExtension.replace(Pos, 1, "_");
                    Pos ++;
                }


                if (FileNameWithoutExtension == RefString) {
                    Path = FilePath;
                    SystemUtils_->Logger_->Log(std::string("Found Potential Match '") + FilePath + std::string("', Attempting To Load"), 5);
                    break;
                }

            
            }


            SecondTryStatus = ReadFile(Path, Data.get());
            TexturePath = Path;
            
            if (!SecondTryStatus) {
                SystemUtils_->Logger_->Log("Failed To Find Texture During Second Try Effort, Abandoning Texture", 8);
            } else {
                SystemUtils_->Logger_->Log("Found Probable File, However This Is Not Guarenteed To Be Correct", 6);
            }

        }

        if (Success || SecondTryStatus) {
            TextureFiles.push_back(std::make_pair(TexturePath, Data));
        }

    }

    // Load Textures Into Memory
    std::vector<std::pair<std::string, FIBITMAP*>> ImageBytes;
    for (unsigned int i = 0; i < TextureFiles.size(); i++) {

        SystemUtils_->Logger_->Log(std::string("Loading Texture Image '")  + TextureFiles[i].first + "'", 4);
        
        ERS_STRUCT_IOData* ImageData = TextureFiles[i].second.get();
        FIMEMORY* FIImageData = FreeImage_OpenMemory(ImageData->Data.get(), ImageData->Size_B);
        FREE_IMAGE_FORMAT Format = FreeImage_GetFileTypeFromMemory(FIImageData);
        FIBITMAP* RawImage = FreeImage_LoadFromMemory(Format, FIImageData);
        FreeImage_CloseMemory(FIImageData);

        FreeImage_FlipVertical(RawImage);

        FIBITMAP* Image = FreeImage_ConvertTo32Bits(RawImage);
        FreeImage_Unload(RawImage);

        SystemUtils_->Logger_->Log(std::string("Loaded Texture Image"), 3);


        ImageBytes.push_back(std::make_pair(TextureFiles[i].first, Image));
    }

    // Remove Duplicate Stuff (Like Alpha Maps), Just Generally Consolidate Stuff
    MergeTextures(Model, &ImageBytes);

    // Resize For Mipmaps, Save To New Project
    for (unsigned int i = 0; i < ImageBytes.size(); i++) {

        // Get Raw Source Texture Information
        FIBITMAP* Image = ImageBytes[i].second;
        int SourceImageWidth = FreeImage_GetWidth(Image);
        int SourceImageHeight = FreeImage_GetHeight(Image);

        // Generate List Of New Resolutions
        std::vector<std::pair<int, int>> Resolutions;
        int X = SourceImageWidth;
        int Y = SourceImageHeight;
        for (int MipMapIndex = MipMaps - 1; MipMapIndex >= 0; MipMapIndex--) {

            X = std::max(1, X);
            Y = std::max(1, Y);
            
            Resolutions.push_back(std::make_pair(X, Y));
            SystemUtils_->Logger_->Log(std::string("Calculating Texture Level '") + std::to_string(MipMapIndex) + "' Size '" + std::to_string(X) + "," + std::to_string(Y) + "'", 4);

            // Limit Sizes
            if (X > 1) {
                X /= 2;
            }
            if (Y > 1) {
                Y /= 2;
            }

        }

        // Resize Images
        std::vector<int> ImageMemorySizes;
        std::vector<long> ImageAssetIDs;
        std::vector<int> ImageChannels;
        for (int MipMapIndex = 0; MipMapIndex < MipMaps; MipMapIndex++) {

            // Resize Image
            int TargetX, TargetY;
            TargetX = Resolutions[MipMapIndex].first;
            TargetY = Resolutions[MipMapIndex].second;
            SystemUtils_->Logger_->Log(std::string("Resizing Texture Image To Size '") + std::to_string(TargetX) + "," + std::to_string(TargetY) + "'", 4);
            FIBITMAP* NewImage = FreeImage_Rescale(Image, TargetX, TargetY);

            // Swap Colors From RGB To BGR
            FIBITMAP* Red = FreeImage_GetChannel(NewImage, FICC_RED);
            FIBITMAP* Green = FreeImage_GetChannel(NewImage, FICC_GREEN);
            FIBITMAP* Blue = FreeImage_GetChannel(NewImage, FICC_BLUE);
            FIBITMAP* Alpha = FreeImage_GetChannel(NewImage, FICC_ALPHA);
            FreeImage_SetChannel(NewImage, Red, FICC_BLUE);
            FreeImage_SetChannel(NewImage, Green, FICC_GREEN);
            FreeImage_SetChannel(NewImage, Blue, FICC_RED);
            FreeImage_SetChannel(NewImage, Alpha, FICC_ALPHA);
            FreeImage_Unload(Red);
            FreeImage_Unload(Green);
            FreeImage_Unload(Blue);

            // Get Metadata Info
            int MemorySize = FreeImage_GetMemorySize(NewImage);
            long ImageAssetID = SystemUtils_->ERS_IOSubsystem_->AllocateAssetID();
            ImageMemorySizes.push_back(MemorySize);
            ImageAssetIDs.push_back(ImageAssetID);
            SystemUtils_->Logger_->Log(std::string("Generating Texture Image Metadata,  Size Is '") + std::to_string(MemorySize) + "' Bytes, ID Is '" + std::to_string(ImageAssetID) + "'", 3);


            // Save Image
            SystemUtils_->Logger_->Log(std::string("Writing Texture Image For Layer '")
            + std::to_string((MipMaps - 1) - MipMapIndex)
            + "' With ID '" + std::to_string(ImageAssetID)
            + "' For Asset Texture '" + TextureList_[i], 3);
            FIMEMORY* Memory = FreeImage_OpenMemory();
            FreeImage_SaveToMemory(Format, NewImage, Memory);
            FreeImage_Unload(NewImage);


            std::unique_ptr<ERS_STRUCT_IOData> Data = std::make_unique<ERS_STRUCT_IOData>();
            Data->AssetTypeName = "TextureImage";
            DWORD ImageCompressedSize = 0;
            BYTE *ImageCompressedBytes;
            FreeImage_AcquireMemory(Memory, &ImageCompressedBytes, &ImageCompressedSize);
            Data->Data.reset(new unsigned char[ImageCompressedSize]);
            ::memcpy(Data->Data.get(), ImageCompressedBytes, ImageCompressedSize);
            FreeImage_CloseMemory(Memory);
            Data->Size_B = ImageCompressedSize;
            Data->AssetCreationDate = SystemUtils_->ERS_IOSubsystem_->GetCurrentTime();
            Data->AssetModificationDate = SystemUtils_->ERS_IOSubsystem_->GetCurrentTime();
            bool WriteSuccess = SystemUtils_->ERS_IOSubsystem_->WriteAsset(ImageAssetID, Data.get());
            if (!WriteSuccess) {
                SystemUtils_->Logger_->Log("Error Writing Texture File", 8);
                ImageChannels.push_back(0);
            }


            if (WriteSuccess) {

                // Test Re-Loading Image And Confirm it's all good
                SystemUtils_->Logger_->Log(std::string("Testing Texture Image For Layer '")
                + std::to_string((MipMaps - 1) - MipMapIndex)
                + "' With ID '" + std::to_string(ImageAssetID)
                + "' For Asset Texture '" + TextureList_[i], 3);
                bool ReadSuccess = SystemUtils_->ERS_IOSubsystem_->ReadAsset(ImageAssetID, Data.get());

                if (ReadSuccess) {
                    FIMEMORY* FIImageData = FreeImage_OpenMemory(Data->Data.get(), Data->Size_B);
                    FREE_IMAGE_FORMAT Format = FreeImage_GetFileTypeFromMemory(FIImageData);
                    FIBITMAP* TestImage = FreeImage_LoadFromMemory(Format, FIImageData);
                    FreeImage_CloseMemory(FIImageData);
                    FreeImage_FlipVertical(TestImage);

                    // Detect Channels
                    int Line = FreeImage_GetLine(TestImage);
                    int Width = FreeImage_GetWidth(TestImage);
                    if (Width == 0 || Line == 0) {
                        ImageChannels.push_back(0);
                    } else {
                        ImageChannels.push_back(Line / Width);
                    }
                    SystemUtils_->Logger_->Log(std::string("Detected Number Of Channels To Be '")
                    + std::to_string(Line/Width) + "' For " + TextureList_[i], 3);
                    FreeImage_Unload(TestImage);
                } else {
                    SystemUtils_->Logger_->Log("Error Reading Image Asset Data", 8);
                    ImageChannels.push_back(0);
                }

            }


        }
        FreeImage_Unload(Image);

        // Add To Output Vectors
        TextureImageMemorySizes->push_back(ImageMemorySizes);
        TextureImageAssetIDs->push_back(ImageAssetIDs);
        TextureImageResolutions->push_back(Resolutions);
        TextureImageChannels->push_back(ImageChannels);

    }

}

void ERS_CLASS_ModelImporter::ProcessNode(ERS_STRUCT_Model* Model, aiNode *Node, const aiScene *Scene, std::string ModelDirectory) {

    // Process Meshes In Current Node
    for (unsigned int i = 0; i < Node->mNumMeshes; i++) {
        aiMesh* Mesh = Scene->mMeshes[Node->mMeshes[i]];
        Model->Meshes.push_back(ProcessMesh(Model, Mesh, Scene, ModelDirectory));
    }

    // Process Children Nodes
    for (unsigned int i = 0; i < Node->mNumChildren; i++) {
        ProcessNode(Model, Node->mChildren[i], Scene, ModelDirectory);
    }


}

void ERS_CLASS_ModelImporter::HandleMeshTextures(ERS_STRUCT_Model* Model, aiMaterial* Material, std::string ModelDirectory) {

    SystemUtils_->Logger_->Log("Identifying Mesh Textures", 3);
    AddTexture(Model, Material, aiTextureType_AMBIENT, "texture_ambient", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_AMBIENT_OCCLUSION, "texture_ambient_occlusion", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_BASE_COLOR, "texture_base_color", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_DIFFUSE, "texture_diffuse", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_DIFFUSE_ROUGHNESS, "texture_diffuse_roughness", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_DISPLACEMENT, "texture_displacement", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_EMISSION_COLOR, "texture_emission_color", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_EMISSIVE, "texture_emissive", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_HEIGHT, "texture_height", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_LIGHTMAP, "texture_lightmap", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_METALNESS, "texture_metalness", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_NORMAL_CAMERA, "texture_normal_camera", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_NORMALS, "texture_normals", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_OPACITY, "texture_opacity", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_REFLECTION, "texture_reflection", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_SHININESS, "texture_shininess", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_SPECULAR, "texture_specular", ModelDirectory);
    SystemUtils_->Logger_->Log("Finshed Mesh Texture Identification", 4);

}

ERS_STRUCT_Mesh ERS_CLASS_ModelImporter::ProcessMesh(ERS_STRUCT_Model* Model, aiMesh *Mesh, const aiScene *Scene, std::string ModelDirectory) {

    // Process Materials
    aiMaterial* Material = Scene->mMaterials[Mesh->mMaterialIndex];
    HandleMeshTextures(Model, Material, ModelDirectory);


    // Create Data Holders
    ERS_STRUCT_Mesh OutputMesh;

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

    return OutputMesh;

}

void ERS_CLASS_ModelImporter::AddTexture(ERS_STRUCT_Model* Model, aiMaterial *Mat, aiTextureType Type, std::string TypeName, std::string ModelDirectory) {


    for (unsigned int i=0; i< Mat->GetTextureCount(Type); i++) {

        aiString Str;
        Mat->GetTexture(Type, i, &Str);

        // Calculate Texture Path, Append If Not Already In List
        std::string FilePath = std::string(ModelDirectory + std::string(Model->Directory)  + std::string("/") + std::string(Str.C_Str()));
        std::string Message = std::string("Found Texture Of Type '") + TypeName + std::string("' At Path '") + FilePath + std::string("'");
        SystemUtils_->Logger_->Log(Message, 3);
        if (std::find(TextureList_.begin(), TextureList_.end(), FilePath) == TextureList_.end()) {
            TextureList_.push_back(FilePath);
        }   

    }

}

bool ERS_CLASS_ModelImporter::ReadFile(std::string FilePath, ERS_STRUCT_IOData* OutputData) {


    struct stat Buffer;
    int FileStatus = stat(FilePath.c_str(), &Buffer);


        if (FileStatus == 0) {

            OutputData->Data.reset(new unsigned char[Buffer.st_size]);
            if (OutputData->Data) {

                FILE *Stream = fopen(FilePath.c_str(), "rb");
                if (Stream) {

                    fread(OutputData->Data.get(), sizeof(unsigned char), Buffer.st_size, Stream);
                    OutputData->Size_B = Buffer.st_size;
                    fclose(Stream);
                    OutputData->HasLoaded = true;

                } else {
                    SystemUtils_->Logger_->Log(std::string(std::string("Error Loading Asset '") + FilePath + std::string("', Failed To Open Filestream")).c_str(), 9);
                    OutputData->HasLoaded = false;
                    return false;
                }

            } else {
                SystemUtils_->Logger_->Log(std::string(std::string("Error Loading Asset '") + FilePath + std::string("', Memory Allocation Failed")).c_str(), 9);            
                OutputData->HasLoaded = false;
                return false;
            }
        
        } else {
            SystemUtils_->Logger_->Log(std::string(std::string("Error Loading Asset '") + FilePath + std::string("', File Not Found")).c_str(), 9);
            OutputData->HasLoaded = false;
            return false;
        }

    return true;

}