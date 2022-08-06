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
struct ERS_STRUCT_Texture {

    // New Loading System Info
    std::vector<unsigned int> LevelTextureOpenGLIDs; /**<List of opengl ids for every texture level*/
    std::vector<unsigned int> LevelTextureAssetIDs; /**<List of asset ids for every texture level*/
    std::vector<bool> LevelLoadedInRAM; /**<True/false for every level showing if that level is loaded in RAM*/
    std::vector<bool> LevelLoadedInVRAM; /**<True/false for every level showing f that level is loaded in VRAM*/  
    std::vector<std::pair<int, int>> LevelResolutions; /**<List of all texture level's resolutions*/
    std::vector<int> LevelMemorySizeBytes; /**<Tells the system how many bytes every level will take*/
    std::vector<FIBITMAP*> LevelBitmaps; /**<List of bitmaps for each level - contains the texture's RAM data.*/
    std::vector<int> LevelChannels; /**<List containing number of channels for every texture layer*/

    unsigned int BestAvailableOpenGLID = 0; /**<The current best ID we have loaded*/
    bool HasAnyLevelReady = false; /**<Tells the mesh renderer if we have any levels ready for it*/

    int TextureLevelInRAM_ = 0; /**<Determines the current texture level in RAM*/
    int TextureLevelInVRAM_ = 0; /**<Determines the current texture level in RAM*/

    int NumberChannels; /**<Shows the number of color channels in this texture*/

    // Set ImageData For Deferred OpenGL Loading
    // float Channels;
    // float Width;
    // float Height;
    // FIBITMAP* ImageData;
    // unsigned char* ImageBytes;
    // bool FreeImageBackend = true;
    bool HasImageData = false;

    // Set Metadata
    std::string Type;
    std::string Path;

};
