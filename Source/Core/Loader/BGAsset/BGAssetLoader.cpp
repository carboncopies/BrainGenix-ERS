//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for loading assets from the scene.
    Additonal Notes: None
    Date Created: 2021-10-13
*/ 

#include "BGAssetLoader.h"



// Asset Loader Constructor
AssetLoader::AssetLoader(LoggerClass *Logger) {

    // Initialization Start
    Logger->Log("Initializing Asset Loader Class", 6);

    // Copy Pointer
    Logger_ = Logger;

    // Log Initialization
    Logger_->Log("Initialized Asset Loader Class", 5);

}