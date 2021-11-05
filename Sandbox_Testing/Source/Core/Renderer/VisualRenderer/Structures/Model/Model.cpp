//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file creates the ERSModel Struct/Functions.
    Additonal Notes: None
    Date Created: 2021-11-04
*/ 





// Load Model From File
void ERS_OBJECT_MODEL::LoadModelFromFile(std::string const &Path) {

    // Read File
    Assimp::Importer Importer;
    const aiScene* Scene = Importer.ReadFile(Path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    // Log Errors
    if (!Scene || Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode) {
        std::cout<< "ASSET IMPORT ERROR" << Importer.GetErrorString()<<std::endl; /// FIX ME - SHOULD USE ERSLOGGER
        return;
    }

    // Retrieve Directory
    Directory = Path.substr(0, Path.find_last_of("/"));

    // Process Root Node Recursively
    ProcessNode(Scene->mRootNode, Scene);


}

// Draw Model
void ERS_OBJECT_MODEL::Draw(ERS_OBJECT_SHADER &Shader) {

    // Draw All Meshes
    for (unsigned int i=0; i<Meshes.size(); i++) {
        Meshes[i].Draw(Shader);
    }

}

// Process Nodes
void ERS_OBJECT_MODEL::ProcessNode(aiNode *Node, const aiScene *Scene) {

    // Process Meshes In Current Node
    for (unsigned int i = 0; i < Node->mNumMeshes; i++) {
        aiMesh* Mesh = Scene->mMeshes[Node->mMeshes[i]];
        Meshes.push_back(ProcessMesh(Mesh, Scene));
    }

    // Process Children Nodes
    for (unsigned int i = 0; i < Node->mNumChildren; i++) {
        ProcessNode(Node->mChildren[i], Scene);
    }


}

// Process Mesh
ERS_OBJECT_MESH ERS_OBJECT_MODEL::ProcessMesh(aiMesh *Mesh, const aiScene *Scene) {

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
        for (unsigned int j = 0; i < Face.mNumIndices; j++) {
            Indices.push_back(Face.mIndices[j]);
        }
    }

    // Process Materials
    aiMaterial* Material = Scene->mMaterials[Mesh->mMaterialIndex];

    // Diffuse Maps
    std::vector<ERS_OBJECT_TEXTURE_2D> DiffuseMaps = LoadMaterialTextures(Material, aiTextureType_DIFFUSE, "texture_diffuse");
    Textures.insert(Textures.end(), DiffuseMaps.begin(), DiffuseMaps.end());
    // 2. specular maps
    std::vector<ERS_OBJECT_TEXTURE_2D> SpecularMaps = LoadMaterialTextures(Material, aiTextureType_SPECULAR, "texture_specular");
    Textures.insert(Textures.end(), SpecularMaps.begin(), SpecularMaps.end());
    // 3. normal maps
    std::vector<ERS_OBJECT_TEXTURE_2D> NormalMaps = loadMaterialTextures(Material, aiTextureType_HEIGHT, "texture_normal");
    Textures.insert(Textures.end(), NormalMaps.begin(), NormalMaps.end());
    // 4. height maps
    std::vector<ERS_OBJECT_TEXTURE_2D> HeightMaps = loadMaterialTextures(Material, aiTextureType_AMBIENT, "texture_height");
    Textures.insert(Textures.end(), HeightMaps.begin(), HeightMaps.end());

    // Mesh Object
    return ERS_OBJECT_MESH(Vertices, Indices, Textures);

}

// Check Material Textures
std::vector<ERS_TEXTURE_OBJECT> ERS_OBJECT_MODEL::LoadMaterialTextures(aiMaterial *Mat, aiTextureType Type, string TypeName) {

    std::vector<ERS_TEXTURE_OBJECT> Textures;
    for (unsigned int i=0; i< Mat->GetTextureCount(Type); i++) {

        aiString Str;
        Mat->GetTexture(Type, i, &Str);

        bool Skip = false;
        
        // Check If Texture Already Loaded
        for (unsigned int j = 0; j < Textures_Loaded.size(); j++) {

            if (std::strcmp(Textures_Loaded[j].Path.Data(), Str.C_Str()) == 0) {
                Textures.push_back(Textures_Loaded[j]);
                Skip = true;
                break;
            }

        }
        // If Texture Not Already Loaded
        if (!Skip) {
            
            ERS_OBJECT_TEXTURE Texture;
            Texture.ID = TextureFromFile(Str.C_Str(), this->Directory);
            Texture.Type = TypeName;
            Texture.Path = Str.C_Str();
            Textures.push_back(Texture);
            Textures_Loaded.push_back(Texture);

        }

        return Textures;

    }


}


