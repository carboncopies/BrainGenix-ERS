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
 * @brief This class gets information about how the system is performing to influence the streaming manager.
 * Essentially, it just informs the manager when we're about to run out of memory to ensure that we can unload things as needed.
 * Additionally, it does the opposite - informing us when we have more memory so that we know when we can load more textures into CPU RAM.
 * This class gets the CPU/System RAM info from the Hardware Information Class, and processes that info to make 'reccomendataions' to the manager.
 * 
 */
class ERS_CLASS_AssetStreamingSystemResourceMonitor {



};