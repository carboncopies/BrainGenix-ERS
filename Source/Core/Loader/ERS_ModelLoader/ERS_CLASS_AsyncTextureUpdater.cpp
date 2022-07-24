//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_AsyncTextureUpdater.h>

// todo, implement system that searches over all models in the scene and loads the requested texture level
// also for now, we disable reference loading acceleration due to simplicity.

ERS_CLASS_AsyncTextureUpdater::ERS_CLASS_AsyncTextureUpdater(ERS_STRUCT_SystemUtils* SystemUtils, unsigned int Threads) {

    SystemUtils_ = SystemUtils;
    SystemUtils_->Logger_->Log("Initializing Automatic Texture Loading Subsystem", 5);

    

}