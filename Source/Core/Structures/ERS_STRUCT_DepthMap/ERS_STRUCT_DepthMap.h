//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <memory.h>
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")


/**
 * @brief This struct stores the opengl ids for a full depth map 'object'. 
 * Ie: the FBO id, Texture ID, etc.
 * 
 * Please Note: The depth maps are managed by 'ERS_CLASS_DepthMaps' not the light itself.
 * The depth maps are created and rendered-to by that class.
 * 
 */
struct ERS_STRUCT_DepthMap {

    unsigned int FrameBufferObjectID; /**<OpenGL Depth Map FBO ID*/
    std::vector<int> DepthMapTextureIndexes; /**<OpenGL Depth Map Texture Index In 2D Array, Multiple To Support CubeMaps For Point Lights*/
    bool Initialized = false; /**<Indiciates If The Target Is Initialized Or Not*/

};