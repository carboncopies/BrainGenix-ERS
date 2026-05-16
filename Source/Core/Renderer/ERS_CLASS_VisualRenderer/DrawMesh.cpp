//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <DrawMesh.h>


void ERS_FUNCTION_DrawMesh(ERS_STRUCT_Mesh* Mesh, ERS_STRUCT_OpenGLDefaults* OpenGLDefaults, ERS_STRUCT_Shader* Shader) {

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
    unsigned int ReflectionHandle = 1;
    unsigned int ShininessHandle = 1;
    unsigned int SpecularHandle = 1;



    // Reset All Textures To Defaults
    unsigned int ShaderProgram = Shader->ShaderProgram_;
    unsigned int ResetTexID = OpenGLDefaults->DefaultTexture_;
    ERS_FUNCTION_ResetMeshTexture("texture_ambient1", 0, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_ambient_occlusion1", 1, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_base_color1", 2, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_diffuse1", 2, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_displacement1", 3, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_emission_color1", 4, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_emissive1", 4, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_metalness1", 5, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_normal_camera1", 6, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_normals1", 6, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_shininess1", 7, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_height1", 8, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_diffuse_roughness1", 9, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_lightmap1", 10, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_opacity1", 11, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_reflection1", 12, ShaderProgram, ResetTexID);
    ERS_FUNCTION_ResetMeshTexture("texture_specular1", 13, ShaderProgram, ResetTexID);



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
    bool HasReflection = false;
    bool HasShininess = false;
    bool HasSpecular = false;


    // Iterate Through Textures
    for (unsigned int i = 0; i < Mesh->Textures_.size(); i++) {

        // Set To Proper Texture
        glActiveTexture(GL_TEXTURE0 + i);

        // Get Texture Type ID
        std::string Number;
        std::string Type = Mesh->Textures_[i]->Type;
        int TypeID = -1;

        // Detect Type
        if(Type == "texture_ambient") {
            Number = std::to_string(AmbientHandle++);
            TypeID = 0;
            HasAmbient = true;
        } else if(Type == "texture_ambient_occlusion") {
            Number = std::to_string(AmbientOcclusionHandle++);
            TypeID = 1;
            HasAmbientOcclusion = true;
        } else if(Type == "texture_base_color") {
            Number = std::to_string(BaseColorHandle++);
            TypeID = 2;
            HasBaseColor = true;
            HasDiffuse = true;
        } else if(Type == "texture_diffuse") {
            Number = std::to_string(DiffuseHandle++);
            TypeID = 2;
            HasDiffuse = true;
        } else if(Type == "texture_diffuse_roughness") {
            Number = std::to_string(DiffuseRoughnessHandle++);
            TypeID = 9;
            HasDiffuseRoughness = true;
        } else if(Type == "texture_displacement") {
            Number = std::to_string(DisplacementHandle++);
            TypeID = 3;
            HasDisplacement = true;
        } else if(Type == "texture_emission_color") {
            Number = std::to_string(EmissionColorHandle++);
            TypeID = 4;
            HasEmissionColor = true;
            HasEmissive = true;
        } else if(Type == "texture_emissive") {
            Number = std::to_string(EmissiveHandle++);
            TypeID = 4;
            HasEmissive = true;
        } else if(Type == "texture_height") {
            Number = std::to_string(HeightHandle++);
            TypeID = 8;
            HasHeight = true;
        } else if(Type == "texture_lightmap") {
            Number = std::to_string(LightmapHandle++);
            TypeID = 10;
            HasLightmap = true;
        } else if(Type == "texture_metalness") {
            Number = std::to_string(MetalnessHandle++);
            TypeID = 5;
            HasMetalness = true;
        } else if(Type == "texture_normal_camera") {
            Number = std::to_string(NormalCameraHandle++);
            TypeID = 6;
            HasNormalCamera = true;
        } else if(Type == "texture_normals") {
            Number = std::to_string(NormalsHandle++);
            TypeID = 6;
            HasNormals = true;
        } else if(Type == "texture_opacity") {
            Number = std::to_string(OpacityHandle++);
            TypeID = 11;
            HasOpacity = true;
        } else if(Type == "texture_reflection") {
            Number = std::to_string(ReflectionHandle++);
            TypeID = 12;
            HasReflection = true;
        } else if(Type == "texture_shininess") {
            Number = std::to_string(ShininessHandle++);
            TypeID = 7;
            HasShininess = true;
        } else if(Type == "texture_specular") {
            Number = std::to_string(SpecularHandle++);
            TypeID = 13;
            HasSpecular = true;
        }

        if (TypeID < 0) {
            continue;
        }

        glUniform1i(glGetUniformLocation(Shader->ShaderProgram_, (Type + Number).c_str()), TypeID);
        if (Type == "texture_base_color") {
            glUniform1i(glGetUniformLocation(Shader->ShaderProgram_, (std::string("texture_diffuse") + Number).c_str()), TypeID);
        } else if (Type == "texture_emission_color") {
            glUniform1i(glGetUniformLocation(Shader->ShaderProgram_, (std::string("texture_emissive") + Number).c_str()), TypeID);
        }

        // Check If Texture Has Any Levels
        if (Mesh->Textures_[i]->HasAnyLevelReady) {
            glActiveTexture(GL_TEXTURE0 + TypeID);
            glBindTexture(GL_TEXTURE_2D, Mesh->Textures_[i]->BestAvailableOpenGLID);
        } else {
            glActiveTexture(GL_TEXTURE0 + TypeID);
            glBindTexture(GL_TEXTURE_2D, OpenGLDefaults->Loadingtexture_);

        }

    }

    if ((*Mesh->TreatMissingTexturesAsTransparent_) && !HasDiffuse) {
        glUniform1i(glGetUniformLocation(Shader->ShaderProgram_, "texture_diffuse1"), 2);
        glActiveTexture(GL_TEXTURE0 + 2);
        glBindTexture(GL_TEXTURE_2D, OpenGLDefaults->TransparentTexture_);
    }

    // Set Uniforms
    Shader->SetBool("HasAmbient", HasAmbient);
    Shader->SetBool("HasAmbientOcclusion", HasAmbientOcclusion);
    Shader->SetBool("HasBaseColor", HasBaseColor);
    Shader->SetBool("HasDiffuse", HasDiffuse);
    Shader->SetBool("HasDiffuseRoughness", HasDiffuseRoughness);
    Shader->SetBool("HasDisplacement", HasDisplacement);
    Shader->SetBool("HasEmissionColor", HasEmissionColor);
    Shader->SetBool("HasEmissive", HasEmissive);
    Shader->SetBool("HasHeight", HasHeight);
    Shader->SetBool("HasLightmap", HasLightmap);
    Shader->SetBool("HasMetalness", HasMetalness);
    Shader->SetBool("HasNormalCamera", HasNormalCamera);
    Shader->SetBool("HasNormals", HasNormals);
    Shader->SetBool("HasOpacity", HasOpacity);
    Shader->SetBool("HasReflection", HasReflection);
    Shader->SetBool("HasShininess", HasShininess);
    Shader->SetBool("HasSpecular", HasSpecular);

    // Shadow Control Uniforms
    Shader->SetBool("CastDynamicShadows_", *Mesh->CastDynamicShadows_);
    Shader->SetBool("CastStaticShadows_", *Mesh->CastStaticShadows_);
    Shader->SetBool("ReceiveShadows_", *Mesh->ReceiveShadows_);
    



    // Draw Mesh
    glBindVertexArray(Mesh->VAO);
    glDrawElements(GL_TRIANGLES, Mesh->NumberIndices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}
