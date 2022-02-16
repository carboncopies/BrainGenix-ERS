//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <memory>


// Third-Party Libraries (BG convention: use <> instead of "")
#include <glad/glad.h>

#include <GLFW/glfw3.h>


// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_SystemUtils.h>
#include <ERS_STRUCT_Shader.h>



class ERS_CLASS_Grid {

private:

    std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<Shared Pointer To System Utils*/
    std::shared_ptr<ERS_STRUCT_Shader> GridShader_; /**<Pointer To Shader With Grid*/
    glm::mat4 GridModelArray_; /**<Grid Model Mat4*/

    unsigned int GridVBO_; /**<OpenGL ID To Grid Vertex Buffer Object*/
    unsigned int GridVAO_; /**<OpenGL ID To Grid Vertex Array Object*/


public:

    /**
     * @brief Construct a new ers class grid object
     * 
     * @param SystemUtils 
     */
    ERS_CLASS_Grid(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils, std::shared_ptr<ERS_STRUCT_Shader> GridShader);

    /**
     * @brief Destroy the ers class grid object
     * 
     */
    ~ERS_CLASS_Grid();

    
    /**
     * @brief Draw The Grid To The Viewport
     * 
     */
    void DrawGrid(glm::mat4 View);

};