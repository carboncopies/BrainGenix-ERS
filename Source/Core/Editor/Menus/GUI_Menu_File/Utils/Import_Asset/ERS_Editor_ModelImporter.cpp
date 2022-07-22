//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_Editor_ModelImporter.h>


ERS_CLASS_ModelImporter::ERS_CLASS_ModelImporter(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;

}

ERS_CLASS_ModelImporter::~ERS_CLASS_ModelImporter() {

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



    // Calculate Bounding Box
    glm::vec3 ModelMinXYZ;
    glm::vec3 ModelMaxXYZ;
    for (unsigned int i = 0; i < Model.Meshes.size(); i++) {

        // Get Mesh Min/Max
        glm::vec3 MeshMinXYZ = Model.Meshes[i].MinXYZ_;
        glm::vec3 MeshMaxXYZ = Model.Meshes[i].MaxXYZ_;

        // Check If Larger/Smaller Than Model Min/Max
        if (MeshMinXYZ.x < ModelMinXYZ.x) {
            ModelMinXYZ.x = MeshMinXYZ.x;
        }
        if (MeshMinXYZ.y < ModelMinXYZ.y) {
            ModelMinXYZ.y = MeshMinXYZ.y;
        }
        if (MeshMinXYZ.z < ModelMinXYZ.z) {
            ModelMinXYZ.z = MeshMinXYZ.z;
        }
        if (MeshMaxXYZ.x > ModelMaxXYZ.x) {
            ModelMaxXYZ.x = MeshMaxXYZ.x;
        }
        if (MeshMaxXYZ.y > ModelMaxXYZ.y) {
            ModelMaxXYZ.y = MeshMaxXYZ.y;
        }
        if (MeshMaxXYZ.z > ModelMaxXYZ.z) {
            ModelMaxXYZ.z = MeshMaxXYZ.z;
        }
    }
    Model.BoxScale_ = abs(ModelMaxXYZ) + abs(ModelMinXYZ);

    Model.BoxOffset_ = (Model.BoxScale_ / 2.0f) + ModelMinXYZ;
    
    std::string LogMsg = std::string("Calculated Model Bounding Box To Be '") 
    + std::to_string(Model.BoxScale_.x) + "X, "
    + std::to_string(Model.BoxScale_.y) + "Y, "
    + std::to_string(Model.BoxScale_.z) + "Z' With Offset Of '"
    + std::to_string(Model.BoxOffset_.x) + "X, "
    + std::to_string(Model.BoxOffset_.y) + "Y, "
    + std::to_string(Model.BoxOffset_.z) + "Z'";
    SystemUtils_->Logger_->Log(LogMsg, 3);



    // Copy Model File
    std::unique_ptr<ERS_STRUCT_IOData> Data = std::make_unique<ERS_STRUCT_IOData>();
    
    

    ReadFile(AssetPath, Data.get());
    long ModelID = SystemUtils_->ERS_IOSubsystem_->AllocateAssetID();

    SystemUtils_->Logger_->Log(std::string(std::string("Assigning ID '") + std::to_string(ModelID) + std::string("' To Model '") + AssetPath + std::string("'")).c_str(), 4);
    SystemUtils_->ERS_IOSubsystem_->WriteAsset(ModelID, Data.get());    

    // Get Vert/Indice Metadata Info
    for (unsigned long i = 0; i < Model.Meshes.size(); i++) {
        unsigned long VertSize = Model.Meshes[i].Vertices.size();
        unsigned long IndSize = Model.Meshes[i].Indices.size();
        Model.TotalVertices_ += VertSize;
        Model.TotalIndices_ += IndSize;
    }



    std::vector<std::vector<int>> TextureMemorySizes;
    std::vector<std::vector<long>> ImageAssetIDs;
    std::vector<std::vector<std::pair<int, int>>> ImageResolutions;
    WriteTextures(&TextureMemorySizes, &ImageAssetIDs, &ImageResolutions, AssetPath);



    // Generate Metadata
    YAML::Emitter MetadataEmitter;
    MetadataEmitter<<YAML::BeginMap;

    MetadataEmitter<<YAML::Key<<"Name"<<YAML::Value<<AssetPath;
    MetadataEmitter<<YAML::Key<<"FormatVersion"<<YAML::Value<<"0.0.2";

    MetadataEmitter<<YAML::Key<<"ModelID"<<YAML::Value<<ModelID;




    MetadataEmitter<<YAML::Key<<"Textures";
    MetadataEmitter<<YAML::Key<<YAML::BeginMap;

    // Iterate Over All Textures
    for (unsigned int i = 0; i < TextureList_.size(); i++) {

        // Set Path For Each Texture, Iterate OVer All Levels Of This Texture
        MetadataEmitter<<YAML::Key<<TextureList_[i].substr(TextureList_[i].find_last_of("/")+1, TextureList_[i].size()-(TextureList_[i].find_last_of("/")+1))<<YAML::Value<<YAML::BeginMap;
        for (unsigned int TextureLevel = 0; TextureLevel < TextureMemorySizes[i].size(); TextureLevel++) {
            MetadataEmitter<<YAML::Key<<TextureLevel<<YAML::Value<<YAML::BeginMap;

            MetadataEmitter<<YAML::Key<<"TextureLevelAssetID"<<YAML::Value<<ImageAssetIDs[i][TextureLevel];
            MetadataEmitter<<YAML::Key<<"TextureLevelMemorySizeBytes"<<YAML::Value<<TextureMemorySizes[i][TextureLevel];
            MetadataEmitter<<YAML::Key<<"TextureLevelResolutionX"<<YAML::Value<<ImageResolutions[i][TextureLevel].first;
            MetadataEmitter<<YAML::Key<<"TextureLevelResolutionY"<<YAML::Value<<ImageResolutions[i][TextureLevel].second;

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

// todo: make write textures function take emitter pointer
// then test, fix bugs
// then make loader able to understand this version
// also cleanup loader to just be generally more sensible

void ERS_CLASS_ModelImporter::WriteTextures(std::vector<std::vector<int>>* TextureImageMemorySizes, std::vector<std::vector<long>>* TextureImageAssetIDs, std::vector<std::vector<std::pair<int, int>>>* TextureImageResolutions, std::string AssetPath, FREE_IMAGE_FORMAT Format, int MipMaps) {

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
        FIBITMAP* Image = FreeImage_LoadFromMemory(Format, FIImageData);
        FreeImage_CloseMemory(FIImageData);
        SystemUtils_->Logger_->Log(std::string("Loaded Texture Image"), 3);


        ImageBytes.push_back(std::make_pair(TextureFiles[i].first, Image));
    }

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
        for (int MipMapIndex = 0; MipMapIndex < MipMaps; MipMapIndex++) {
            Resolutions.push_back(std::make_pair(X, Y));
            SystemUtils_->Logger_->Log(std::string("Calculating Texture Level '") + std::to_string(MipMapIndex) + "' Size '" + std::to_string(X) + "," + std::to_string(Y) + "'", 4);
            X /= 2;
            Y /= 2;
        }

        // Resize Images
        std::vector<int> ImageMemorySizes;
        std::vector<long> ImageAssetIDs;
        for (int MipMapIndex = 0; MipMapIndex < MipMaps; MipMapIndex++) {

            // Resize Image
            int TargetX, TargetY;
            TargetX = Resolutions[MipMapIndex].first;
            TargetY = Resolutions[MipMapIndex].second;
            SystemUtils_->Logger_->Log(std::string("Resizing Texture Image To Size '") + std::to_string(TargetX) + "," + std::to_string(TargetY) + "'", 4);
            FIBITMAP* NewImage = FreeImage_Rescale(Image, TargetX, TargetY);

            // Get Metadata Info
            int MemorySize = FreeImage_GetMemorySize(NewImage);
            long ImageAssetID = SystemUtils_->ERS_IOSubsystem_->AllocateAssetID();
            ImageMemorySizes.push_back(MemorySize);
            ImageAssetIDs.push_back(ImageAssetID);
            SystemUtils_->Logger_->Log(std::string("Generating Texture Image Metadata,  Size Is '") + std::to_string(MemorySize) + "' Bytes, ID Is '" + std::to_string(ImageAssetID) + "'", 3);


            // Save Image
            SystemUtils_->Logger_->Log(std::string("Writing Texture Image For Layer '")
            + std::to_string(MipMapIndex)
            + "' With ID '" + std::to_string(ImageAssetID)
            + "' For Asset Texture '" + TextureList_[i], 3);

            FIMEMORY* Memory = FreeImage_OpenMemory();
            FreeImage_SaveToMemory(Format, NewImage, Memory);
            FreeImage_Unload(NewImage);


            std::unique_ptr<ERS_STRUCT_IOData> Data = std::make_unique<ERS_STRUCT_IOData>();
            Data->AssetTypeName = "TextureImage";
            //Data->Data.reset(new unsigned char[MemorySize]);
            //::memcpy(Data->Data.get(), Memory->data, MemorySize);

            DWORD ImageCompressedBytes = 0;
            FreeImage_AcquireMemory(Memory, Data->Data.get(), &ImageCompressedBytes);

            FreeImage_CloseMemory(Memory);
            Data->Size_B = ImageCompressedBytes;
            Data->AssetCreationDate = SystemUtils_->ERS_IOSubsystem_->GetCurrentTime();
            Data->AssetModificationDate = SystemUtils_->ERS_IOSubsystem_->GetCurrentTime();
            SystemUtils_->ERS_IOSubsystem_->WriteAsset(ImageAssetID, Data.get());


        }
        FreeImage_Unload(Image);

        // Add To Output Vectors
        TextureImageMemorySizes->push_back(ImageMemorySizes);
        TextureImageAssetIDs->push_back(ImageAssetIDs);
        TextureImageResolutions->push_back(Resolutions);

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

ERS_STRUCT_Mesh ERS_CLASS_ModelImporter::ProcessMesh(ERS_STRUCT_Model* Model, aiMesh *Mesh, const aiScene *Scene, std::string ModelDirectory) {

    // Process Materials
    aiMaterial* Material = Scene->mMaterials[Mesh->mMaterialIndex];

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
    AddTexture(Model, Material, aiTextureType_NONE, "texture_none", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_NORMAL_CAMERA, "texture_normal_camera", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_NORMALS, "texture_normals", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_OPACITY, "texture_opacity", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_REFLECTION, "texture_reflection", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_SHININESS, "texture_shininess", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_SPECULAR, "texture_specular", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_UNKNOWN, "texture_unknown", ModelDirectory);
    SystemUtils_->Logger_->Log("Finshed Mesh Texture Identification", 4);

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


        // Calculate Min/Max XYZ
        if (Vector.x < OutputMesh.MinXYZ_.x) {
            OutputMesh.MinXYZ_.x = Vector.x;
        }
        if (Vector.y < OutputMesh.MinXYZ_.y) {
            OutputMesh.MinXYZ_.y = Vector.y;
        }
        if (Vector.z < OutputMesh.MinXYZ_.z) {
            OutputMesh.MinXYZ_.z = Vector.z;
        }
        if (Vector.x > OutputMesh.MaxXYZ_.x) {
            OutputMesh.MaxXYZ_.x = Vector.x;
        }
        if (Vector.y > OutputMesh.MaxXYZ_.y) {
            OutputMesh.MaxXYZ_.y = Vector.y;
        }
        if (Vector.z > OutputMesh.MaxXYZ_.z) {
            OutputMesh.MaxXYZ_.z = Vector.z;
        }



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