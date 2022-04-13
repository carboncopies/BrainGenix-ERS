//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_FUNCTION_DrawMesh.h>


void ERS_FUNCTION_DrawMesh(ERS_STRUCT_Mesh* Mesh, ERS_STRUCT_OpenGLDefaults* OpenGLDefaults, std::shared_ptr<ERS_STRUCT_Shader> Shader) {

    Shader->SetMat4("model", Mesh->ModelMatrix);


    
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
    ERS_FUNCTION_ResetMeshTexture("texture_ambient1", 0, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_ambient_occlusion1", 1, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_base_color1", 2, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_diffuse1", 3, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_diffuse_roughness1", 4, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_displacement1", 5, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_emission_color1", 6, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_emissive1", 7, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_height1", 8, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_lightmap1", 9, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_metalness1", 10, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_normal_camera1", 11, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_normals1", 12, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_opacity1", 13, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_reflection1", 14, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_shininess1", 15, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_specular1", 16, ShaderProgram, ResetTexID);



    bool HasAmbient = false;
    bool HasAmbientOcclusion = false;
    bool HasBaseColor = false;
    bool HasDiffuse = false;
    bool HasDiffuseRoughness = false;
    bool HasDisplacement = false;
    bool HasEmissionColor = false;
    bool HasEmissive = false;
    bool HasHeight = false;
    bool HasLightmap = false;
    bool HasMetalness = false;
    bool HasNormalCamera = false;
    bool HasNormals = false;
    bool HasOpacity = false;
    bool HasRelfection = false;
    bool HasShininess = false;
    bool HasSpecular = false;


    // Iterate Through Textures
    for (unsigned int i = 0; i < Mesh->TextureIDs.size(); i++) {

        // Set To Proper Texture
        glActiveTexture(GL_TEXTURE0 + i);

        // Get Texture Number
        std::string Number;
        std::string Name = Mesh->TextureNames[i];
        int Type = 0;

        // Detect Type
        if (Name == "texture_ambient") {
            Number = std::to_string(AmbientHandle++);
            Type = 0;
            HasAmbient = true;
        } else if(Name == "texture_ambient_occlusion") {
            Number = std::to_string(AmbientOcclusionHandle++);
            Type = 1;
            HasAmbientOcclusion = true;
        } else if(Name == "texture_base_color") {
            Number = std::to_string(BaseColorHandle++);
            Type = 2;
            HasBaseColor = true;
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
        glBindTexture(GL_TEXTURE_2D, Mesh->TextureIDs[i]);

    }





    // Draw Mesh
    glBindVertexArray(Mesh->VAO);
    glDrawElements(GL_TRIANGLES, Mesh->NumberIndices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}