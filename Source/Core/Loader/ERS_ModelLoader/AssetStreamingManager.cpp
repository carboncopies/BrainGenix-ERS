//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <AssetStreamingManager.h>


ERS_CLASS_AssetStreamingManager::ERS_CLASS_AssetStreamingManager(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;
    SystemUtils_->Logger_->Log("Initializing Asset Streaming Subsystem", 5);

    // Setup Subsystems
    ResourceMonitor_ = std::make_unique<ERS_CLASS_AssetStreamingSystemResourceMonitor>(SystemUtils_);

}

ERS_CLASS_AssetStreamingManager::~ERS_CLASS_AssetStreamingManager() {

    SystemUtils_->Logger_->Log("Asset Streaming Destructor Invoked", 6);

}

void ERS_CLASS_AssetStreamingManager::SetupTextureStreamer(GLFWwindow* Window, void* SharedEGLDisplay, void* SharedEGLConfig, void* SharedEGLContext, void* SharedEGLSurface) {
    AsyncTextureUpdater_ = std::make_unique<ERS_CLASS_AsyncTextureUpdater>(SystemUtils_, ResourceMonitor_.get(), Window, 0, SharedEGLDisplay, SharedEGLConfig, SharedEGLContext, SharedEGLSurface);
}

void ERS_CLASS_AssetStreamingManager::UpdateSceneStreamingQueue(ERS_STRUCT_Scene* Scene, std::vector<ERS_STRUCT_Camera*> Cameras) {

    // Firstly, Extract List Of Models
    std::vector<ERS_STRUCT_Model*> Models;
    for (unsigned int i = 0; i < Scene->Models.size(); i++) {
        Models.push_back(Scene->Models[i].get());        
    }

    // Sort All Models Based On Distance From Each Camera
    std::vector<std::vector<std::pair<float, unsigned int>>> DistancesFromCamera = SortModelsByDistanceFromCameras(Scene, Cameras);

    std::map<unsigned int, int> CameraUpdateQuota = CalculateCameraMaxUpdates(10, Cameras);
    SortSceneModels(CameraUpdateQuota, DistancesFromCamera, Scene);

}

void ERS_CLASS_AssetStreamingManager::SortSceneModels(std::map<unsigned int, int> CameraUpdatesQuota, std::vector<std::vector<std::pair<float, unsigned int>>> DistancesFromCamera, ERS_STRUCT_Scene* Scene) {

    // Iterate Over All Cameras, Make Recomendations From There
    for (unsigned int CameraIndex = 0; CameraIndex < CameraUpdatesQuota.size() && CameraIndex < DistancesFromCamera.size(); CameraIndex++) {

        
        // Sort Models From Cameras
        unsigned int MaxCameraUpdates = CameraUpdatesQuota[CameraIndex];
        unsigned int CameraVRAMUpdates = 0;
        unsigned int CameraRAMUpdates = 0;
        for (auto DistanceMapIterator = DistancesFromCamera[CameraIndex].begin(); DistanceMapIterator != DistancesFromCamera[CameraIndex].end(); ++DistanceMapIterator) {
            
            // Get Parameters From Model Array
            float ModelDistance = DistanceMapIterator->first;
            unsigned int ModelIndex = DistanceMapIterator->second;
            ERS_STRUCT_Model* Model = Scene->Models[ModelIndex].get();
            int NumberTextureLevels = Model->MaxTextureLevel_ + 1;

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
            
            // If User Defined LOD Settings Enabled, Use Them
            TargetTextureLevelVRAM = std::max(TargetTextureLevelVRAM, Model->UserLimitedMinLOD_);
            TargetTextureLevelRAM  = std::max(TargetTextureLevelRAM,  Model->UserLimitedMinLOD_);
            TargetTextureLevelVRAM = std::min(TargetTextureLevelVRAM, Model->UserLimitedMaxLOD_);
            TargetTextureLevelRAM  = std::min(TargetTextureLevelRAM,  Model->UserLimitedMaxLOD_);
            
            

            // Cap Texture Level Range
            if (MinLOD_ > 0) {
                TargetTextureLevelRAM = std::max(MinLOD_, TargetTextureLevelRAM);
                TargetTextureLevelVRAM = std::max(MinLOD_, TargetTextureLevelVRAM);
            }
            if (MaxLOD_ > 0) {
                TargetTextureLevelRAM = std::min(MaxLOD_, TargetTextureLevelRAM);
                TargetTextureLevelVRAM = std::min(MaxLOD_, TargetTextureLevelVRAM);
            }
            TargetTextureLevelVRAM = std::min(TargetTextureLevelVRAM, Model->TargetTextureLevelRAM);

            
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

            TargetTextureLevelRAM  = std::min(NumberTextureLevels - 1, TargetTextureLevelRAM);
            TargetTextureLevelVRAM = std::min(NumberTextureLevels - 1, TargetTextureLevelVRAM);
            TargetTextureLevelRAM  = std::max(0, TargetTextureLevelRAM);
            TargetTextureLevelVRAM = std::max(0, TargetTextureLevelVRAM);
  
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
                    
                    // Allocate
                    for (unsigned int i = 0; i < Model->Textures_Loaded.size(); i++) {
                        ResourceMonitor_->AllocateTextureVRAMFromBudget(Model->Textures_Loaded[i].TextureLevels[TargetTextureLevelVRAM].LevelMemorySizeBytes);
                        Model->Textures_Loaded[i].TextureLevels[TargetTextureLevelVRAM].AllocatedVRAMBudget = true;
                    }

                    Model->TargetTextureLevelVRAM = TargetTextureLevelVRAM;

                    if (Model->TargetTextureLevelVRAM > 0) {
                        CameraVRAMUpdates++;
                    }
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

                    // Allocate
                    for (unsigned int i = 0; i < Model->Textures_Loaded.size(); i++) {
                        ResourceMonitor_->AllocateTextureRAMFromBudget(Model->Textures_Loaded[i].TextureLevels[TargetTextureLevelRAM].LevelMemorySizeBytes);
                        Model->Textures_Loaded[i].TextureLevels[TargetTextureLevelRAM].AllocatedRAMBudget = true;
                    }

                    Model->TargetTextureLevelRAM = TargetTextureLevelRAM;

                    if (Model->TargetTextureLevelRAM > 0) {
                        CameraRAMUpdates++;
                    }
                }
            } else if (Model->TextureLevelInRAM_ > TargetTextureLevelRAM) {
                Model->TargetTextureLevelRAM = TargetTextureLevelRAM;
                CameraRAMUpdates++;
            }

            

        }


    }

    ResourceMonitor_->UpdateTotals();
    CheckHardwareLimitations(Scene);


}

void ERS_CLASS_AssetStreamingManager::CheckHardwareLimitations(ERS_STRUCT_Scene* Scene) {

    // Get Current Free RAM/VRAM Value
    ERS_STRUCT_HardwareInfo HWInfo = SystemUtils_->ERS_HardwareInformation_->GetHWInfo();
    unsigned long long int FreeRAM = HWInfo.Dynamic_.PhysicalMemoryFree;
    long long unsigned int FreeVRAM = SystemUtils_->RendererSettings_->VRAMBudget_ - SystemUtils_->RendererSettings_->CurrentVRAMUsage_;

    // Start Reducing Target Texture Levels (RAM n VRAM Limitation)
    if((FreeRAM < SystemUtils_->RendererSettings_->WarningLowRAMBytes) || (FreeVRAM < SystemUtils_->RendererSettings_->WarningLowVRAMBytes)){
        for (unsigned int i = 0; i < Scene->Models.size(); i++) {
            if (Scene->Models[i]->Textures_.size() > 0) {

                // Calculate Max Allowed Texture Level
                int TotalLevels = Scene->Models[i]->Textures_[0].TextureLevels.size();
                if (FreeRAM < SystemUtils_->RendererSettings_->WarningLowRAMBytes ){
            
                    unsigned long long int WarningThreshold= SystemUtils_->RendererSettings_->WarningLowRAMBytes;
                    int MaxTextureLevel = FreeRAM / ((double)WarningThreshold / (double)TotalLevels);

                    // Enforce Limit
                    Scene->Models[i]->TargetTextureLevelRAM  = std::min(Scene->Models[i]->TargetTextureLevelRAM, MaxTextureLevel);
                    Scene->Models[i]->TargetTextureLevelVRAM = std::min(Scene->Models[i]->TargetTextureLevelVRAM, MaxTextureLevel);
                }
                if (FreeVRAM < SystemUtils_->RendererSettings_->WarningLowVRAMBytes){

                    // Calculate Max Allowed Texture Level
                    unsigned long long int WarningThreshold = SystemUtils_->RendererSettings_->WarningLowVRAMBytes;
                    int MaxTextureLevel = FreeVRAM / ((double)WarningThreshold / (double)TotalLevels);

                    // Enforce Limit
                    Scene->Models[i]->TargetTextureLevelVRAM = std::min(Scene->Models[i]->TargetTextureLevelVRAM, MaxTextureLevel);
                }

            }
        }
    }


    // Hard RAM Cap (256MiB), Stops Any New Textures From Being Loaded
    if (FreeRAM < SystemUtils_->RendererSettings_->CriticalLowRAMBytes){
        AsyncTextureUpdater_->QueuePanic();
    }

    // Progressively Lower Texture Targets (Furthest-From-Camera First) While Under Sustained Memory Pressure
    ReduceTextureTargetsUnderMemoryPressure(Scene);


}

void ERS_CLASS_AssetStreamingManager::ReduceTextureTargetsUnderMemoryPressure(ERS_STRUCT_Scene* Scene) {

    // Get Current Free RAM/VRAM Values
    ERS_STRUCT_HardwareInfo HWInfo = SystemUtils_->ERS_HardwareInformation_->GetHWInfo();
    unsigned long long int FreeRAM = HWInfo.Dynamic_.PhysicalMemoryFree;
    unsigned long long int FreeVRAM = 0;
    if (SystemUtils_->RendererSettings_->CurrentVRAMUsage_ < SystemUtils_->RendererSettings_->VRAMBudget_) {
        FreeVRAM = SystemUtils_->RendererSettings_->VRAMBudget_ - SystemUtils_->RendererSettings_->CurrentVRAMUsage_;
    }

    // Hysteresis - Pressure Mode Is Entered At The Warning Threshold And Only Exited Once Free Memory
    // Recovers Past A Margin Above It. Targets Are Only Ever Shrunk Here (Never Raised), So Once The
    // Pressure Is Gone The Regular Distance-Based Sizing Re-Raises Them Naturally Without Ping-Ponging.
    const double RecoveryMarginFactor = 1.25;
    unsigned long long int RAMRecoveryTarget  = (unsigned long long int)(SystemUtils_->RendererSettings_->WarningLowRAMBytes * RecoveryMarginFactor);
    unsigned long long int VRAMRecoveryTarget = (unsigned long long int)(SystemUtils_->RendererSettings_->WarningLowVRAMBytes * RecoveryMarginFactor);

    if (FreeRAM < SystemUtils_->RendererSettings_->WarningLowRAMBytes) {
        if (!RAMPressureActive_) {
            SystemUtils_->Logger_->Log("Free RAM Below Warning Threshold, Entering Texture Streaming Memory Pressure Mode", 3);
        }
        RAMPressureActive_ = true;
    } else if (FreeRAM > RAMRecoveryTarget) {
        RAMPressureActive_ = false;
    }
    if (FreeVRAM < SystemUtils_->RendererSettings_->WarningLowVRAMBytes) {
        if (!VRAMPressureActive_) {
            SystemUtils_->Logger_->Log("Free VRAM Budget Below Warning Threshold, Entering Texture Streaming Memory Pressure Mode", 3);
        }
        VRAMPressureActive_ = true;
    } else if (FreeVRAM > VRAMRecoveryTarget) {
        VRAMPressureActive_ = false;
    }
    if (!RAMPressureActive_ && !VRAMPressureActive_) {
        return;
    }

    // Estimate How Many Bytes Must Be Reclaimed To Recover Past The Hysteresis Margin
    long long int RAMBytesToReclaim = 0;
    long long int VRAMBytesToReclaim = 0;
    if (RAMPressureActive_ && FreeRAM < RAMRecoveryTarget) {
        RAMBytesToReclaim = (long long int)(RAMRecoveryTarget - FreeRAM);
    }
    if (VRAMPressureActive_ && FreeVRAM < VRAMRecoveryTarget) {
        VRAMBytesToReclaim = (long long int)(VRAMRecoveryTarget - FreeVRAM);
    }

    // Sort Models By Ascending Importance - Furthest From The Cameras First (They Matter The Least Visually)
    std::vector<std::pair<float, unsigned int>> ModelsByDescendingDistance;
    for (unsigned int i = 0; i < Scene->Models.size(); i++) {

        float ClosestDistance = 0.0f;
        if (Cameras_.size() > 0) {
            ClosestDistance = std::numeric_limits<float>::max();
            for (unsigned int CameraIndex = 0; CameraIndex < Cameras_.size(); CameraIndex++) {
                if (Cameras_[CameraIndex] != nullptr) {
                    ClosestDistance = std::min(ClosestDistance, glm::distance(Cameras_[CameraIndex]->GetPosition(), Scene->Models[i]->ModelPosition));
                }
            }
            if (ClosestDistance == std::numeric_limits<float>::max()) {
                ClosestDistance = 0.0f;
            }
        }

        ModelsByDescendingDistance.push_back(std::make_pair(ClosestDistance, i));
    }
    std::sort(ModelsByDescendingDistance.begin(), ModelsByDescendingDistance.end(),
        [](const std::pair<float, unsigned int>& A, const std::pair<float, unsigned int>& B) { return A.first > B.first; });

    // Progressively Lower Texture Targets, One Level At A Time, Until The Budgets Recover Or Nothing More Can Be Lowered
    int ModelsReduced = 0;
    long long int EstimatedRAMReclaimedBytes = 0;
    long long int EstimatedVRAMReclaimedBytes = 0;
    for (auto ModelEntry = ModelsByDescendingDistance.begin(); ModelEntry != ModelsByDescendingDistance.end(); ++ModelEntry) {

        if (RAMBytesToReclaim <= 0 && VRAMBytesToReclaim <= 0) {
            break;
        }

        ERS_STRUCT_Model* Model = Scene->Models[ModelEntry->second].get();
        if (Model->Textures_.size() == 0 || Model->Textures_[0].TextureLevels.size() == 0) {
            continue;
        }

        // Never Lower Targets Below The Model's Floor (User/Global Minimum LOD, And Never Below Level 0)
        int MinFloor = std::max(0, Model->UserLimitedMinLOD_);
        if (MinLOD_ > 0) {
            MinFloor = std::max(MinFloor, MinLOD_);
        }
        MinFloor = std::min(MinFloor, Model->MaxTextureLevel_);

        bool ModelReduced = false;
        bool TargetReduced = true;
        while (TargetReduced) {
            TargetReduced = false;

            // Lower RAM Target
            if (RAMBytesToReclaim > 0 && Model->TargetTextureLevelRAM > MinFloor) {
                int DroppedLevel = std::min(Model->TextureLevelInRAM_, Model->TargetTextureLevelRAM);
                Model->TargetTextureLevelRAM--;
                ModelReduced = true;
                TargetReduced = true;

                // Estimate Reclaimed Bytes From The Level That Will Actually Be Unloaded
                if (DroppedLevel > Model->TargetTextureLevelRAM && DroppedLevel >= 0) {
                    for (unsigned int TextureIndex = 0; TextureIndex < Model->Textures_.size(); TextureIndex++) {
                        if (DroppedLevel < (int)Model->Textures_[TextureIndex].TextureLevels.size()) {
                            RAMBytesToReclaim -= Model->Textures_[TextureIndex].TextureLevels[DroppedLevel].LevelMemorySizeBytes;
                            EstimatedRAMReclaimedBytes += Model->Textures_[TextureIndex].TextureLevels[DroppedLevel].LevelMemorySizeBytes;
                        }
                    }
                }
            }

            // Lower VRAM Target
            if (VRAMBytesToReclaim > 0 && Model->TargetTextureLevelVRAM > MinFloor) {
                int DroppedLevel = std::min(Model->TextureLevelInVRAM_, Model->TargetTextureLevelVRAM);
                Model->TargetTextureLevelVRAM--;
                ModelReduced = true;
                TargetReduced = true;

                // Estimate Reclaimed Bytes From The Level That Will Actually Be Unloaded
                if (DroppedLevel > Model->TargetTextureLevelVRAM && DroppedLevel >= 0) {
                    for (unsigned int TextureIndex = 0; TextureIndex < Model->Textures_.size(); TextureIndex++) {
                        if (DroppedLevel < (int)Model->Textures_[TextureIndex].TextureLevels.size()) {
                            VRAMBytesToReclaim -= Model->Textures_[TextureIndex].TextureLevels[DroppedLevel].LevelMemorySizeBytes;
                            EstimatedVRAMReclaimedBytes += Model->Textures_[TextureIndex].TextureLevels[DroppedLevel].LevelMemorySizeBytes;
                        }
                    }
                }
            }

        }

        if (ModelReduced) {
            ModelsReduced++;
        }

    }

    // Enqueue The Affected Models So The Async Updater's Normal Downward Pass Actually Unloads The Dropped Levels
    if (ModelsReduced > 0) {
        AsyncTextureUpdater_->SortModels(Scene);
        SystemUtils_->Logger_->Log(std::string("Memory Pressure Response: Lowered Texture Targets For '")
            + std::to_string(ModelsReduced) + "' Model(s) (Furthest From Camera First), Estimated Reclaim '"
            + std::to_string(EstimatedRAMReclaimedBytes / 1048576) + "' MiB RAM, '"
            + std::to_string(EstimatedVRAMReclaimedBytes / 1048576) + "' MiB VRAM", 4);
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

        for (auto ModelDistanceIterator = ModelDistances.begin(); ModelDistanceIterator != ModelDistances.end(); ++ModelDistanceIterator) {


            ERS_STRUCT_Model* CurrentModel = Scene->Models[ModelDistanceIterator->second].get();
            if (NumberUpdates >= CameraUpdatesQuota[x]) {
                break;
            }

            // Check If Next Level Exists
            int CurrentLevel = CurrentModel->TextureLevelInVRAM_;
            if (CurrentLevel < CurrentModel->MaxTextureLevel_) {
                
                // Calculate Total Texture Size For Next Level
                int NextLevelTextureSize = 0;
                for (unsigned int z = 0; z < CurrentModel->Textures_Loaded.size(); z++) {
                    NextLevelTextureSize += CurrentModel->Textures_Loaded[z].TextureLevels[CurrentLevel].LevelMemorySizeBytes;
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

        for (auto ModelDistanceIterator = ModelDistances.begin(); ModelDistanceIterator != ModelDistances.end(); ++ModelDistanceIterator) {

            ERS_STRUCT_Model* CurrentModel = Scene->Models[ModelDistanceIterator->second].get();
            if (NumberUpdates >= CameraUpdatesQuota[x]) {
                break;
            }

            // Check If Next Level Exists
            int CurrentLevel = CurrentModel->TextureLevelInRAM_;
            if (CurrentLevel < CurrentModel->MaxTextureLevel_) {
                
                // Calculate Total Texture Size For Next Level
                int NextLevelTextureSize = 0;
                for (unsigned int z = 0; z < CurrentModel->Textures_Loaded.size(); z++) {
                    NextLevelTextureSize += CurrentModel->Textures_Loaded[z].TextureLevels[CurrentLevel].LevelMemorySizeBytes;
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
        CameraUpdatePercentages.push_back(static_cast<float>(Cameras[i]->GetStreamingPriority()) / static_cast<float>(TotalCameraPriorities));
    }

    // Convert Update Percentages Into Actual Update Totals
    std::map<unsigned int, int> CameraUpdateMap;
    for (unsigned int i = 0; i < Cameras.size(); i++) {
        int CameraUpdateCount = round(CameraUpdatePercentages[i] * NumberMaxUpdates);
        CameraUpdateMap.insert(std::make_pair(i, CameraUpdateCount));
    }

    return CameraUpdateMap;

}

std::vector<std::vector<std::pair<float, unsigned int>>> ERS_CLASS_AssetStreamingManager::SortModelsByDistanceFromCameras(ERS_STRUCT_Scene* Scene, std::vector<ERS_STRUCT_Camera*> Cameras) {

    std::vector<std::vector<std::pair<float, unsigned int>>> DistancesFromCamera;
    for (unsigned int i = 0; i < Cameras.size(); i++) {
        DistancesFromCamera.push_back(SortModelsByDistanceFromCamera(Scene, Cameras[i]));
    }
    return DistancesFromCamera;

}

std::vector<std::pair<float, unsigned int>> ERS_CLASS_AssetStreamingManager::SortModelsByDistanceFromCamera(ERS_STRUCT_Scene* Scene, ERS_STRUCT_Camera* Camera) {

    // Create Sorted List Of Distances Based On Position
    std::vector<std::pair<float, unsigned int>> Distances;        
    for (unsigned int i = 0; i < Scene->Models.size(); i++) {


        float TotalDistance = glm::distance(Camera->GetPosition(), Scene->Models[i]->ModelPosition);
  
        glm::vec3 CubeBoundryBox = Scene->Models[i]->BoxScale_ * Scene->Models[i]->TrueModelScale;
        float ApproxCubeBoundryDistance = CubeBoundryBox.x;
        if (ApproxCubeBoundryDistance < CubeBoundryBox.y) {
            ApproxCubeBoundryDistance = CubeBoundryBox.y;
        } else if (ApproxCubeBoundryDistance < CubeBoundryBox.z) {
            ApproxCubeBoundryDistance = CubeBoundryBox.z;
        }
        float Distance = TotalDistance - ApproxCubeBoundryDistance;

        // Cap Distance At 0 - We don't want negative distance, (thats happens if the camera is inside the bounding box of the model)
        Distance = std::max(0.0f, Distance);
        Distances.push_back(std::make_pair(Distance, i));
    }


    std::vector<std::pair<float, unsigned int>> SortedDistances; 
    for (std::pair<float, unsigned int> Entry : Distances) {
        SortedDistances.push_back(std::make_pair(Entry.first, Entry.second));
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

void ERS_CLASS_AssetStreamingManager::PreloadScene(ERS_STRUCT_Scene* Scene) {

    // Sanity Checks - Don't Preload Invalid Scenes, The Scene We're Already Handling, Or Before The Texture Updater Exists
    if (Scene == nullptr || Scene == CurrentScene_ || AsyncTextureUpdater_ == nullptr) {
        return;
    }

    // Schedule Every Model To Have Its Baseline (Lowest Useful) Texture Level In RAM
    int ModelsScheduled = 0;
    for (unsigned int i = 0; i < Scene->Models.size(); i++) {
        ERS_STRUCT_Model* Model = Scene->Models[i].get();

        // Skip Models Without Any Texture Level Metadata (Nothing Can Be Loaded Yet)
        if (Model->Textures_.size() == 0 || Model->Textures_[0].TextureLevels.size() == 0) {
            continue;
        }

        // Compute Baseline Level - Level 0, Raised By The User/Global Minimum LOD Floors, Capped By What The Asset Has
        int BaselineLevel = 0;
        BaselineLevel = std::max(BaselineLevel, Model->UserLimitedMinLOD_);
        if (MinLOD_ > 0) {
            BaselineLevel = std::max(BaselineLevel, MinLOD_);
        }
        BaselineLevel = std::min(BaselineLevel, Model->UserLimitedMaxLOD_);
        BaselineLevel = std::min(BaselineLevel, Model->MaxTextureLevel_);

        // Skip Models That Already Have (Or Are Already Scheduled To Have) The Baseline Level Or Better
        if (Model->TextureLevelInRAM_ >= BaselineLevel || Model->TargetTextureLevelRAM >= BaselineLevel) {
            continue;
        }

        // Calculate How Much RAM The New Levels Will Need
        unsigned long BytesNeeded = 0;
        int FirstLevelToLoad = std::max(Model->TextureLevelInRAM_, Model->TargetTextureLevelRAM) + 1;
        for (unsigned int TextureIndex = 0; TextureIndex < Model->Textures_.size(); TextureIndex++) {
            int NumberTextureLevels = Model->Textures_[TextureIndex].TextureLevels.size();
            for (int Level = FirstLevelToLoad; Level <= BaselineLevel && Level < NumberTextureLevels; Level++) {
                BytesNeeded += Model->Textures_[TextureIndex].TextureLevels[Level].LevelMemorySizeBytes;
            }
        }

        // Only Schedule While The Resource Monitor Says It Fits - The Loader Re-Checks The Budget Again At Load Time
        if (!ResourceMonitor_->TextureFitsInRAMBudget(BytesNeeded)) {
            SystemUtils_->Logger_->Log(std::string("Skipping Preload Of Model '") + Model->Name + "', Will Not Fit In RAM Budget", 4);
            continue;
        }

        // Set The RAM Target Only (VRAM Staging Is Left Untouched) And Enqueue The Model For A RAM-Only Load
        Model->TargetTextureLevelRAM = BaselineLevel;
        AsyncTextureUpdater_->QueueRAMOnlyUpdate(i, Scene);
        ModelsScheduled++;

    }

    if (ModelsScheduled > 0) {
        SystemUtils_->Logger_->Log(std::string("Preloading Scene '") + Scene->SceneName + "', Scheduled Baseline RAM Texture Loads For '" + std::to_string(ModelsScheduled) + "' Model(s)", 4);
    }

}

void ERS_CLASS_AssetStreamingManager::SetCameraStructs(std::vector<ERS_STRUCT_Camera*> Cameras) {
    Cameras_ = Cameras;
}
