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
    
    // New Loading System Info
    std::vector<unsigned int> TextureIDs; /**<List of opengl ids for every texture level*/
    std::vector<bool> LoadedInRAM; /**<True/false for every level showing if that level is loaded in RAM*/
    std::vector<bool> LoadedInVRAM; /**<True/false for every level showing f that level is loaded in VRAM*/  
    std::vector<std::pair<int, int>> LevelResolutions; /**<List of all texture level's resolutions*/
    int NumberChannels; /**<Shows the number of color channels in this texture*/

    // Set ImageData For Deferred OpenGL Loading
    float Channels;
    float Width;
    float Height;
    FIBITMAP* ImageData;
    unsigned char* ImageBytes;
    bool FreeImageBackend = true;
    bool HasImageData = false;

    // Set Metadata
    std::string Type;
    std::string Path;

};
