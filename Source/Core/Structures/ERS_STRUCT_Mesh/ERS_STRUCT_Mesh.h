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
    bool HasDiffuseRoughness; /**<Check If Has A Given Type Of Texture*/
    bool HasDisplacement; /**<Check If Has A Given Type Of Texture*/
    bool HasEmissionColor; /**<Check If Has A Given Type Of Texture*/
    bool HasEmissive; /**<Check If Has A Given Type Of Texture*/
    bool HasHeight; /**<Check If Has A Given Type Of Texture*/
    bool HasLightmap; /**<Check If Has A Given Type Of Texture*/
    bool HasMetalness; /**<Check If Has A Given Type Of Texture*/
    bool HasNormalCamera; /**<Check If Has A Given Type Of Texture*/
    bool HasNormals; /**<Check If Has A Given Type Of Texture*/
    bool HasOpacity; /**<Check If Has A Given Type Of Texture*/
    bool HasReflection; /**<Check If Has A Given Type Of Texture*/
    bool HasShininess; /**<Check If Has A Given Type Of Texture*/
    bool HasSpecular; /**<Check If Has A Given Type Of Texture*/


public:

    std::vector<ERS_STRUCT_Vertex> Vertices; /**<Array of Vertices*/
    std::vector<unsigned int> Indices; /**<Array of Indices*/
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

};
