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

void ERS_CLASS_AssetStreamingManager::SetupTextureStreamer(GLFWwindow* Window) {
    AsyncTextureUpdater_ = std::make_unique<ERS_CLASS_AsyncTextureUpdater>(SystemUtils_, ResourceMonitor_.get(), Window);
}

void ERS_CLASS_AssetStreamingManager::UpdateSceneStreamingQueue(ERS_STRUCT_Scene* Scene, std::vector<ERS_STRUCT_Camera*> Cameras) {

    // Firstly, Extract List Of Models
    std::vector<ERS_STRUCT_Model*> Models;
    for (unsigned int i = 0; i < Scene->Models.size(); i++) {
        Models.push_back(Scene->Models[i].get());        
    }

    // Sort All Models Based On Distance From Each Camera
    std::vector<std::map<float, unsigned int>> DistancesFromCamera = SortModelsByDistanceFromCameras(Scene, Cameras);

    std::map<unsigned int, int> CameraUpdateQuota = CalculateCameraMaxUpdates(100, Cameras);
    SortSceneModels(CameraUpdateQuota, DistancesFromCamera, Scene);

}

void ERS_CLASS_AssetStreamingManager::SortSceneModels(std::map<unsigned int, int> CameraUpdatesQuota, std::vector<std::map<float, unsigned int>> DistancesFromCamera, ERS_STRUCT_Scene* Scene) {

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

            // std::cout<<ModelIndex<<std::endl;
            // if (Model->Name == "ApartmentCeiling") {
            //     std::cout<<"SceneSort: "<<ModelDistance<<std::endl;
            // }

            // Calculate Distance Per Level Cutoff
            int TargetTextureLevelVRAM;
            int TargetTextureLevelRAM;
            float DistancePerLevelVRAM = DistanceCutoffVRAM_ / NumberTextureLevels;
            float DistancePerLevelRAM = DistanceCutoffRAM_ / NumberTextureLevels;

            if (!UseQuadraticDistanceRolloff_) {
                TargetTextureLevelVRAM = NumberTextureLevels - round(ModelDistance / DistancePerLevelVRAM);
                TargetTextureLevelRAM = NumberTextureLevels - round(ModelDistance / DistancePerLevelRAM);
            } else {
                float EquationValue = pow(ModelDistance, QuadraticDistanceComponent_) + ModelDistance*LinearDistanceComponent_ + ConstantDistanceComponent_;
                TargetTextureLevelVRAM = NumberTextureLevels - round(EquationValue / DistancePerLevelVRAM);
                TargetTextureLevelRAM = NumberTextureLevels - round(EquationValue / DistancePerLevelRAM);
            }   
            
            // Cap Texture Level Range
            if (MinLOD_ > 0) {
                TargetTextureLevelRAM = std::max(MinLOD_, TargetTextureLevelRAM);
                TargetTextureLevelVRAM = std::max(MinLOD_, TargetTextureLevelVRAM);
            }
            if (MaxLOD_ > 0) {
                TargetTextureLevelRAM = std::min(MaxLOD_, TargetTextureLevelRAM);
                TargetTextureLevelVRAM = std::min(MaxLOD_, TargetTextureLevelVRAM);
            }
            if (TargetTextureLevelVRAM > NumberTextureLevels - 1) {
                TargetTextureLevelVRAM = NumberTextureLevels - 1;
            } else if (TargetTextureLevelVRAM < 0) {
                TargetTextureLevelVRAM = 0;
            }
            if (TargetTextureLevelRAM > NumberTextureLevels - 1) {
                TargetTextureLevelRAM = NumberTextureLevels - 1;
            } else if (TargetTextureLevelRAM < 0) {
                TargetTextureLevelRAM = 0;
            }
            if (MaxTextureResolution_ > 0 && Model->Textures_.size() > 0) {
                while (Model->Textures_[0].TextureLevels[TargetTextureLevelRAM].LevelResolution.first > MaxTextureResolution_) {
                    TargetTextureLevelRAM -=1;
                }
                while (Model->Textures_[0].TextureLevels[TargetTextureLevelVRAM].LevelResolution.first > MaxTextureResolution_) {
                    TargetTextureLevelVRAM -=1;
                }
                
            } else if (MaxTextureResolution_ < 0) {
                MaxTextureResolution_ = 0;
            }
            TargetTextureLevelVRAM = std::min(TargetTextureLevelVRAM, Model->TargetTextureLevelRAM);
  

            // Calculate Texture Size
            int TextureSizeVRAM = 0;
            int TextureSizeRAM = 0;
            for (unsigned int i = 0; i < Model->Textures_Loaded.size(); i++) {
                TextureSizeVRAM += Model->Textures_Loaded[i].TextureLevels[TargetTextureLevelVRAM].LevelMemorySizeBytes;
            }
            for (unsigned int i = 0; i < Model->Textures_Loaded.size(); i++) {
                TextureSizeRAM += Model->Textures_Loaded[i].TextureLevels[TargetTextureLevelRAM].LevelMemorySizeBytes;
            }

            // Check What Can Fit Into VRAM
            bool AlreadyHasVRAMLevel = Model->TextureLevelInVRAM_ >= TargetTextureLevelVRAM;
            bool VRAMUpdateQuotaExceeded = CameraVRAMUpdates >= MaxCameraUpdates;
            bool TextureFitsInVRAM = ResourceMonitor_->TextureFitsInVRAMBudget(TextureSizeVRAM);
            if (!AlreadyHasVRAMLevel && !VRAMUpdateQuotaExceeded && TextureFitsInVRAM) {
                if (Model->TargetTextureLevelVRAM < TargetTextureLevelVRAM) {
                    Model->TargetTextureLevelVRAM = TargetTextureLevelVRAM;
                    CameraVRAMUpdates++;
                }
            } else if (Model->TextureLevelInVRAM_ > TargetTextureLevelVRAM) {
                Model->TargetTextureLevelVRAM = TargetTextureLevelVRAM;
                CameraVRAMUpdates++;
            }


            // Check What Can Fit Into RAM
            bool AlreadyHasRAMLevel = Model->TextureLevelInRAM_ >= TargetTextureLevelRAM;
            bool RAMUpdateQuotaExceeded = CameraRAMUpdates >= MaxCameraUpdates;
            bool TextureFitsInRAM = ResourceMonitor_->TextureFitsInRAMBudget(TextureSizeRAM);
            if (!AlreadyHasRAMLevel && !RAMUpdateQuotaExceeded && TextureFitsInRAM) {
                if (Model->TargetTextureLevelRAM < TargetTextureLevelRAM) {
                    Model->TargetTextureLevelRAM = TargetTextureLevelRAM;
                    CameraRAMUpdates++;
                }
            } else if (Model->TextureLevelInRAM_ > TargetTextureLevelRAM) {
                Model->TargetTextureLevelRAM = TargetTextureLevelRAM;
                CameraRAMUpdates++;
            }

            

        }


    }

    ResourceMonitor_->UpdateTotals();


}

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
                    NextLevelTextureSize += CurrentModel->Textures_Loaded[i].TextureLevels[CurrentLevel].LevelMemorySizeBytes;
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
                    NextLevelTextureSize += CurrentModel->Textures_Loaded[i].TextureLevels[CurrentLevel].LevelMemorySizeBytes;
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
        TotalCameraPriorities += Cameras[i]->GetStreamingPriority();
    }
    TotalCameraPriorities = std::max(1, TotalCameraPriorities);

    // Calculate Percentage Of Total Updates Each Camera Should Have
    std::vector<float> CameraUpdatePercentages;
    for (unsigned int i = 0; i < Cameras.size(); i++) {
        CameraUpdatePercentages.push_back(Cameras[i]->GetStreamingPriority() / TotalCameraPriorities);
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


        float TotalDistance = glm::distance(Camera->GetPosition(), Scene->Models[i]->ModelPosition);
        
        // if (Scene->Models[i]->Name == "ApartmentCeiling") {
        //         std::cout<<"DistSort: "<<TotalDistance<<" Index: "<<i<<std::endl;
        // }

        // glm::vec3 UnscaledAngle = Camera->GetPosition() - Scene->Models[i]->ModelPosition;
        // float MaxSide = UnscaledAngle.x;
        // if (UnscaledAngle.y > MaxSide) {
        //     MaxSide = UnscaledAngle.y;
        // } else if (UnscaledAngle.z > MaxSide) {
        //     MaxSide = UnscaledAngle.z;
        // }
        // float ScaleFactor = (MaxSide + 0.000001f);
        // glm::vec3 ScaledAngle = UnscaledAngle / ScaleFactor;


        // glm::vec3 CubeDistance = ScaledAngle * Scene->Models[i]->BoxScale_;

        // float Distance = glm::distance(glm::vec3(0.0f), CubeDistance);

        glm::vec3 CubeBoundryBox = Scene->Models[i]->BoxScale_ * Scene->Models[i]->TrueModelScale;
        float ApproxCubeBoundryDistance = CubeBoundryBox.x;
        if (ApproxCubeBoundryDistance < CubeBoundryBox.y) {
            ApproxCubeBoundryDistance = CubeBoundryBox.y;
        } else if (ApproxCubeBoundryDistance < CubeBoundryBox.z) {
            ApproxCubeBoundryDistance = CubeBoundryBox.z;
        }
        

        float Distance = TotalDistance - ApproxCubeBoundryDistance;
        Distance = std::max(0.0f, Distance);
        
        Distances.insert(std::make_pair(Distance, i));
    }
    std::map<float, unsigned int> SortedDistances; 
    for (auto const& Entry : Distances) {
        SortedDistances.insert(std::make_pair(Entry.first, Entry.second));
        if (Scene->Models[Entry.second]->Name == "ApartmentCeiling") {
                std::cout<<"Found"<<Entry.second<<std::endl;
        }
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



