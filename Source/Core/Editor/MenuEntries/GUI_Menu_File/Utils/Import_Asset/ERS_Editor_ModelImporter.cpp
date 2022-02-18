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

    // Read File
    Assimp::Importer Importer;
    SystemUtils_->Logger_->Log(std::string(std::string("Loading Model At File Path: ") + std::string(AssetPath)).c_str(), 3);
    const aiScene* Scene = Importer.ReadFile(AssetPath, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    // Log Errors
    if (!Scene || Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode) {
        SystemUtils_->Logger_->Log(std::string(std::string("Model Loading Error: ") + std::string(Importer.GetErrorString())).c_str(), 10);
        return -1;
    }

    // Process Root Node Recursively, Identify Textures/Files
    ProcessNode(&Model, Scene->mRootNode, Scene, ModelDirectory);


    // Copy Model File
    std::shared_ptr<ERS_STRUCT_IOData> Data = std::make_shared<ERS_STRUCT_IOData>();
    ReadFile(AssetPath, Data);
    long ModelID = SystemUtils_->ERS_IOSubsystem_->AllocateAssetID();
    SystemUtils_->Logger_->Log(std::string(std::string("Assigning ID '") + std::to_string(ModelID) + std::string("' To Model '") + AssetPath + std::string("'")).c_str(), 4);
    SystemUtils_->ERS_IOSubsystem_->WriteAsset(ModelID, Data);    

    // Copy Textures
    std::vector<long> TextureIDs = SystemUtils_->ERS_IOSubsystem_->BatchAllocateIDs(TextureList_.size());
    for (int i = 0; i < TextureList_.size(); i++) {
        SystemUtils_->Logger_->Log(std::string(std::string("Assigning ID '") + std::to_string(TextureIDs[i]) + std::string("' To Texture '") + TextureList_[i] + std::string("'")).c_str(), 4);
        ReadFile(TextureList_[i], Data);
        SystemUtils_->ERS_IOSubsystem_->WriteAsset(TextureIDs[i], Data);

    }

   
    // Generate Metadata
    YAML::Emitter MetadataEmitter;
    MetadataEmitter<<YAML::BeginMap;

    MetadataEmitter<<YAML::Key<<"Name"<<YAML::Value<<AssetPath; // Default name is file path, user can rename
    MetadataEmitter<<YAML::Key<<"ModelID"<<YAML::Value<<ModelID;

    MetadataEmitter<<YAML::Key<<"TextureIDs";
    MetadataEmitter<<YAML::Key<<YAML::BeginMap;
    for (int i = 0; i < TextureIDs.size(); i++) {
        MetadataEmitter<<YAML::Key<<TextureList_[i].substr(TextureList_[i].find_last_of("/")+1, TextureList_[i].size()-(TextureList_[i].find_last_of("/")+1))<<YAML::Value<<TextureIDs[i];
    }
    MetadataEmitter<<YAML::EndMap;
    
    MetadataEmitter<<YAML::EndMap;


    // Write Metadata
    std::string Metadata = std::string(MetadataEmitter.c_str());
    Data->Data.reset(new unsigned char[Metadata.size()]);
    Data->Size_B = Metadata.size();
    memcpy(Data->Data.get(), Metadata.c_str(), Metadata.size());

    // Set Metadata (FIXME: Save Modification Date + Creation Date Here!)
    Data->AssetTypeName = "Model";

    long MetadataID = SystemUtils_->ERS_IOSubsystem_->AllocateAssetID();
    SystemUtils_->Logger_->Log(std::string(std::string("Assigning ID '") + std::to_string(MetadataID) + std::string("' To Model Metadata")).c_str(), 4);
    SystemUtils_->ERS_IOSubsystem_->WriteAsset(MetadataID, Data);
    
    return MetadataID;
}



// Process Nodes
void ERS_CLASS_ModelImporter::ProcessNode(ERS_STRUCT_Model* Model, aiNode *Node, const aiScene *Scene, std::string ModelDirectory) {

    // Process Meshes In Current Node
    for (unsigned int i = 0; i < Node->mNumMeshes; i++) {
        aiMesh* Mesh = Scene->mMeshes[Node->mMeshes[i]];
        ProcessMesh(Model, Mesh, Scene, ModelDirectory);
    }

    // Process Children Nodes
    for (unsigned int i = 0; i < Node->mNumChildren; i++) {
        ProcessNode(Model, Node->mChildren[i], Scene, ModelDirectory);
    }


}

// Process Mesh
void ERS_CLASS_ModelImporter::ProcessMesh(ERS_STRUCT_Model* Model, aiMesh *Mesh, const aiScene *Scene, std::string ModelDirectory) {

    // Process Materials
    aiMaterial* Material = Scene->mMaterials[Mesh->mMaterialIndex];

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
    AddTexture(Model, Material, aiTextureType_NORMALS, "texture_normal", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_OPACITY, "texture_opacity", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_REFLECTION, "texture_reflection", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_SHININESS, "texture_shininess", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_SPECULAR, "texture_specular", ModelDirectory);
    AddTexture(Model, Material, aiTextureType_UNKNOWN, "texture_unknown", ModelDirectory);


}

// Check Material Textures
void ERS_CLASS_ModelImporter::AddTexture(ERS_STRUCT_Model* Model, aiMaterial *Mat, aiTextureType Type, std::string TypeName, std::string ModelDirectory) {


    for (unsigned int i=0; i< Mat->GetTextureCount(Type); i++) {

        aiString Str;
        Mat->GetTexture(Type, i, &Str);

        std::string Message = std::string("Found Texture '") + TypeName + std::string("'");
        SystemUtils_->Logger_->Log(Message, 3);

        // Calculate Texture Path, Append If Not Already In List
        std::string FilePath = std::string(ModelDirectory + std::string(Model->Directory)  + std::string("/") + std::string(Str.C_Str()));
        if (std::find(TextureList_.begin(), TextureList_.end(), FilePath) == TextureList_.end()) {
            TextureList_.push_back(FilePath);
        }   

    }

}

// Load IOData
void ERS_CLASS_ModelImporter::ReadFile(std::string FilePath, std::shared_ptr<ERS_STRUCT_IOData> OutputData) {


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
                }

            } else {
                SystemUtils_->Logger_->Log(std::string(std::string("Error Loading Asset '") + FilePath + std::string("', Memory Allocation Failed")).c_str(), 9);            
                OutputData->HasLoaded = false;
            }
        
        } else {
            SystemUtils_->Logger_->Log(std::string(std::string("Error Loading Asset '") + FilePath + std::string("', File Not Found")).c_str(), 9);
            OutputData->HasLoaded = false;
        }

}