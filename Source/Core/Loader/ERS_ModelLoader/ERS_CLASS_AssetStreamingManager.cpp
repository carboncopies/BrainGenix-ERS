//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_AssetStreamingManager.h>


ERS_CLASS_AssetStreamingManager::ERS_CLASS_AssetStreamingManager(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;
    SystemUtils_->Logger_->Log("Initializing Asset Streaming Subsystem", 5);

    // Setup Subsystems
    ResourceMonitor_ = std::make_unique<ERS_CLASS_AssetStreamingSystemResourceMonitor>(SystemUtils_);

    // // Create Worker Thread
    // SystemUtils_->Logger_->Log("Starting Asset Streaming Subsystem Sorting Thread", 4);
    // SceneSortingThread_ = std::thread(&ERS_CLASS_AssetStreamingManager::WorkerThread, this);
    // SystemUtils_->Logger_->Log("Launched Asset Streaming Subsystem Sorting Thread", 3);

}

ERS_CLASS_AssetStreamingManager::~ERS_CLASS_AssetStreamingManager() {

    SystemUtils_->Logger_->Log("Asset Streaming Destructor Invoked", 6);

    // // Stop Thread
    // SystemUtils_->Logger_->Log("Locking Sorting Thread Mutex", 4);
    // SortingThreadMutex_.lock();

    // SystemUtils_->Logger_->Log("Sending Sorting Thread Join Command", 3);
    // SortingThreadShouldExit_ = true;
    // SortingThreadMutex_.unlock();

    // SystemUtils_->Logger_->Log("Joining Sorting Thread", 4);
    // SceneSortingThread_.join();
    // SystemUtils_->Logger_->Log("Joined Sorting Thread", 3);


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

    for (unsigned int i = 0; i < Scene->Models.size(); i++) {
        Scene->Models[i]->ModelLoadingStatus_ = "NoChange";
    }

    // Sort All Models Based On Distance From Each Camera
    std::vector<std::map<float, unsigned int>> DistancesFromCamera = SortModelsByDistanceFromCameras(Scene, Cameras);

    std::map<unsigned int, int> CameraUpdateQuota = CalculateCameraMaxUpdates(100, Cameras);
    //std::vector<ERS_STRUCT_Model*> NextLevelToVRAM = CreateListOfModelsToLoadNextLevelToVRAM(CameraUpdateQuota, Scene, DistancesFromCamera);


    // for (std::map<float, unsigned int>::iterator it = DistancesFromCamera[0].begin(); it != DistancesFromCamera[0].end(); ++it) {
    //     float Distance = it->first;
    //     ERS_STRUCT_Model* Model = Scene->Models[it->second].get();

    //     if (Distance < 4) {
    //         Model->ModelLoadingStatus_ = "LoadNextLevelToVRAM";
    //     } else {
    //         Model->ModelLoadingStatus_ = "NoChange";
    //     }

    // }

    // for (unsigned int i = 0; i < NextLevelToVRAM.size(); i++) {
    //     NextLevelToVRAM[i]->ModelLoadingStatus_ = "LoadNextLevelToVRAM";
    // }


    // Next, Based On Camera Priority, Create List Of Items Needing To Be Updated Most,
    // as well as items that should be loaded to RAM
    
    // Also, Create A List Of Items In Memory That Can Be Deallocated as they're the least close
    // or smallest, or just contribute to the view least 

    // Then, Go Down List, And Check If it'll fit into memory Of The Items Selected
    // Do that for each category such as VRAM and RAM

    // If Feasable And Not Already In Loading Queue, Add To Queue



}

void ERS_CLASS_AssetStreamingManager::SortSceneModels(std::map<unsigned int, int> CameraUpdatesQuota, std::vector<std::map<float, unsigned int>> DistancesFromCamera, ERS_STRUCT_Scene* Scene, float DistanceCutoff) {

    // Reset All Target Distances
    for (unsigned int i = 0; i < Scene->Models.size(); i++) {
        Scene->Models[i]->TargetTextureLevelVRAM = -1;
        Scene->Models[i]->TargetTextureLevelRAM = -1;
    }

    // Iterate Over All Cameras, Make Recomendations From There
    for (unsigned int CameraIndex = 0; CameraIndex < CameraUpdatesQuota.size(); CameraIndex++) {

        
        // Sort Models From Cameras
        unsigned int MaxCameraUpdates = CameraUpdatesQuota[CameraIndex];
        unsigned int CameraVRAMUpdates = 0;
        unsigned int CameraRAMUpdates = 0;
        for (auto DistanceMapIterator = DistancesFromCamera[0].begin(); DistanceMapIterator != DistancesFromCamera[0].end(); ++DistanceMapIterator) {
            
            // Get Parameters From Model Array
            float ModelDistance = DistanceMapIterator->first;
            unsigned int ModelIndex = DistanceMapIterator->second;
            ERS_STRUCT_Model* Model = Scene->Models[ModelIndex].get();
            int NumberTextureLevels = Model->MaxTextureLevel_ + 1;

            // Calculate Distance Per Level Cutoff
            float DistancePerLevel = DistanceCutoff / NumberTextureLevels;
            int TargetTextureLevel = round(ModelDistance / DistancePerLevel);
            if (Model->TargetTextureLevel < TargetTextureLevel) {
                Model->TargetTextureLevel = TargetTextureLevel;
            }
            

        }


    }


}

std::vector<ERS_STRUCT_Model*> ERS_CLASS_AssetStreamingManager::CreateListOfModelsToLoadNextLevelToVRAM(std::map<unsigned int, int> CameraUpdatesQuota, ERS_STRUCT_Scene* Scene, std::vector<std::map<float, unsigned int>> DistancesFromCamera) {

    // Create Vector Containing Models Which Should Be Pushed into RAM if possible
    std::vector<ERS_STRUCT_Model*> UpdateRequests;

    // Iterate Over All Cameras, And Determine What Needs To Be Loaded
    for (unsigned int x = 0; x < DistancesFromCamera.size(); x++) {

        // Setup Vars To Count Number Of Updates, etc.
        std::map<float, unsigned int> ModelDistances = DistancesFromCamera[x];
        int NumberUpdates = 0;


        std::cout<<ModelDistances.size()<<std::endl;
        for (unsigned int i = 0; i < ModelDistances.size(); i++) {

            if (i >= ModelDistances.size()) {
                std::cout<<i<<std::endl;
            }

            ERS_STRUCT_Model* CurrentModel = Scene->Models[ModelDistances[i]].get();
            if (NumberUpdates >= CameraUpdatesQuota[x]) {
                break;
            }

            // Check If Next Level Exists
            int CurrentLevel = CurrentModel->TextureLevelInVRAM_;
            if (CurrentLevel < CurrentModel->MaxTextureLevel_) {
                
                // Calculate Total Texture Size For Next Level
                int NextLevelTextureSize = 0;
                for (unsigned int z = 0; z < CurrentModel->Textures_Loaded.size(); z++) {
                    NextLevelTextureSize += CurrentModel->Textures_Loaded[i].LevelMemorySizeBytes[CurrentLevel];
                }

                // Check If Will Fit In Mem
                if (ResourceMonitor_->TextureFitsInVRAMBudget(NextLevelTextureSize)) {
                    UpdateRequests.push_back(CurrentModel);
                    CurrentModel->AssetLoadngStateVRAM = 1;
                    NumberUpdates++;
                }

            }

        }

    } 

    return UpdateRequests;


}
std::vector<ERS_STRUCT_Model*> ERS_CLASS_AssetStreamingManager::CreateListOfModelsToLoadNextLevelToRAM(std::map<unsigned int, int> CameraUpdatesQuota, ERS_STRUCT_Scene* Scene, std::vector<std::map<float, unsigned int>> DistancesFromCamera) {

    // Create Vector Containing Models Which Should Be Pushed into RAM if possible
    std::vector<ERS_STRUCT_Model*> UpdateRequests;

    // Iterate Over All Cameras, And Determine What Needs To Be Loaded
    for (unsigned int x = 0; x < DistancesFromCamera.size(); x++) {

        // Setup Vars To Count Number Of Updates, etc.
        std::map<float, unsigned int> ModelDistances = DistancesFromCamera[x];
        int NumberUpdates = 0;

        for (unsigned int i = 0; i < ModelDistances.size(); i++) {

            ERS_STRUCT_Model* CurrentModel = Scene->Models[ModelDistances[i]].get();
            if (NumberUpdates >= CameraUpdatesQuota[x]) {
                break;
            }

            // Check If Next Level Exists
            int CurrentLevel = CurrentModel->TextureLevelInRAM_;
            if (CurrentLevel < CurrentModel->MaxTextureLevel_) {
                
                // Calculate Total Texture Size For Next Level
                int NextLevelTextureSize = 0;
                for (unsigned int z = 0; z < CurrentModel->Textures_Loaded.size(); z++) {
                    NextLevelTextureSize += CurrentModel->Textures_Loaded[i].LevelMemorySizeBytes[CurrentLevel];
                }

                // Check If Will Fit In Mem
                if (ResourceMonitor_->TextureFitsInRAMBudget(NextLevelTextureSize)) {
                    UpdateRequests.push_back(CurrentModel);
                    CurrentModel->AssetLoadngStateRAM = 1;
                    NumberUpdates++;
                }

            }

        }

    } 

    return UpdateRequests;

}

std::map<unsigned int, int> ERS_CLASS_AssetStreamingManager::CalculateCameraMaxUpdates(int NumberMaxUpdates, std::vector<ERS_STRUCT_Camera*> Cameras) {

    // Sum Camera Priorities
    int TotalCameraPriorities = 0;
    for (unsigned int i = 0; i < Cameras.size(); i++) {
        TotalCameraPriorities += Cameras[i]->Priority_;
    }

    // Calculate Percentage Of Total Updates Each Camera Should Have
    std::vector<float> CameraUpdatePercentages;
    for (unsigned int i = 0; i < Cameras.size(); i++) {
        CameraUpdatePercentages.push_back(Cameras[i]->Priority_ / TotalCameraPriorities);
    }

    // Convert Update Percentages Into Actual Update Totals
    std::map<unsigned int, int> CameraUpdateMap;
    for (unsigned int i = 0; i < Cameras.size(); i++) {
        int CameraUpdateCount = round(CameraUpdatePercentages[i] * NumberMaxUpdates);
        CameraUpdateMap.insert(std::make_pair(i, CameraUpdateCount));
    }

    return CameraUpdateMap;

}

std::vector<std::map<float, unsigned int>> ERS_CLASS_AssetStreamingManager::SortModelsByDistanceFromCameras(ERS_STRUCT_Scene* Scene, std::vector<ERS_STRUCT_Camera*> Cameras) {

    std::vector<std::map<float, unsigned int>> DistancesFromCamera;
    for (unsigned int i = 0; i < Cameras.size(); i++) {
        DistancesFromCamera.push_back(SortModelsByDistanceFromCamera(Scene, Cameras[i]));
    }
    return DistancesFromCamera;

}

std::map<float, unsigned int> ERS_CLASS_AssetStreamingManager::SortModelsByDistanceFromCamera(ERS_STRUCT_Scene* Scene, ERS_STRUCT_Camera* Camera) {

    // Create Sorted List Of Distances Based On Position
    std::map<float, unsigned int> Distances;        
    for (unsigned int i = 0; i < Scene->Models.size(); i++) {
        float Distance = glm::distance(Camera->Position_, Scene->Models[i]->ModelPosition);
        Distances.insert(std::make_pair(Distance, i));
    }
    std::map<float, unsigned int> SortedDistances; 
    for (auto const& Entry : Distances) {
        SortedDistances.insert(std::make_pair(Entry.first, Entry.second));
    }

    return SortedDistances;
}

void ERS_CLASS_AssetStreamingManager::WorkerThread() {
    SystemUtils_->Logger_->Log("Asset Streaming Subsystem Sorting Thread Started", 3);
    while (true) {

        // Make Sure Nobody Messes With The Scene Pointers While We're Using Them
        std::unique_lock<std::mutex> Lock(SortingThreadMutex_);

        // Update Scene
        if (CurrentScene_ != nullptr && Cameras_.size() > 0) {
            UpdateSceneStreamingQueue(CurrentScene_, Cameras_);
        }

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
// void ERS_CLASS_AssetStreamingManager::PreloadScene(ERS_STRUCT_Scene* Scene) {
//     std::cout<<"WARNING: NOT YET IMPLEMENTED!\n";
// }

