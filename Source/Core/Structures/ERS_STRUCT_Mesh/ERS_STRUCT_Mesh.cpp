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




    glUniform1i(glGetUniformLocation(Shader->ShaderProgram, "texture_ambient1"), 0);

    glActiveTexture(GL_TEXTURE0 + 0);
    glBindTexture(GL_TEXTURE0, OpenGLDefaults->DefaultTexture_);




    // Iterate Through Textures
    for (unsigned int i = 0; i < TextureIDs.size(); i++) {

        // Set To Proper Texture
        glActiveTexture(GL_TEXTURE0 + i);

        // Get Texture Number
        std::string Number;
        std::string Name = TextureNames[i];

        // Detect Type
        if (Name == "texture_ambient")
            Number = std::to_string(AmbientHandle++);
        else if(Name == "texture_ambient_occlusion")
            Number = std::to_string(AmbientOcclusionHandle++);
        else if(Name == "texture_base_color")
            Number = std::to_string(BaseColorHandle++);
        else if(Name == "texture_diffuse")
            Number = std::to_string(DiffuseHandle++);
        else if(Name == "texture_diffuse_roughness")
            Number = std::to_string(DiffuseRoughnessHandle++);
        else if(Name == "texture_displacement")
            Number = std::to_string(DisplacementHandle++);
        else if(Name == "texture_emission_color")
            Number = std::to_string(EmissionColorHandle++);
        else if(Name == "texture_emissive")
            Number = std::to_string(EmissiveHandle++);
        else if(Name == "texture_height")
            Number = std::to_string(HeightHandle++);
        else if(Name == "texture_lightmap")
            Number = std::to_string(LightmapHandle++);
        else if(Name == "texture_metalness")
            Number = std::to_string(MetalnessHandle++);
        else if(Name == "texture_normal_camera")
            Number = std::to_string(NormalCameraHandle++);
        else if(Name == "texture_normals")
            Number = std::to_string(NormalsHandle++);
        else if(Name == "texture_opacity")
            Number = std::to_string(OpacityHandle++);
        else if(Name == "texture_reflection")
            Number = std::to_string(RelfectionHandle++);
        else if(Name == "texture_shininess")
            Number = std::to_string(ShininessHandle++);
        else if(Name == "texture_specular")
            Number = std::to_string(SpecularHandle++);


        glUniform1i(glGetUniformLocation(Shader->ShaderProgram, (Name + Number).c_str()), i);
        
        // Bind Texture
        glBindTexture(GL_TEXTURE_2D, TextureIDs[i]);

    }







    // Draw Mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, NumberIndices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}