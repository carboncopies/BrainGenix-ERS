//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Third-Party Libraries (BG convention: use <> instead of "")
#include <vector>
#include <string>
#include <memory>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_Shader.h>
#include <ERS_STRUCT_Texture.h>
#include <ERS_STRUCT_Vertex.h>
#include <ERS_STRUCT_OpenGLDefaults.h>




/**
 * @brief This struct contains a mesh object that is a part of the model struct. It is ment for ERS Internal use.
 * 
 */
class ERS_STRUCT_Mesh {


private:

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


    std::vector<int> TextureColorChannels_; /**<List Of Number Of Color Channels In Texture*/
    bool HasTransparency_; /**<Indicates if this model has any transparent textures (detected by number of channels)*/


    /**
     * @brief Reset the texture to the default with the given name and offset.
     * 
     * @param Name 
     * @param Offset 
     */
    void ResetTexture(const char* Name, int Offset, unsigned int ShaderProgram, unsigned int TextureID);

public:

    std::vector<ERS_STRUCT_Vertex> Vertices; /**<Array of Mesh Vertices*/
    std::vector<unsigned int> Indices; /**<Array of Mesh Vertex Indices*/
    long NumberIndices; /**<Size of Indices Array*/
    unsigned int VAO; /**<Vertex Array Object OpenGL Handle*/


    std::vector<int> TextureReferences_; /**<Texture Reference IDs*/
    std::vector<unsigned int> TextureIDs; /**<Textur IDs*/
    std::vector<std::string> TextureNames; /**<Human Readable Names Of Textures*/
    

    /**
     * @brief Setup the mesh (create opengl objects, etc.)
     * 
     */
    void SetupMesh();

    /**
     * @brief Draw The Mesh (Called Once Per Frame For All Meshes To Be Rendered)
     * 
     * @param Shader 
     */
    void Draw(ERS_STRUCT_OpenGLDefaults* OpenGLDefaults, std::shared_ptr<ERS_STRUCT_Shader> Shader);


    /**
     * @brief Updates if the model is transparent or not
     * 
     */
    void UpdateTransparencyStatus(); 


};
