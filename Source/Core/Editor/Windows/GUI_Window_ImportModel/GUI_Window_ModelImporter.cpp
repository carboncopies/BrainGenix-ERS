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

    // Set Min Size For Bounding Box
    Model->BoxScale_.x = std::max(Model->BoxScale_.x, 0.025f);
    Model->BoxScale_.y = std::max(Model->BoxScale_.y, 0.025f);
    Model->BoxScale_.z = std::max(Model->BoxScale_.z, 0.025f);

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
    TextureNames_ = std::vector<std::string>();

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


    ERS_STRUCT_ModelWriterData ModelWriterData = ERS_STRUCT_ModelWriterData();
    ModelWriterData.Model                    = &Model;
    ModelWriterData.ModelOriginDirectoryPath = AssetPath;
    ModelWriterData.ModelScene               = Scene;





    


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
            TextureNames_.push_back(Str.C_Str());
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