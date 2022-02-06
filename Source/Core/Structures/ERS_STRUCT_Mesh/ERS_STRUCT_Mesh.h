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





/**
 * @brief This struct contains a mesh object that is a part of the model struct. It is ment for ERS Internal use.
 * 
 */
class ERS_STRUCT_Mesh {


private:

    unsigned int VBO; /**<Vertex buffer object OpenGL ID.*/
    unsigned int EBO; /**<OpenGL EBO Object ID*/


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
    void Draw(std::shared_ptr<ERS_STRUCT_Shader> Shader);

};
