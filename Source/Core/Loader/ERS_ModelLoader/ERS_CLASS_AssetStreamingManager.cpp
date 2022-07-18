//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_AssetStreamingManager.h>


ERS_CLASS_AssetStreamingManager::ERS_CLASS_AssetStreamingManager(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;
    SystemUtils_->Logger_->Log("Initializing Asset Streaming Subsystem", 5);

    // Setup Subsystems
    ResourceMonitor_ = std::make_unique<ERS_CLASS_AssetStreamingSystemResourceMonitor>(SystemUtils_);

}

ERS_CLASS_AssetStreamingManager::~ERS_CLASS_AssetStreamingManager() {

    SystemUtils_->Logger_->Log("Asset Streaming Destructor Invoked", 6);

}


void ERS_CLASS_AssetStreamingManager::SetCurrentScene(ERS_STRUCT_Scene* Scene) {
    CurrentScene_ = Scene;
}

void ERS_CLASS_AssetStreamingManager::SetCameraStructs(std::vector<ERS_STRUCT_Camera*> Cameras) {

    
}

// Not Yet Implemented
void ERS_CLASS_AssetStreamingManager::PreloadScene(ERS_STRUCT_Scene* Scene) {
    std::cout<<"WARNING: NOT YET IMPLEMENTED!\n";
}