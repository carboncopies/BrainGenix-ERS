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

    ERS_STRUCT_SystemUtils* SystemUtils_; /**<Struct containing essential services such as logging and Asset IO*/


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

    

};
