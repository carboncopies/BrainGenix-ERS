//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_AssetStreamingManager.h>


ERS_CLASS_AssetStreamingManager::ERS_CLASS_AssetStreamingManager(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;
    SystemUtils_->Logger_->Log("Initializing Asset Streaming Subsystem", 5);

    // Setup Subsystems
    ResourceMonitor_ = std::make_unique<ERS_CLASS_AssetStreamingSystemResourceMonitor>(SystemUtils_);

    // Create Worker Thread

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

    // Sort All Models Based On Distance From Each Camera
    std::vector<std::map<float, unsigned int>> DistancesFromCamera = SortModelsByDistanceFromCameras(Scene, Cameras);



    // Next, Based On Camera Priority, Create List Of Items Needing To Be Updated Most,
    // as well as items that should be loaded to RAM
    
    // Also, Create A List Of Items In Memory That Can Be Deallocated as they're the least close
    // or smallest, or just contribute to the view least 

    // Then, Go Down List, And Check If it'll fit into memory Of The Items Selected
    // Do that for each category such as VRAM and RAM

    // If Feasable And Not Already In Loading Queue, Add To Queue



}

// TODO: Add visual contribution as a factor when determining what textures to load

std::vector<ERS_STRUCT_Model*> ERS_CLASS_AssetStreamingManager::CreateListOfModelsToLoadNextLevelToVRAM(std::map<unsigned int, int> CameraUpdatesQuota, ERS_STRUCT_Scene* Scene, std::vector<std::map<float, unsigned int>> DistancesFromCamera) {

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
    SystemUtils_->Logger_->Log("Starting Scene Texture Prioritization Thread", 5);
    while (true) {

        // Make Sure Nobody Messes With The Scene Pointers While We're Using Them
        std::unique_lock<std::mutex> Lock(SortingThreadMutex_);

        // Update Scene
        if (CurrentScene_ != nullptr) {
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
void ERS_CLASS_AssetStreamingManager::PreloadScene(ERS_STRUCT_Scene* Scene) {
    std::cout<<"WARNING: NOT YET IMPLEMENTED!\n";
}

