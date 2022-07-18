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
#include <ERS_STRUCT_Scene.h>
#include <ERS_STRUCT_Camera.h>


#include <ERS_CLASS_AssetStreamingSystemResourceMonitor.h>
#include <ERS_CLASS_AsyncTextureUpdater.h>


/**
 * @brief This class is responsible for indicating to the worker threads what needs to be done.
 * The other threads handle loading the vertex data and textures as well as unloading them when told to do so.
 * They also update the model struct to reflect the status of what's in GPU memory to ensure that there are no issues resulting from "cunfusion" as to what's in memory.
 * 
 * To summarize, this class looks at the current scene, and determines what's around the player camera(s) and determines if it needs to be in memory or not.
 * Additionally, it tells the loading system when to start loading more into memory, so that as the camera gets closer to an object, the higher res textures will be loaded.
 * 
 */
class ERS_CLASS_AssetStreamingManager {

private:

    // System Vars
    ERS_STRUCT_Scene* CurrentScene_ = nullptr;


    ERS_STRUCT_SystemUtils* SystemUtils_; /**<Struct containing essential services such as logging and Asset IO*/

    // Class Instances
    std::unique_ptr<ERS_CLASS_AssetStreamingSystemResourceMonitor> ResourceMonitor_; /**<Instance of System Monitor Used For Tex Streaming Choices*/


public:

    /**
     * @brief Constructor, sets up threads used to sort what models are prioritized, etc.
     * 
     * @param SystemUtils 
     */
    ERS_CLASS_AssetStreamingManager(ERS_STRUCT_SystemUtils* SystemUtils);

    /**
     * @brief Cleans up sorting threads, destroys class instance.
     * 
     */
    ~ERS_CLASS_AssetStreamingManager();

    /**
     * @brief Tells the streaming manager what the current scene is so that it knows what assets are actually relevant and what aren't.
     * We handle what the current scene is internally, so calling this every frame is okay, we check if the pointer is the same.
     * If you want to start loading another scene in advance (perhaps the camera is getting close to a scene switch, use the PreloadScene function).
     * 
     * @param CurrentScene 
     */
    void SetCurrentScene(ERS_STRUCT_Scene* CurrentScene);

    /**
     * @brief Not yet implemented!
     * 
     * Will start loading this new scene in the background so our loading time is shorter when we switch scenes.
     * 
     * @param Scene 
     */
    void PreloadScene(ERS_STRUCT_Scene* Scene);

    /**
     * @brief Give us a list containing the cameras in the scene so we know where we need to keep the textures loaded in versus where we can dump them.
     * Feel free to call this every frame or only when the cameras change, we monitor what's going on internally so it doesn't matter. (Just make sure we have no null pointers!)
     * 
     * @param Cameras 
     */
    void SetCameraStructs(std::vector<ERS_STRUCT_Camera*> Cameras);

};
