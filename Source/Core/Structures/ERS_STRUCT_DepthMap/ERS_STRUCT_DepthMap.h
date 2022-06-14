//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <memory.h>
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <glm/glm.hpp>

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

    std::vector<unsigned int> FrameBufferObjectIDs; /**<OpenGL Depth Map FBO ID, Multiple to support point lights*/

    std::vector<int> DepthMapTextureIndexes; /**<OpenGL Depth Map Texture Index In 2D Array, Multiple To Support CubeMaps For Point Lights*/
    std::vector<glm::mat4> TransformationMatricies; /**<Used to store the transformation matrix for every index used in the texture array*/

    bool Initialized = false; /**<Indiciates If The Target Is Initialized Or Not*/

};