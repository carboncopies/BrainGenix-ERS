//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")


/**
 * @brief struct to contain default opengl ids for textures, objects, etc.
 * 
 */
struct ERS_STRUCT_OpenGLDefaults {

    unsigned int DefaultTexture_; /** Default Texture ID To Be Bound To*/
    unsigned int DefaultObject_; /** Default Object To Be Bound To*/
    unsigned int AllBlackTexture_; /**<Default All-Black Texture*/
    unsigned int AllWhiteTexture_; /**<Completely white texture*/

    unsigned int PointLightTexture_; /**<Texture ID For Point Light*/
    unsigned int DirectionalLightTexture_; /**<Texture ID For Directional Light*/
    unsigned int SpotLightTexture_; /**<Texture ID For Spot Light*/

};