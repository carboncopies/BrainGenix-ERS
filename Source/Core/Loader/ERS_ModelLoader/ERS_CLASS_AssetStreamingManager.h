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
#include <ERS_STRUCT_Mesh.h>
#include <ERS_STRUCT_Texture.h>
#include <ERS_STRUCT_Vertex.h>
#include <ERS_STRUCT_Model.h>

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


};


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

};


/**
 * @brief This class gets information about how the system is performing to influence the streaming manager.
 * Essentially, it just informs the manager when we're about to run out of memory to ensure that we can unload things as needed.
 * Additionally, it does the opposite - informing us when we have more memory so that we know when we can load more textures into CPU RAM.
 * This class gets the CPU/System RAM info from the Hardware Information Class, and processes that info to make 'reccomendataions' to the manager.
 * 
 */
class ERS_CLASS_AssetStreamingSystemResourceMonitor {

};