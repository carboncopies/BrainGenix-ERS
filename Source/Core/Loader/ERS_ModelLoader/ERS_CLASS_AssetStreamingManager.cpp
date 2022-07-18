//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_AssetStreamingManager.h>


ERS_CLASS_AssetStreamingManager::ERS_CLASS_AssetStreamingManager(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;
    SystemUtils_->Logger_->Log("Initializing Asset Streaming Subsystem", 5);

    // Setup Subsystems
    ResourceMonitor_ = std::make_shared<ERS_CLASS_AssetStreamingSystemResourceMonitor>(SystemUtils_);

}