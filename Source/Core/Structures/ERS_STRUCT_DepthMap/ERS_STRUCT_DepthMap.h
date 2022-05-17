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
 * Please Note: The depth maps are managed by 'ERS_CLASS_DepthMaps' not the light itself.
 * The depth maps are created and rendered-to by that class.
 * 
 */
struct ERS_STRUCT_DepthMap {

    unsigned int FrameBufferObjectID; /**<OpenGL Depth Map FBO ID*/
    unsigned int DepthMapTextureID; /**<OpenGL Depth Map Texture ID*/
    
    int ResolutionX; /**<Width In Pixels Of The Depth Map*/
    int ResolutionY; /**<Height In Pixels Of The Depth Map*/
    

};