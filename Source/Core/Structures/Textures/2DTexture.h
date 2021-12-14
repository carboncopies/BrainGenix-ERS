//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the 2d texture struct.
    Additonal Notes: None
    Date Created: 2021-11-04
*/

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <FreeImage.h>

// Structure To Hold 2D ERS Texture
struct ERS_OBJECT_TEXTURE_2D {

    // Set OpenGL Handles
    unsigned int ID;
    
    // Set ImageData For Deferred OpenGL Loading
    unsigned char* ImageData;

    // Set Metadata
    std::string Type;
    std::string Path;

};
