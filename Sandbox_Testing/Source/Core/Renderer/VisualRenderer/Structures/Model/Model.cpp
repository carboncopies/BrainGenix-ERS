//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file creates the ERSModel Struct/Functions.
    Additonal Notes: None
    Date Created: 2021-11-04
*/ 


#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Core/VisualRenderer/Structures/Meshes/Mesh.cpp"

#include "Core/VisualRenderer/Structures/Models/Model.h"


// Load Model From File
void ERS_OJBECT_MODEL::LoadModelFromFile(std::string const &Path) {

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
    ProcessNode(Scene->mRootNode, scene);


}

// Draw Model
void ERS_OBJECT_MODEL::Draw(ERS_OBJECT_SHADER &Shader) {

    // Draw All Meshes
    for (unsigned int i=0; i<Meshes.size(), i++) {
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

    

}

