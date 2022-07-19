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


void ERS_CLASS_AssetStreamingManager::UpdateSceneStreamingQueue(ERS_STRUCT_Scene* Scene, std::vector<ERS_STRUCT_Camera*> Cameras) {

    // Firstly, Extract List Of Models
    std::vector<ERS_STRUCT_Model*> Models;
    for (unsigned int i = 0; i < Scene->Models.size(); i++) {
        Models.push_back(Scene->Models[i].get());        
    }

    // Update camera struct with param about priority
    // Also update the model struct with a parameter that forces it to always be loaded in
    // 

    // Then, For Each Camera, Sort By Distance

    // Next, Based On Camera Priority, Create List Of Items Needing To Be Updated Most,
    // as well as items that should be loaded to RAM
    
    // Also, Create A List Of Items In Memory That Can Be Deallocated as they're the least close
    // or smallest, or just contribute to the view least 

    // Then, Go Down List, And Check If it'll fit into memory Of The Items Selected
    // Do that for each category such as VRAM and RAM

    // If Feasable And Not Already In Loading Queue, Add To Queue



}



void ERS_CLASS_AssetStreamingManager::WorkerThread() {
    SystemUtils_->Logger_->Log("Starting Scene Texture Prioritization Thread", 5);
    while (true) {

        // Make Sure Nobody Messes With The Scene Pointers While We're Using Them
        std::unique_lock<std::mutex> Lock(SortingThreadMutex_);

        // Update Scene
        UpdateSceneStreamingQueue(CurrentScene_, Cameras_);

        // Check If Thread Needs To Exit
        if (SortingThreadShouldExit_) {
            break;
        }

    }
}

void ERS_CLASS_AssetStreamingManager::SetCurrentScene(ERS_STRUCT_Scene* Scene) {
    HasSceneChanged_ = CurrentScene_ != Scene;
    CurrentScene_ = Scene;
}

void ERS_CLASS_AssetStreamingManager::SetCameraStructs(std::vector<ERS_STRUCT_Camera*> Cameras) {
    Cameras_ = Cameras;
}

// Not Yet Implemented
void ERS_CLASS_AssetStreamingManager::PreloadScene(ERS_STRUCT_Scene* Scene) {
    std::cout<<"WARNING: NOT YET IMPLEMENTED!\n";
}

