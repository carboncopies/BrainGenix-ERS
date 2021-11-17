//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the asset loader class.
    Additional Notes: None
    Date Created: 2021-11-17
*/

#include "AssetLoader.h"


// Asset Loader Constructor
AssetLoader(LoggerClass* Logger, YAML::Node* InitialSystemConfiguration) {

    // Log Initialization Start
    Logger->Log("Loading Subsystem Initialization Started", 5);

    // Copy Pointers
    Logger_ = Logger;
    InitialSystemConfiguration_ = InitialSystemConfiguration;

    // Log Initialization Finish
    Logger_->Log("Loading Subsystem Initialization Finished", 4);

}
