//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once



// Standard Libraries (BG convention: use <> instead of "")
#include <string>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <FreeImage.h>

// Internal Libraries (BG convention: use <> instead of "")


// Structure To Hold 2D ERS Texture
struct ERS_STRUCT_Texture {

    // Set OpenGL Handles
    unsigned int ID;
    
    // Set ImageData For Deferred OpenGL Loading
    float Channels;
    float Width;
    float Height;
    FIBITMAP* ImageData;
    unsigned char* ImageBytes;
    bool HasImageData = false;

    // Set Metadata
    std::string Type;
    std::string Path;

};
