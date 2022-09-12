//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_FUNCTION_Legacy_PreprocessTextureInfo.h>


void ERS_CLASS_ModelLoader::LoadModel(long AssetID, std::shared_ptr<ERS_STRUCT_Model> Model) {

    // Log Loading For Debugging Purposes
    //SystemUtils_->Logger_->Log(std::string(std::string("Loading Model '") + std::to_string(AssetID) + std::string("'")).c_str(), 4);
    Model->LoadingStartTime_ = glfwGetTime();

    // Read Metadata From Asset
    std::unique_ptr<ERS_STRUCT_IOData> ModelMetadata = std::make_unique<ERS_STRUCT_IOData>();
    SystemUtils_->ERS_IOSubsystem_->ReadAsset(AssetID, ModelMetadata.get());
    std::string ModelMetadataString = std::string((const char*)ModelMetadata->Data.get());
    YAML::Node Metadata = YAML::Load(ModelMetadataString);


    ERS_FUNCTION_DecodeModelMetadata(Metadata, Model.get(), SystemUtils_, AssetID, false);

    // Spawn Threads To Load Textures
    // std::vector<std::future<ERS_STRUCT_Texture>> DecodedTextures;
    // for (int i = 0; (long)i < (long)TexturePaths.size(); i++) {
    //     SystemUtils_->Logger_->Log(std::string(std::string("Assigning Texture To Thread With ID: ") + std::to_string(TextureIDs[i])).c_str(), 4);
    //     DecodedTextures.push_back(std::async(&ERS_CLASS_ModelLoader::LoadTexture, this, TextureIDs[i], FlipTextures));
    // }


    // Read Mesh
    Assimp::Importer Importer;
    //SystemUtils_->Logger_->Log(std::string(std::string("Loading Model With ID: ") + std::to_string(AssetID)).c_str(), 3);

    std::unique_ptr<ERS_STRUCT_IOData> ModelData = std::make_unique<ERS_STRUCT_IOData>();
    SystemUtils_->ERS_IOSubsystem_->ReadAsset(Model->ModelDataID, ModelData.get());
    const aiScene* Scene = Importer.ReadFileFromMemory(ModelData->Data.get(), (int)ModelData->Size_B, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_PreTransformVertices | aiProcess_JoinIdenticalVertices, "");

    // Log Errors
    if (!Scene || Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode) {
        SystemUtils_->Logger_->Log(std::string(std::string("Model Loading Error: ") + std::string(Importer.GetErrorString())).c_str(), 10);
        Model->IsReadyForGPU = false;
        return;
    }

    // Decode Mesh, Create Texture Pointers
    ProcessNode(Model.get(), Scene->mRootNode, Scene);

    // // Get Texture Images From Loader, Push Into Vector
    // for (unsigned long i = 0; i < DecodedTextures.size(); i++) {
    //     SystemUtils_->Logger_->Log(std::string(std::string("Getting Texture With ID: ") + std::to_string(TextureIDs[i])).c_str(), 4);
    //     Model->TexturesToPushToGPU_.push_back(DecodedTextures[i].get());
    // }


    // Math Textures To Meshes
    MatchTextures(Model.get());


    // Set Ready For GPU
    Model->IsReadyForGPU = true;
}

void ERS_CLASS_ModelLoader::MatchTextures(ERS_STRUCT_Model* Model) {

    // Extract Information About Textures For Simplicity
    std::vector<ERS_STRUCT_Mesh*> Meshes;
    for (unsigned int i = 0; i < Model->Meshes.size(); i++) {
        Meshes.push_back(&Model->Meshes[i]);
    }

    // Match
    for (unsigned int MeshIndex = 0; MeshIndex < Meshes.size(); MeshIndex++) {
        ERS_STRUCT_Mesh* CurrentMesh = Meshes[MeshIndex];

        // Iterate Over Mesh's Requested Textures, Try To Match With What Model Has
        for (unsigned int TextureIndex = 0; TextureIndex < CurrentMesh->Loader_RequestedTextureInformation_.size(); TextureIndex++) {
            std::string TextureType = CurrentMesh->Loader_RequestedTextureInformation_[TextureIndex].first;
            std::string TextureIdentifier = CurrentMesh->Loader_RequestedTextureInformation_[TextureIndex].second;

            // Now, Search Model's Textures For Match
            for (unsigned int ModelTextureIndex = 0; ModelTextureIndex < Model->Textures_.size(); ModelTextureIndex++) {
                std::string ModelTextureIdentifier = Model->Textures_[ModelTextureIndex].Path;
                
                if (ModelTextureIdentifier == TextureIdentifier) {
                    Model->Textures_[ModelTextureIndex].Type = TextureType;
                    CurrentMesh->Textures_.push_back(&Model->Textures_[ModelTextureIndex]);
                    break;
                }

            }

        }

    }  

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

void ERS_CLASS_ModelLoader::ProcessNode(ERS_STRUCT_Model* Model, aiNode *Node, const aiScene *Scene) {


    // Process Meshes In Current Node
    for (unsigned int i = 0; i < Node->mNumMeshes; i++) {
        aiMesh* Mesh = Scene->mMeshes[Node->mMeshes[i]];
        Model->Meshes_.push_back(
            ProcessMesh(
                Model,
                (unsigned long)Mesh->mNumVertices,
                (unsigned long)Mesh->mNumFaces*3,
                Mesh,
                Scene
            )
        );

    }

    // Process Children Nodes
    for (unsigned int i = 0; i < Node->mNumChildren; i++) {
        ProcessNode(Model, Node->mChildren[i], Scene);
    }

}

ERS_STRUCT_Mesh ERS_LEGACY_FUNCTION_ProcessMesh(ERS_STRUCT_Model* Model, unsigned long PreallocVertSize, unsigned long PreallocIndSize, aiMesh *Mesh, const aiScene *Scene) {

    // Create Data Holders
    ERS_STRUCT_Mesh OutputMesh;

    // Process Materials
    aiMaterial* Material = Scene->mMaterials[Mesh->mMaterialIndex];
    ERS_LEGACY_FUNCTION_IdentifyMeshTextures(Material, &OutputMesh);


    // Return Populated Mesh
    return OutputMesh;

}

void ERS_LEGACY_FUNCTION_IdentifyMeshTextures(aiMaterial* Mat, ERS_STRUCT_Mesh* Mesh) {

    std::vector<std::pair<aiTextureType, std::string>> TextureTypes;
    TextureTypes.push_back(std::make_pair(aiTextureType_AMBIENT,           "texture_ambient"));
    TextureTypes.push_back(std::make_pair(aiTextureType_AMBIENT_OCCLUSION, "texture_ambient_occlusion"));
    TextureTypes.push_back(std::make_pair(aiTextureType_BASE_COLOR,        "texture_base_color"));
    TextureTypes.push_back(std::make_pair(aiTextureType_DIFFUSE,           "texture_diffuse"));
    TextureTypes.push_back(std::make_pair(aiTextureType_DIFFUSE_ROUGHNESS, "texture_diffuse_roughness"));
    TextureTypes.push_back(std::make_pair(aiTextureType_DISPLACEMENT,      "texture_displacement"));
    TextureTypes.push_back(std::make_pair(aiTextureType_EMISSION_COLOR,    "texture_emission_color"));
    TextureTypes.push_back(std::make_pair(aiTextureType_EMISSIVE,          "texture_emissive"));
    TextureTypes.push_back(std::make_pair(aiTextureType_HEIGHT,            "texture_height"));
    TextureTypes.push_back(std::make_pair(aiTextureType_LIGHTMAP,          "texture_lightmap"));
    TextureTypes.push_back(std::make_pair(aiTextureType_METALNESS,         "texture_metalness"));
    TextureTypes.push_back(std::make_pair(aiTextureType_NONE,              "texture_none"));
    TextureTypes.push_back(std::make_pair(aiTextureType_NORMAL_CAMERA,     "texture_normal_camera"));
    TextureTypes.push_back(std::make_pair(aiTextureType_NORMALS,           "texture_normals"));
    TextureTypes.push_back(std::make_pair(aiTextureType_OPACITY,           "texture_opacity"));
    TextureTypes.push_back(std::make_pair(aiTextureType_REFLECTION,        "texture_reflection"));
    TextureTypes.push_back(std::make_pair(aiTextureType_SHININESS,         "texture_shininess"));
    TextureTypes.push_back(std::make_pair(aiTextureType_SPECULAR,          "texture_specular"));
    TextureTypes.push_back(std::make_pair(aiTextureType_UNKNOWN,           "texture_unknown"));

    // Iterate Over All Texture Types
    for (unsigned int TextureTypeIndex = 0; TextureTypeIndex < TextureTypes.size(); TextureTypeIndex++) {

        aiTextureType Type = TextureTypes[TextureTypeIndex].first;
        std::string TypeName = TextureTypes[TextureTypeIndex].second;

        // Iterate Through Textures For This Type
        for (unsigned int i=0; i< Mat->GetTextureCount(Type); i++) {


            // Calculate Texture Path
            aiString TextureString;
            Mat->GetTexture(Type, i, &TextureString);
            std::string TextureIdentifier = std::string(std::string(TextureString.C_Str()));

            //std::string Message = std::string("Model Requesting Texture Of Type '") + TypeName + std::string("' With Identifier '") + TextureIdentifier + std::string("'");
            //SystemUtils_->Logger_->Log(Message, 3);

            // Search Texture List For Index Of Same Match, Add To List Of Unique Textures If Not Found
            bool AlreadyHasTexture = false;
            for (unsigned long x = 0; x < Mesh->Loader_RequestedTextureInformation_.size(); x++) {
                if (Mesh->Loader_RequestedTextureInformation_[x].second == TextureIdentifier) {
                    SystemUtils_->Logger_->Log(std::string("Found Matching Texture '") + Mesh->Loader_RequestedTextureInformation_[x].second + "'", 3);
                    AlreadyHasTexture = true;
                    break;
                }
            }

            // If It's Not Already In The List, Add IT
            if (!AlreadyHasTexture) {
                Mesh->Loader_RequestedTextureInformation_.push_back(std::make_pair(TypeName, TextureIdentifier));
            }


        }

    }

}

