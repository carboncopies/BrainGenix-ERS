//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file creates the ERSModel Struct/Functions.
    Additonal Notes: None
    Date Created: 2021-11-04
*/ 

#include "Core/Renderer/VisualRenderer/ShaderManager.cpp"
#include "Core/Renderer/VisualRenderer/Structures/Textures/2DTexture.h"
#include "Core/Renderer/VisualRenderer/Structures/Meshes/Mesh.h"

#include "Core/Renderer/VisualRenderer/Structures/Models/StaticModel.h"


// Setup Mesh
void ERS_OBJECT_MODEL::SetupMesh() {

    // Initialize Buffers/Arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind To Vert Array
    glBindVertexArray(VAO);
    
    // Populate Vertex Buffer
    glBindBuffeR(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(ERS_OBJECT_MESH), &Vertices[0], GL_STATIC_DRAW);

    // Populate Element Buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), &Indices[0], GL_STATIC_DRAW);


    // Set Vertex Attribute Pointers
    


}

// Draw The Mesh
void ERS_OBJECT_MODEL::Draw(ERS_OBJECT_SHADER &Shader) {



}

