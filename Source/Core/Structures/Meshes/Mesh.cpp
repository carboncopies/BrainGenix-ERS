//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file creates the ERSMesh Struct/Functions.
    Additonal Notes: None
    Date Created: 2021-11-04
*/ 


#include "Mesh.h"


// Setup Mesh
void ERS_OBJECT_MESH::SetupMesh() {

    // Initialize Buffers/Arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind To Vert Array
    glBindVertexArray(VAO);
    
    // Populate Vertex Buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(ERS_OBJECT_VERTEX), &Vertices[0], GL_STATIC_DRAW);

    // Populate Element Buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), &Indices[0], GL_STATIC_DRAW);


    // Set Vertex Attribute Pointers
    
    // Position Data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ERS_OBJECT_VERTEX), (void*)0);

    // Normals Data
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ERS_OBJECT_VERTEX), (void*)offsetof(ERS_OBJECT_VERTEX, Normal));

    // Texture Coordinate Data
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ERS_OBJECT_VERTEX), (void*)offsetof(ERS_OBJECT_VERTEX, TexCoords));

    // Vertex Tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(ERS_OBJECT_VERTEX), (void*)offsetof(ERS_OBJECT_VERTEX, Tangent));

    // Vertex Bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(ERS_OBJECT_VERTEX), (void*)offsetof(ERS_OBJECT_VERTEX, Bitangent));

    // IDs
    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(ERS_OBJECT_VERTEX), (void*)offsetof(ERS_OBJECT_VERTEX, BoneIDs));

    // Weights
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(ERS_OBJECT_VERTEX), (void*)offsetof(ERS_OBJECT_VERTEX, Weights));

    // Unbind From Vert Array
    glBindVertexArray(0);


    // Set NumberIndices
    NumberIndices = Indices.size();

}

// Draw The Mesh
void ERS_OBJECT_MESH::Draw(std::shared_ptr<ERS_OBJECT_SHADER> Shader) {

    // Bind To OpenGL Handels
    unsigned int DiffuseHandel = 1;
    unsigned int SpecularHandel = 1;
    unsigned int NormalHandel = 1;
    unsigned int HeightHandel = 1;

    // Iterate Through Textures
    for (unsigned int i = 0; i < TextureIDs.size(); i++) {

        // Set To Proper Texture
        glActiveTexture(GL_TEXTURE0 + i);

        // Get Texture Number
        std::string Number;
        std::string Name = TextureNames[i];

        // Detect Type
        if (Name == "texture_diffuse")
            Number = std::to_string(DiffuseHandel++);
        else if(Name == "texture_specular")
            Number = std::to_string(SpecularHandel++);
        else if(Name == "texture_normal")
            Number = std::to_string(NormalHandel++);
        else if(Name == "texture_height")
            Number = std::to_string(HeightHandel++);


        // Set Sampler
        glUniform1i(glGetUniformLocation(Shader->ShaderProgram, (Name + Number).c_str()), i);
        
        // Bind Texture
        glBindTexture(GL_TEXTURE_2D, TextureIDs[i]);

    }

    // Draw Mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, NumberIndices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Set Back To Default
    glActiveTexture(GL_TEXTURE0);


}

