//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <string>
#include <vector>
#include <thread>
#include <chrono>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_SystemUtils.h>



/**
 * @brief This class is responsible for managing the different textures that the model needs. 
 * As the Asset Streaming Manager Tells us what to do, here we use lots of threads to load the different textures and move them in and out of GPU memory and regular system RAM.
 * 
 * Texture Caching:
 * We have two different levels of caching here, firstly there's GPU ram for textures actively in use or frequently in use.
 * When a texture is deemed not importent enough to be moved out of that level, we store it in CPU memory until that's full. 
 * This lets us keep our textures as close to the GPU as possble which lets us reduce pop-in issues.
 * 
 */
class ERS_CLASS_AsyncTextureUpdater {

private:

    ERS_STRUCT_SystemUtils* SystemUtils_; /**<Struct containing essential services such as logging and Asset IO*/

public:

    /**
     * @brief Create instance of the texture updater. The optional threads parameters sets the limit on the number of threads we can use.
     * 
     * @param SystemUtils 
     * @param Threads Setting this to 0 will autodetect the number of threads we should use. Otherwise, we'll use whatever is passed in.
     */
    ERS_CLASS_AsyncTextureUpdater(ERS_STRUCT_SystemUtils* SystemUtils, unsigned int Threads = 0);

    /**
     * @brief Destroy the ers class asynctextureupdater object
     * 
     */
    ~ERS_CLASS_AsyncTextureUpdater();


    /**
     * @brief Adds a work item to the queue to load the minimum size texture so we have something to display - this is kept in memory constantly.
     * 
     * @param Model 
     */
    void LoadInitialTexture(ERS_STRUCT_Model* Model);

    /**
     * @brief Adds a work item to the queue to load the specified texture (resolution) level.
     * If the level does not exist, no work will be done.
     * 
     * Texture levels are the inverse of mip maps, the higher the number, the higher the resolution.
     * We do this to simplify what goes on inside this class, apologies for the confusion.
     * 
     * @param Model 
     * @param TextureLevel 
     */
    void LoadTextureLevel(ERS_STRUCT_Model* Model, int TextureLevel);

    /**
     * @brief Add work item(s) to load all texture levels up to the specified range.
     * If you put int for example 4 as the tex level, we'll load 0,1,2,3,4 (unless one of those is already loaded in which case we skip it)
     * 
     * 
     * Texture levels are the inverse of mip maps, the higher the number, the higher the resolution.
     * We do this to simplify what goes on inside this class, apologies for the confusion.
     * 
     * @param Model 
     * @param TextureLevel 
     */
    void LoadTextureLevelRange(ERS_STRUCT_Model* Model, int TextureLevel);


};

