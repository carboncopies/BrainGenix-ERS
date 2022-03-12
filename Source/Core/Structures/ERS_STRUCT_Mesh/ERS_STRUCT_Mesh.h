//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Third-Party Libraries (BG convention: use <> instead of "")
#include <vector>
#include <string>
#include <memory>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glm/glm.hpp>


// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_Shader.h>
#include <ERS_STRUCT_Texture.h>
#include <ERS_STRUCT_Vertex.h>
#include <ERS_STRUCT_OpenGLDefaults.h>




/**
 * @brief This struct contains a mesh object that is a part of the model struct. It is ment for ERS Internal use.
 * 
 */
struct ERS_STRUCT_Mesh {



    unsigned int VBO; /**<Vertex buffer object OpenGL ID.*/
    unsigned int EBO; /**<OpenGL EBO Object ID*/

    bool HasAmbient_; /**<Check If Has A Given Type Of Texture*/
    bool HasAmbientOcclusion_; /**<Check If Has A Given Type Of Texture*/
    bool HasBaseColor_; /**<Check If Has A Given Type Of Texture*/
    bool HasDiffuse_; /**<Check If Has A Given Type Of Texture*/
    bool HasDiffuseRoughness_; /**<Check If Has A Given Type Of Texture*/
    bool HasDisplacement_; /**<Check If Has A Given Type Of Texture*/
    bool HasEmissionColor_; /**<Check If Has A Given Type Of Texture*/
    bool HasEmissive_; /**<Check If Has A Given Type Of Texture*/
    bool HasHeight_; /**<Check If Has A Given Type Of Texture*/
    bool HasLightmap_; /**<Check If Has A Given Type Of Texture*/
    bool HasMetalness_; /**<Check If Has A Given Type Of Texture*/
    bool HasNormalCamera_; /**<Check If Has A Given Type Of Texture*/
    bool HasNormals_; /**<Check If Has A Given Type Of Texture*/
    bool HasOpacity_; /**<Check If Has A Given Type Of Texture*/
    bool HasReflection_; /**<Check If Has A Given Type Of Texture*/
    bool HasShininess_; /**<Check If Has A Given Type Of Texture*/
    bool HasSpecular_; /**<Check If Has A Given Type Of Texture*/




    std::vector<ERS_STRUCT_Vertex> Vertices; /**<Array of Mesh Vertices*/
    std::vector<unsigned int> Indices; /**<Array of Mesh Vertex Indices*/
    long NumberIndices; /**<Size of Indices Array*/
    unsigned int VAO; /**<Vertex Array Object OpenGL Handle*/

    std::vector<int> TextureColorChannels_; /**<List Of Number Of Color Channels In Texture*/
    bool HasTransparency_; /**<Indicates if this model has any transparent textures (detected by number of channels)*/
    glm::mat4 ModelMatrix; /**<Model Matrix Given To The Shader When Rendering*/

    std::vector<int> TextureReferences_; /**<Texture Reference IDs*/
    std::vector<unsigned int> TextureIDs; /**<Textur IDs*/
    std::vector<std::string> TextureNames; /**<Human Readable Names Of Textures*/

    

    /**
     * @brief Setup the mesh (create opengl objects, etc.)
     * 
     */
    void SetupMesh();


    /**
     * @brief Reset the texture to the default with the given name and offset.
     * 
     * @param Name 
     * @param Offset 
     */
    void ResetTexture(const char* Name, int Offset, unsigned int ShaderProgram, unsigned int TextureID);

    /**
     * @brief Updates if the model is transparent or not
     * 
     */
    void UpdateTransparencyStatus(); 


};
