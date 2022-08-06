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

    unsigned int LevelTextureOpenGLIDs; /**<List of opengl ids for every texture level*/
    unsigned int LevelTextureAssetIDs; /**<List of asset ids for every texture level*/
    bool LevelLoadedInRAM; /**<True/false for every level showing if that level is loaded in RAM*/
    bool LevelLoadedInVRAM; /**<True/false for every level showing f that level is loaded in VRAM*/  
    std::pair<int, int> LevelResolutions; /**<List of all texture level's resolutions*/
    int LevelMemorySizeBytes; /**<Tells the system how many bytes every level will take*/
    FIBITMAP* LevelBitmaps; /**<List of bitmaps for each level - contains the texture's RAM data.*/
    int LevelChannels; /**<List containing number of channels for every texture layer*/

};
