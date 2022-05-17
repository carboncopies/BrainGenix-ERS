//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <memory.h>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")


/**
 * @brief This struct stores the opengl ids for a full depth map 'object'. 
 * Ie: the FBO id, Texture ID, etc.
 * 
 */
struct ERS_STRUCT_DepthMap {

    unsigned int FrameBufferObjectID; /**<OpenGL Depth Map FBO ID*/
    unsigned int DepthMapTextureID; /**<OpenGL Depth Map Texture ID*/


};