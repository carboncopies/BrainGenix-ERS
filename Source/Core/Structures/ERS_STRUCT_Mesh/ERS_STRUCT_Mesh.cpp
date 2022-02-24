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

}

void ERS_STRUCT_Mesh::Draw(ERS_STRUCT_OpenGLDefaults* OpenGLDefaults, std::shared_ptr<ERS_STRUCT_Shader> Shader) {


    /* These are the supported materials/textures that ERS will attempt to pass through

    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Model, Material, aiTextureType_AMBIENT, "texture_ambient");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Model, Material, aiTextureType_AMBIENT_OCCLUSION, "texture_ambient_occlusion");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Model, Material, aiTextureType_BASE_COLOR, "texture_base_color");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Model, Material, aiTextureType_DIFFUSE, "texture_diffuse");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Model, Material, aiTextureType_DIFFUSE_ROUGHNESS, "texture_diffuse_roughness");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Model, Material, aiTextureType_DISPLACEMENT, "texture_displacement");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Model, Material, aiTextureType_EMISSION_COLOR, "texture_emission_color");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Model, Material, aiTextureType_EMISSIVE, "texture_emissive");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Model, Material, aiTextureType_HEIGHT, "texture_height");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Model, Material, aiTextureType_LIGHTMAP, "texture_lightmap");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Model, Material, aiTextureType_METALNESS, "texture_metalness");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Model, Material, aiTextureType_NONE, "texture_none");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Model, Material, aiTextureType_NORMAL_CAMERA, "texture_normal_camera");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Model, Material, aiTextureType_NORMALS, "texture_normals");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Model, Material, aiTextureType_OPACITY, "texture_opacity");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Model, Material, aiTextureType_REFLECTION, "texture_reflection");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Model, Material, aiTextureType_SHININESS, "texture_shininess");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Model, Material, aiTextureType_SPECULAR, "texture_specular");
    LoadMaterialTextures(&OutputMesh.TextureReferences_, &OutputMesh.TextureNames, TexturePaths, Model, Material, aiTextureType_UNKNOWN, "texture_unknown");
    */


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
    unsigned int NoneHandle = 1;
    unsigned int NormalCameraHandle = 1;
    unsigned int NormalsHandle = 1;
    unsigned int OpacityHandle = 1;
    unsigned int RelfectionHandle = 1;
    unsigned int ShininessHandle = 1;
    unsigned int SpecularHandle = 1;
    unsigned int UnknownHandle = 1;


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
        else if(Name == "texture_none")
            Number = std::to_string(NoneHandle++);
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
        else if(Name == "texture_unknown")
            Number = std::to_string(UnknownHandle++);


        glUniform1i(glGetUniformLocation(Shader->ShaderProgram, (Name + Number).c_str()), i);
        
        std::cout<<Name + Number<<"|"<<TextureIDs[i]<<std::endl;

        // Bind Texture
        glBindTexture(GL_TEXTURE_2D, TextureIDs[i]);

    }



    // Check If Debug Mode
    if (true) {

        if (AmbientHandle == 1) {
            glUniform1i(glGetUniformLocation(Shader->ShaderProgram, "texture_ambient1"), GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, OpenGLDefaults->DefaultTexture_);
        }



    // unsigned int AmbientHandle = 1;
    // unsigned int AmbientOcclusionHandle = 1;
    // unsigned int BaseColorHandle = 1;
    // unsigned int DiffuseHandle = 1;
    // unsigned int DiffuseRoughnessHandle = 1;
    // unsigned int DisplacementHandle = 1;
    // unsigned int EmissionColorHandle = 1;
    // unsigned int EmissiveHandle = 1;
    // unsigned int HeightHandle = 1;
    // unsigned int LightmapHandle = 1;
    // unsigned int MetalnessHandle = 1;
    // unsigned int NoneHandle = 1;
    // unsigned int NormalCameraHandle = 1;
    // unsigned int NormalsHandle = 1;
    // unsigned int OpacityHandle = 1;
    // unsigned int RelfectionHandle = 1;
    // unsigned int ShininessHandle = 1;
    // unsigned int SpecularHandle = 1;
    // unsigned int UnknownHandle = 1;



    }




    // Draw Mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, NumberIndices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}