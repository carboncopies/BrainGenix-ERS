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

    for (int i = 0; i < TextureNames.size(); i++) {

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

void ERS_STRUCT_Mesh::Draw(ERS_STRUCT_OpenGLDefaults* OpenGLDefaults, std::shared_ptr<ERS_STRUCT_Shader> Shader) {


    unsigned int AmbientHandle = 1;
    unsigned int AmbientOcclusionHandle = 1;
    unsigned int BaseColorHandle = 1;
    unsigned int DiffuseHandle = 1;
    unsigned int DiffuseRoughnessHandle = 1;
    unsigned int DisplacementHandle = 1;
    unsigned int EmissionColorHandle = 1;
    unsigned int EmissiveHandle = 1;
    unsigned int HeightHandle = 1;
    unsigned int LightmapHandle = 1;
    unsigned int MetalnessHandle = 1;
    unsigned int NormalCameraHandle = 1;
    unsigned int NormalsHandle = 1;
    unsigned int OpacityHandle = 1;
    unsigned int RelfectionHandle = 1;
    unsigned int ShininessHandle = 1;
    unsigned int SpecularHandle = 1;



    // Reset All Textures To Defaults
    unsigned int ShaderProgram = Shader->ShaderProgram;
    unsigned int ResetTexID = OpenGLDefaults->DefaultTexture_;
    ResetTexture("texture_ambient1", 0, ShaderProgram, ResetTexID);
    ResetTexture("texture_ambient_occlusion1", 1, ShaderProgram, ResetTexID);
    ResetTexture("texture_base_color1", 2, ShaderProgram, ResetTexID);
    ResetTexture("texture_diffuse1", 3, ShaderProgram, ResetTexID);
    ResetTexture("texture_diffuse_roughness1", 4, ShaderProgram, ResetTexID);
    ResetTexture("texture_displacement1", 5, ShaderProgram, ResetTexID);
    ResetTexture("texture_emission_color1", 6, ShaderProgram, ResetTexID);
    ResetTexture("texture_emissive1", 7, ShaderProgram, ResetTexID);
    ResetTexture("texture_height1", 8, ShaderProgram, ResetTexID);
    ResetTexture("texture_lightmap1", 9, ShaderProgram, ResetTexID);
    ResetTexture("texture_metalness1", 10, ShaderProgram, ResetTexID);
    ResetTexture("texture_normal_camera1", 11, ShaderProgram, ResetTexID);
    ResetTexture("texture_normals1", 12, ShaderProgram, ResetTexID);
    ResetTexture("texture_opacity1", 13, ShaderProgram, ResetTexID);
    ResetTexture("texture_reflection1", 14, ShaderProgram, ResetTexID);
    ResetTexture("texture_shininess1", 15, ShaderProgram, ResetTexID);
    ResetTexture("texture_specular1", 16, ShaderProgram, ResetTexID);



    // Iterate Through Textures
    for (unsigned int i = 0; i < TextureIDs.size(); i++) {

        // Set To Proper Texture
        glActiveTexture(GL_TEXTURE0 + i);

        // Get Texture Number
        std::string Number;
        std::string Name = TextureNames[i];
        int Type = 0;

        // Detect Type
        if (Name == "texture_ambient") {
            Number = std::to_string(AmbientHandle++);
            Type = 0;
        } else if(Name == "texture_ambient_occlusion") {
            Number = std::to_string(AmbientOcclusionHandle++);
            Type = 1;
        } else if(Name == "texture_base_color") {
            Number = std::to_string(BaseColorHandle++);
            Type = 2;
        } else if(Name == "texture_diffuse") {
            Number = std::to_string(DiffuseHandle++);
            Type = 3;
        } else if(Name == "texture_diffuse_roughness") {
            Number = std::to_string(DiffuseRoughnessHandle++);
            Type = 4;
        } else if(Name == "texture_displacement") {
            Number = std::to_string(DisplacementHandle++);
            Type = 5;
        } else if(Name == "texture_emission_color") {
            Number = std::to_string(EmissionColorHandle++);
            Type = 6;
        } else if(Name == "texture_emissive") {
            Number = std::to_string(EmissiveHandle++);
            Type = 7;
        } else if(Name == "texture_height") {
            Number = std::to_string(HeightHandle++);
            Type = 8;
        } else if(Name == "texture_lightmap") {
            Number = std::to_string(LightmapHandle++);
            Type = 9;
        } else if(Name == "texture_metalness") {
            Number = std::to_string(MetalnessHandle++);
            Type = 10;
        } else if(Name == "texture_normal_camera") {
            Number = std::to_string(NormalCameraHandle++);
            Type = 11;
        } else if(Name == "texture_normals") {
            Number = std::to_string(NormalsHandle++);
            Type = 12;
        } else if(Name == "texture_opacity") {
            Number = std::to_string(OpacityHandle++);
            Type = 13;
        } else if(Name == "texture_reflection") {
            Number = std::to_string(RelfectionHandle++);
            Type = 14;
        } else if(Name == "texture_shininess") {
            Number = std::to_string(ShininessHandle++);
            Type = 15;
        } else if(Name == "texture_specular") {
            Number = std::to_string(SpecularHandle++);
            Type = 16;
        }

        glUniform1i(glGetUniformLocation(Shader->ShaderProgram, (Name + Number).c_str()), Type);
        
        // Bind Texture
        glActiveTexture(GL_TEXTURE0 + Type);
        glBindTexture(GL_TEXTURE_2D, TextureIDs[i]);

    }







    // Draw Mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, NumberIndices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}


void ERS_STRUCT_Mesh::ResetTexture(const char* Name, int Offset, unsigned int ShaderProgram, unsigned int TextureID) {

    glUniform1i(glGetUniformLocation(ShaderProgram, Name), Offset);
    glActiveTexture(GL_TEXTURE0 + Offset);
    glBindTexture(GL_TEXTURE_2D, TextureID);

}