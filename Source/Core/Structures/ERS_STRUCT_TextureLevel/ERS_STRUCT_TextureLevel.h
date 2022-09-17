//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once



// Standard Libraries (BG convention: use <> instead of "")
#include <string>
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <FreeImage.h>

// Internal Libraries (BG convention: use <> instead of "")


// Structure To Hold 2D ERS Texture
struct ERS_STRUCT_TextureLevel {

    unsigned int LevelTextureOpenGLID; /**<List of opengl ids for every texture level*/
    unsigned int LevelTextureAssetID; /**<List of asset ids for every texture level*/

    bool LevelLoadedInRAM; /**<True/false for every level showing if that level is loaded in RAM*/
    bool LevelLoadedInVRAM; /**<True/false for every level showing f that level is loaded in VRAM*/

    bool AllocatedRAMBudget; /**<True/False indicating if the level has been allocated from the RAM budget*/
    long long AllocatedRAMSize; /**<Size in bytes of allocated memory for this texture*/
    bool AllocatedVRAMBudget; /**<True/False indicating if the level has been allocated from the VRAM budget*/
    long long AllocatedVRAMSize; /**<Size in bytes of allocated memory for this texture*/

    std::pair<int, int> LevelResolution; /**<List of all texture level's resolutions*/
    
    int LevelMemorySizeBytes; /**<Tells the system how many bytes every level will take*/
    
    FIBITMAP* LevelBitmap; /**<List of bitmaps for each level - contains the texture's RAM data.*/
    
    int LevelChannel; /**<List containing number of channels for every texture layer*/
    int Level; /**<What level is this (used for sorting internally)*/

};
