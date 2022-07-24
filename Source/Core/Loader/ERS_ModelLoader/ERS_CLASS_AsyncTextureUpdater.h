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
#include <yaml-cpp/yaml.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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

    std::vector<std::thread> TextureWorkerThreads_; /**<Vector containing thread objects for the worker pool*/
    std::mutex BlockThreads_; /**<Lock this to block all the treads (Usually done to add new items to the work queue)*/
    std::atomic_bool StopThreads_; /**<Used to start/stop threads*/
    std::vector<std::shared_ptr<ERS_STRUCT_Model*>> WorkItems_; /**<Models here have some work that needs to be done to them*/

    /**
     * @brief Method called as worker thread.
     * 
     */
    void TextureModifierWorkerThread();


    /**
     * @brief Adds a work item to the queue to load the minimum size texture to VRAM so we have something to display - this is kept in memory constantly.
     * Calling this will have the system check if the specified texture is already in system ram. If so, we'll push to gpu, if not, we'll load to system ram first.
     * 
     * @param Model 
     */
    void LoadInitialTextureVRAM(ERS_STRUCT_Model* Model);

    /**
     * @brief Adds a work item to the queue to load the specified texture (resolution) level.
     * Calling this will have the system check if the specified texture is already in system ram. If so, we'll push to gpu, if not, we'll load to system ram first.
     * If the level does not exist, no work will be done.
     * 
     * Texture levels are the inverse of mip maps, the higher the number, the higher the resolution.
     * We do this to simplify what goes on inside this class, apologies for the confusion.
     * 
     * @param Model 
     * @param TextureLevel 
     */
    void LoadTextureLevelVRAM(ERS_STRUCT_Model* Model, int TextureLevel);

    /**
     * @brief Add work item(s) to load all texture levels up to the specified range to VRAM.
     * Calling this will have the system check if the specified texture is already in system ram. If so, we'll push to gpu, if not, we'll load to system ram first.
     * If you put int for example 4 as the tex level, we'll load levels [1,2,3,4] (unless one of those is already loaded in which case we skip it)
     * 
     * 
     * Texture levels are the inverse of mip maps, the higher the number, the higher the resolution.
     * We do this to simplify what goes on inside this class, apologies for the confusion.
     * 
     * @param Model 
     * @param TextureLevel 
     */
    void LoadTextureLevelRangeVRAM(ERS_STRUCT_Model* Model, int TextureLevel);


    /**
     * @brief Unload a specific texture level from VRAM.
     * 
     * @param Model 
     * @param TextureLevel 
     */
    void UnloadTextureLevelVRAM(ERS_STRUCT_Model* Model, int TextureLevel);

    /**
     * @brief Does the same thing as unload level, but unloads every level down to the specified level from VRAM.
     * Example:
     * Loaded: [0,1,2,3,4,5,6], TextureLevel given is 4, we unload [6,5,4]
     * 
     * @param Model 
     * @param TextureLevel 
     */
    void UnloadTextureRangeVRAM(ERS_STRUCT_Model* Model, int TextureLevel);

    /**
     * @brief Unload all textures for the model because it's going to be removed from VRAM completely.
     * 
     * @param Model 
     */
    void UnloadInitialTextureVRAM(ERS_STRUCT_Model* Model);




    /**
     * @brief Adds a work item to the queue to load the minimum size texture to system RAM so we have something to display - this is kept in memory constantly.
     * 
     * @param Model 
     */
    void LoadInitialTextureRAM(ERS_STRUCT_Model* Model);

    /**
     * @brief Adds a work item to the queue to load the specified texture (resolution) level to system RAM.
     * If the level does not exist, no work will be done.
     * 
     * Texture levels are the inverse of mip maps, the higher the number, the higher the resolution.
     * We do this to simplify what goes on inside this class, apologies for the confusion.
     * 
     * @param Model 
     * @param TextureLevel 
     */
    void LoadTextureLevelRAM(ERS_STRUCT_Model* Model, int TextureLevel);

    /**
     * @brief Add work item(s) to load all texture levels up to the specified range to system RAM.
     * If you put int for example 4 as the tex level, we'll load levels [1,2,3,4] (unless one of those is already loaded in which case we skip it)
     * 
     * 
     * Texture levels are the inverse of mip maps, the higher the number, the higher the resolution.
     * We do this to simplify what goes on inside this class, apologies for the confusion.
     * 
     * @param Model 
     * @param TextureLevel 
     */
    void LoadTextureLevelRangeRAM(ERS_STRUCT_Model* Model, int TextureLevel);


    /**
     * @brief Unload a specific texture level from system RAM.
     * 
     * @param Model 
     * @param TextureLevel 
     */
    void UnloadTextureLevelRAM(ERS_STRUCT_Model* Model, int TextureLevel);

    /**
     * @brief Does the same thing as unload level, but unloads every level down to the specified level from system RAM.
     * Example:
     * Loaded: [0,1,2,3,4,5,6], TextureLevel given is 4, we unload [6,5,4]
     * 
     * @param Model 
     * @param TextureLevel 
     */
    void UnloadTextureRangeRAM(ERS_STRUCT_Model* Model, int TextureLevel);

    /**
     * @brief Unload all textures for the model from system RAM because it's going to be removed from memory completely.
     * 
     * @param Model 
     */
    void UnloadInitialTextureRAM(ERS_STRUCT_Model* Model);



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
     * @brief Sorts through all items in the scene and automatically adds them to the update queue.
     * Ideally this should be called every frame to ensure that the models marked for updates are updated.
     * 
     * @param Scene 
     */
    void SortModels(ERS_STRUCT_Scene* Scene);



};

