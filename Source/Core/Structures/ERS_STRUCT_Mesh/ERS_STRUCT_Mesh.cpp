//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include "ERS_STRUCT_Mesh.h"


void ERS_STRUCT_Mesh::SetupMesh() {

    // Initialize Buffers/Arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // Bind To Vert Array
    glBindVertexArray(VAO);
    
    // Populate Vertex Buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(ERS_STRUCT_Vertex), &Vertices[0], GL_STATIC_DRAW);

    // Populate Element Buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Indices.size() * sizeof(unsigned int), &Indices[0], GL_STATIC_DRAW);


    // Set Vertex Attribute Pointers
    
    // Position Data
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ERS_STRUCT_Vertex), (void*)0);

    // Normals Data
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ERS_STRUCT_Vertex), (void*)offsetof(ERS_STRUCT_Vertex, Normal));

    // Texture Coordinate Data
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(ERS_STRUCT_Vertex), (void*)offsetof(ERS_STRUCT_Vertex, TexCoords));

    // Vertex Tangent
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(ERS_STRUCT_Vertex), (void*)offsetof(ERS_STRUCT_Vertex, Tangent));

    // Vertex Bitangent
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(ERS_STRUCT_Vertex), (void*)offsetof(ERS_STRUCT_Vertex, Bitangent));

    // IDs
    glEnableVertexAttribArray(5);
    glVertexAttribIPointer(5, 4, GL_INT, sizeof(ERS_STRUCT_Vertex), (void*)offsetof(ERS_STRUCT_Vertex, BoneIDs));

    // Weights
    glEnableVertexAttribArray(6);
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(ERS_STRUCT_Vertex), (void*)offsetof(ERS_STRUCT_Vertex, Weights));

    // Unbind From Vert Array
    glBindVertexArray(0);


    // Set NumberIndices
    NumberIndices = Indices.size();


    // Reset Then Update Texture "Has" Parameters
    HasAmbient_ = false;
    HasAmbientOcclusion_ = false;
    HasBaseColor_ = false;
    HasDiffuse_ = false;
    HasDiffuseRoughness_ = false;
    HasDisplacement_ = false;
    HasEmissionColor_ = false;
    HasEmissive_ = false;
    HasHeight_ = false;
    HasLightmap_ = false;
    HasMetalness_ = false;
    HasNormalCamera_ = false;
    HasNormals_ = false;
    HasOpacity_ = false;
    HasReflection_ = false;
    HasShininess_ = false;
    HasSpecular_ = false;

    for (int i = 0; i < (long)TextureNames.size(); i++) {

        std::string Name = TextureNames[i];

        if (Name == "texture_ambient")
            HasAmbient_ = true;
        else if(Name == "texture_ambient_occlusion")
            HasAmbientOcclusion_ = true;
        else if(Name == "texture_base_color")
            HasBaseColor_ = true;
        else if(Name == "texture_diffuse")
            HasDiffuse_ = true;
        else if(Name == "texture_diffuse_roughness")
            HasDiffuseRoughness_ = true;
        else if(Name == "texture_displacement")
            HasDisplacement_ = true;
        else if(Name == "texture_emission_color")
            HasEmissionColor_ = true;
        else if(Name == "texture_emissive")
            HasEmissive_ = true;
        else if(Name == "texture_height")
            HasHeight_ = true;
        else if(Name == "texture_lightmap")
            HasLightmap_ = true;
        else if(Name == "texture_metalness")
            HasMetalness_ = true;
        else if(Name == "texture_normal_camera")
            HasNormalCamera_ = true;
        else if(Name == "texture_normals")
            HasNormals_ = true;
        else if(Name == "texture_opacity")
            HasOpacity_ = true;
        else if(Name == "texture_reflection")
            HasReflection_ = true;
        else if(Name == "texture_shininess")
            HasShininess_ = true;
        else if(Name == "texture_specular")
            HasSpecular_ = true;
    }





}

void ERS_STRUCT_Mesh::ResetTexture(const char* Name, int Offset, unsigned int ShaderProgram, unsigned int TextureID) {

    glUniform1i(glGetUniformLocation(ShaderProgram, Name), Offset);
    glActiveTexture(GL_TEXTURE0 + Offset);
    glBindTexture(GL_TEXTURE_2D, TextureID);

}

void ERS_STRUCT_Mesh::UpdateTransparencyStatus() {

    // Check Color Channels
    HasTransparency_ = false;
    for (unsigned long i = 0; i < TextureColorChannels_.size(); i++) {
        if (TextureColorChannels_[i] == 4) {
            HasTransparency_ = true;
        }
    }

}