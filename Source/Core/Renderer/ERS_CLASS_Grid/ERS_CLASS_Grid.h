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



class ERS_CLASS_Grid {

private:

    std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<Shared Pointer To System Utils*/

    unsigned int GridVBO_; /**<OpenGL ID To Grid Vertex Buffer Object*/
    unsigned int GridVAO_; /**<OpenGL ID To Grid Vertex Array Object*/





public:

    /**
     * @brief Construct a new ers class grid object
     * 
     * @param SystemUtils 
     */
    ERS_CLASS_Grid(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils);

    /**
     * @brief Destroy the ers class grid object
     * 
     */
    ~ERS_CLASS_Grid();


};