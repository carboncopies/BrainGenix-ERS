//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_AsyncTextureUpdater.h>

// todo, implement system that searches over all models in the scene and loads the requested texture level
// also for now, we disable reference loading acceleration due to simplicity.

ERS_CLASS_AsyncTextureUpdater::ERS_CLASS_AsyncTextureUpdater(ERS_STRUCT_SystemUtils* SystemUtils, GLFWwindow* Window, unsigned int Threads) {

    SystemUtils_ = SystemUtils;
    MainThreadWindowContext_ = Window;
    SystemUtils_->Logger_->Log("Initializing Automatic Texture Loading Subsystem", 5);

    // If Threads Is Left To Autodetect, Use That
    if (Threads <= 0) {

        // Check If Config Has Param
        if ((*SystemUtils_->LocalSystemConfiguration_)["TextureLoaderThreadCount"]) {
            SystemUtils_->Logger_->Log("Using Config File To Set Number Of Texture Loader Threads", 4);
            Threads = (*SystemUtils_->LocalSystemConfiguration_)["TextureLoaderThreadCount"].as<int>();
        } else {
            SystemUtils_->Logger_->Log("Autodetecting Number Of Threads To Use", 4);
            Threads = std::thread::hardware_concurrency() - 2;
            if (Threads < 2) {
                Threads = 2;
                SystemUtils_->Logger_->Log("Less Than Two CPUs Detected, Will Use Two Threads Regardless, However Frame Drops May Happen", 6);
            }
        }
    }

    SetNumThreads(1);//Threads);
    SetupThreads();

}

ERS_CLASS_AsyncTextureUpdater::~ERS_CLASS_AsyncTextureUpdater() {

    SystemUtils_->Logger_->Log("Automatic Texture Loading Subsystem Shutdown Invoked", 6);


    TeardownThreads();

    // Cleanup
    SystemUtils_->Logger_->Log("Cleaning Up OpenGL/GLFW", 6);
    glfwTerminate();

}


bool ERS_CLASS_AsyncTextureUpdater::LoadImageDataRAM(ERS_STRUCT_Texture* Texture, int Level, bool LogEnable) {

    // Check If Requested Level Exists
    if (Level < 0) {
        SystemUtils_->Logger_->Log("Texture Updater Tried To Load Negative Texture Level", 8, LogEnable);
        return false;
    } else if (Level > (int)Texture->LevelResolutions.size()) {
        SystemUtils_->Logger_->Log("Texture Updater Tried To Load Nonexistant Texture Level", 8, LogEnable);
        return false;
    }

    // Check If Level Already Loaded
    if (Texture->LevelBitmaps[Level] != nullptr) {
        return false;
    }


    // Load Image Data
    ERS_STRUCT_IOData ImageData;
    long LevelAssetID = Texture->LevelTextureAssetIDs[Level];
    SystemUtils_->ERS_IOSubsystem_->ReadAsset(LevelAssetID, &ImageData);

    // Decode Image
    FIMEMORY* FIImageData = FreeImage_OpenMemory(ImageData.Data.get(), ImageData.Size_B);
    FREE_IMAGE_FORMAT Format = FreeImage_GetFileTypeFromMemory(FIImageData);
    FIBITMAP* Image = FreeImage_LoadFromMemory(Format, FIImageData);
    FreeImage_CloseMemory(FIImageData);


    // Detect Width/Height
    int Width = FreeImage_GetWidth(Image);
    int Height = FreeImage_GetHeight(Image);
    if (Width <= 0) {
        SystemUtils_->Logger_->Log(std::string("Error Loading Texture '") + Texture->Path
        + "', Level '" + std::to_string(Level) + "' With ID '" + std::to_string(LevelAssetID)
        + "' Width Is <1", 8, LogEnable);
        FreeImage_Unload(Image);
        return false;
    }
    if (Height <= 0) {
        SystemUtils_->Logger_->Log(std::string("Error Loading Texture '") + Texture->Path
        + "', Level '" + std::to_string(Level) + "' With ID '" + std::to_string(LevelAssetID)
        + "' Height Is <1", 8, LogEnable);
        FreeImage_Unload(Image);
        return false;
    }

    std::pair<int, int> TargetWidthHeight = Texture->LevelResolutions[Level];
    if ((TargetWidthHeight.first != Width) && (TargetWidthHeight.first != -1)) {
        SystemUtils_->Logger_->Log(std::string("Error Loading Texture '") + Texture->Path
        + "', Level '" + std::to_string(Level) + "' With ID '" + std::to_string(LevelAssetID)
        + "' Width Does Not Match Metadata Target", 8, LogEnable);
        FreeImage_Unload(Image);
        return false;
    }
    if ((TargetWidthHeight.second != Height) && (TargetWidthHeight.second != -1)) {
        SystemUtils_->Logger_->Log(std::string("Error Loading Texture '") + Texture->Path
        + "', Level '" + std::to_string(Level) + "' With ID '" + std::to_string(LevelAssetID)
        + "' Height Does Not Match Metadata Target", 8, LogEnable);
        FreeImage_Unload(Image);
        return false;
    }
    

    // Detect NumChannels
    int Channels = FreeImage_GetLine(Image) / FreeImage_GetWidth(Image);
    if ((Channels < 1) || (Channels > 4)) {
        SystemUtils_->Logger_->Log(std::string("Error Loading Texture '") + Texture->Path
        + "', Level '" + std::to_string(Level) + "' With ID '" + std::to_string(LevelAssetID)
        + "' Invalid Number Of Channels", 8, LogEnable);
        FreeImage_Unload(Image);
        return false;
    }
    if ((Texture->LevelChannels[Level] != Channels) && (Texture->LevelChannels[Level] != -1)) {
        SystemUtils_->Logger_->Log(std::string("Error Loading Texture '") + Texture->Path
        + "', Level '" + std::to_string(Level) + "' With ID '" + std::to_string(LevelAssetID)
        + "' Number Channels Does Not Match Metadata Target", 8, LogEnable);
        FreeImage_Unload(Image);
        return false;
    }

    // Finally After Passing Sanity Checks, Populate Info
    Texture->LevelLoadedInRAM[Level] = true;
    Texture->LevelBitmaps[Level] = Image;

    return true;

}

bool ERS_CLASS_AsyncTextureUpdater::UnloadImageDataRAM(ERS_STRUCT_Texture* Texture, int Level, bool LogEnable) {

    // Check If Requested Level Exists
    if (Level < 0) {
        SystemUtils_->Logger_->Log("Texture Updater Tried To Unload Negative Texture Level", 8, LogEnable);
        return false;
    } else if (Level > (int)Texture->LevelResolutions.size()) {
        SystemUtils_->Logger_->Log("Texture Updater Tried To Unload Nonexistant Texture Level", 8, LogEnable);
        return false;
    }

    // Check If Level Already Not Loaded
    if (Texture->LevelBitmaps[Level] == nullptr) {
        SystemUtils_->Logger_->Log("Texture Updater Tried To Unload Not Loaded Image", 8, LogEnable);
        return false;
    }


    // Update Data
    FreeImage_Unload(Texture->LevelBitmaps[Level]);
    Texture->LevelBitmaps[Level] = nullptr;
    Texture->LevelLoadedInRAM[Level] = false;

    return true;
}

bool ERS_CLASS_AsyncTextureUpdater::LoadImageDataVRAM(ERS_STRUCT_Texture* Texture, int Level, bool LogEnable) {

    // Check If Requested Level Exists
    if (Level < 0) {
        SystemUtils_->Logger_->Log("Texture Updater Tried To Load Negative Texture Level Into VRAM", 8, LogEnable);
        return false;
    } else if (Level > (int)Texture->LevelResolutions.size()) {
        SystemUtils_->Logger_->Log("Texture Updater Tried To Load Nonexistant Texture Level Into VRAM", 8, LogEnable);
        return false;
    }

    // Check If Level Already Loaded
    if ((Texture->LevelTextureOpenGLIDs[Level] != 0)) {
        SystemUtils_->Logger_->Log("Texture Updater Tried To Load Already Loaded Image Into VRAM", 8, LogEnable);
        return false;
    }

    // Get Image Metadata, Perform Checks
    int Channels = Texture->LevelChannels[Level];
    if (Channels > 4) {
        SystemUtils_->Logger_->Log(std::string("Error Loading Texture '") + Texture->Path
        + "', Level '" + std::to_string(Level) + "' With ID '" + std::to_string(Texture->LevelTextureAssetIDs[Level])
        + "' Channel Count >4", 8, LogEnable);
        return false;
    }
    if (Channels < 1) {
        SystemUtils_->Logger_->Log(std::string("Error Loading Texture '") + Texture->Path
        + "', Level '" + std::to_string(Level) + "' With ID '" + std::to_string(Texture->LevelTextureAssetIDs[Level])
        + "' Channel Count <1", 8, LogEnable);
        return false;
    }
    for ( int i = 0; i < Level; i++) {
        if (!Texture->LevelLoadedInRAM[i]) {
            SystemUtils_->Logger_->Log(std::string("Error Loading Texture '") + Texture->Path
            + "', Level '" + std::to_string(Level) + "' With ID '" + std::to_string(Texture->LevelTextureAssetIDs[Level])
            + "' Not All Prior Levels Are Loaded Into RAM", 8, LogEnable);
            return false;
        }
    }

    // Generate OpenGL Texture ID
    unsigned int OpenGLTextureID;
    glGenTextures(1, &OpenGLTextureID);
    glBindTexture(GL_TEXTURE_2D, OpenGLTextureID);

    // Set Texture Properties
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, Level);

    // Identify Required Texture Format
    GLint TextureInternFormat;
    GLenum TextureExternFormat;
    if (Channels == 4) {
        TextureInternFormat = GL_RGBA;
        TextureExternFormat = GL_BGRA;
    } else if (Channels == 3) {
        TextureInternFormat = GL_RGB;
        TextureExternFormat = GL_BGR;
    } else if (Channels == 2) {
        TextureInternFormat = GL_RG;
        TextureExternFormat = GL_RG;
    } else if (Channels == 1) {
        TextureInternFormat = GL_RED;
        TextureExternFormat = GL_RED;
    } else {
        return false;
    }

    
    // Setup Texture To Accept MipMaps
    int MaxWidth = Texture->LevelResolutions[Level].first;
    int MaxHeight = Texture->LevelResolutions[Level].second;
    glTexImage2D(GL_TEXTURE_2D, 0, TextureInternFormat, MaxWidth, MaxHeight, 0, TextureExternFormat, GL_UNSIGNED_BYTE, NULL);
    //glGenerateMipmap(GL_TEXTURE_2D);

    // Load MipMaps Into Texture
    for (int i = 0; i < Level; i++) {
        int Width = Texture->LevelResolutions[Level - i].first;
        int Height = Texture->LevelResolutions[Level - i].second;
        unsigned char* ImageBytes = (unsigned char*)FreeImage_GetBits(Texture->LevelBitmaps[Level - i]);
        glTexSubImage2D(GL_TEXTURE_2D, i, 0, 0, Width, Height, TextureExternFormat, GL_UNSIGNED_BYTE, ImageBytes);
    }

    // Update Struct
    Texture->LevelTextureOpenGLIDs[Level] = OpenGLTextureID;
    Texture->LevelLoadedInVRAM[Level] = true;
    glBindTexture(GL_TEXTURE_2D, 0);


    return true;
}

bool ERS_CLASS_AsyncTextureUpdater::UnloadImageDataVRAM(ERS_STRUCT_Texture* Texture, int Level, bool LogEnable) {
    
    // Check If Requested Level Exists
    if (Level < 0) {
        SystemUtils_->Logger_->Log("Texture Updater Tried To Unload Negative Texture Level Out Of VRAM", 8, LogEnable);
        return false;
    } else if (Level > (int)Texture->LevelResolutions.size()) {
        SystemUtils_->Logger_->Log("Texture Updater Tried To Unload Nonexistant Texture Level Out Of VRAM", 8, LogEnable);
        return false;
    }

    // Check If Level Already Unloaded
    if ((Texture->LevelTextureOpenGLIDs[Level] == 0)) {
        SystemUtils_->Logger_->Log("Texture Updater Tried To Unload Already Loaded Image Out Of VRAM", 8, LogEnable);
        return false;
    }

    // Delete Texture
    glDeleteTextures(1, &Texture->LevelTextureOpenGLIDs[Level]);

    // Update Struct
    Texture->LevelTextureOpenGLIDs[Level] = 0;
    Texture->LevelLoadedInVRAM[Level] = false;

    return true;

}

void ERS_CLASS_AsyncTextureUpdater::SetLevelRAM(ERS_STRUCT_Model* Model, bool LogEnable) {

        // NOTE: RAM UPDATES MUST BE CONSECUATIVE (you must have every level loaded consecuitively, eg: if you have level 3 loaded, you must also have 0,1,2 as well)
        // Also apparenly I don't know how to spell...
        // Load New Levels Into Memory
        if (Model->TextureLevelInRAM_ < Model->TargetTextureLevelRAM) {
            for (unsigned int LevelToLoad = (unsigned int)Model->TextureLevelInRAM_; LevelToLoad <= (unsigned int)Model->TargetTextureLevelRAM; LevelToLoad++) {
                for (unsigned int TextureIndex = 0; TextureIndex < Model->Textures_.size(); TextureIndex++) {
                    LoadImageDataRAM(&Model->Textures_[TextureIndex], LevelToLoad, LogEnable);
                }
                Model->TextureLevelInRAM_ = LevelToLoad;

            }
        }

        // Unload Old 
        else if (Model->TextureLevelInRAM_ > Model->TargetTextureLevelRAM) {
            for (unsigned int LevelToUnload = (unsigned int)Model->TextureLevelInRAM_; LevelToUnload > (unsigned int)Model->TargetTextureLevelRAM; LevelToUnload--) {
                for (unsigned int TextureIndex = 0; TextureIndex < Model->Textures_.size(); TextureIndex++) {
                    UnloadImageDataRAM(&Model->Textures_[TextureIndex], LevelToUnload, LogEnable);
                }
                Model->TextureLevelInRAM_ = LevelToUnload - 1;
            }
        }


}

void ERS_CLASS_AsyncTextureUpdater::SetLevelVRAM(ERS_STRUCT_Model* Model, bool LogEnable) {


        if (Model->TextureLevelInVRAM_ < Model->TargetTextureLevelVRAM) {

            // We Need All Texture Levels In RAM To Push To VRAM, Check This Is True!
            // If It's Not, We're Going To Load Them
            if (Model->TextureLevelInRAM_ <= Model->TargetTextureLevelVRAM) {
                if (Model->TargetTextureLevelRAM < Model->TargetTextureLevelVRAM) {
                    Model->TargetTextureLevelRAM = Model->TargetTextureLevelVRAM;
                }
                SetLevelRAM(Model, LogEnable);
            }


            // Load This VRAM Level For All Textures
            int LevelToLoad = Model->TargetTextureLevelVRAM;
            for (unsigned int TextureIndex = 0; TextureIndex < Model->Textures_.size(); TextureIndex++) {

                // Requested Level
                LoadImageDataVRAM(&Model->Textures_[TextureIndex], LevelToLoad, LogEnable);
                Model->Textures_[TextureIndex].BestAvailableOpenGLID = Model->Textures_[TextureIndex].LevelTextureOpenGLIDs[LevelToLoad];

                // Ensure That Level 0 Is Always Loaded
                if (!Model->Textures_[TextureIndex].LevelLoadedInVRAM[0]) {
                    LoadImageDataVRAM(&Model->Textures_[TextureIndex], 0, LogEnable);
                    Model->Textures_[TextureIndex].HasAnyLevelReady = true;
                }

            }
            Model->TextureLevelInVRAM_ = LevelToLoad;
        }

        else if (Model->TextureLevelInVRAM_ > Model->TargetTextureLevelVRAM) {

            // Here, we unload *all* levels that are above the target (if they're loaded)
            for (unsigned int LevelToUnload = (unsigned int)Model->TextureLevelInVRAM_; LevelToUnload > (unsigned int)Model->TargetTextureLevelVRAM; LevelToUnload--) {
                for (unsigned int TextureIndex = 0; TextureIndex < Model->Textures_.size(); TextureIndex++) {
                    
                    // Check If Level Already Loaded, Otherwise, Don't Try To Unload It
                    if (Model->Textures_[TextureIndex].LevelLoadedInVRAM[LevelToUnload]) {
                        UnloadImageDataVRAM(&Model->Textures_[TextureIndex], LevelToUnload, LogEnable);
                    }

                    // Find New Best OpenGL ID
                    for (unsigned int i = 0; i < Model->Textures_[TextureIndex].LevelTextureOpenGLIDs.size(); i++) {
                        if (Model->Textures_[TextureIndex].LevelLoadedInVRAM[i]) {
                            Model->Textures_[TextureIndex].BestAvailableOpenGLID = Model->Textures_[TextureIndex].LevelTextureOpenGLIDs[i];
                        }
                    }

                }
                Model->TextureLevelInVRAM_ = LevelToUnload - 1;
            }
        }


}

void ERS_CLASS_AsyncTextureUpdater::ProcessWorkItem(ERS_STRUCT_Model* Model) {
    
    // Identify Type Of Work To Be Done
    int TargetRAMLevel = Model->TargetTextureLevelRAM;
    int TargetVRAMLevel = Model->TargetTextureLevelVRAM;


    // Perform RAM Updates
    if (Model->TextureLevelInRAM_!= TargetRAMLevel) {
        SetLevelRAM(Model, true);
    }

    // Perform VRAM Updates
    if (Model->TextureLevelInVRAM_ != TargetVRAMLevel) {
        SetLevelVRAM(Model, true);
    }
       


}

void ERS_CLASS_AsyncTextureUpdater::SortModels(ERS_STRUCT_Scene* Scene) {

    // Iterate Over All Models
    for (unsigned int i = 0; i < Scene->Models.size(); i++) {
        
        // Check RAM Level vs Target
        int CurrentRAMLevel = Scene->Models[i]->TextureLevelInRAM_;
        int TargetRAMLevel = Scene->Models[i]->TargetTextureLevelRAM;
        bool RAMUpdate = CurrentRAMLevel!=TargetRAMLevel;

        // Check VRAM Level vs Target
        int CurrentVRAMLevel = Scene->Models[i]->TextureLevelInVRAM_;
        int TargetVRAMLevel = Scene->Models[i]->TargetTextureLevelVRAM;
        bool VRAMUpdate = CurrentVRAMLevel!=TargetVRAMLevel;

        // If There's Anything To Update, Add To Queue
        if (VRAMUpdate || RAMUpdate) {
            BlockThreads_.lock();

            bool CanAdd = true;

            // Check If Queue Full
            if (WorkItems_.size() >= (unsigned int)WorkQueueLimit_) {
                CanAdd = false;
            }

            // Skip Checking If Already In Queue If We Can't Add
            if (CanAdd && PreventDuplicateWorkItems_) {
                for (unsigned int x = 0; x < WorkItems_.size(); x++) {
                    if (WorkItems_[x] == Scene->Models[i]) {
                        CanAdd = false;
                        break;
                    }
                }
            }

            // If We Can Actually Add It, Do SO
            if (CanAdd) {

                if (PrioritizeQueueByVisualImpact_) {
                    int HighestTargetLevel = std::max(Scene->Models[i]->TargetTextureLevelRAM, Scene->Models[i]->TargetTextureLevelVRAM);
                    float Priority = HighestTargetLevel / Scene->Models[i]->MaxTextureLevel_;
                    int Index = WorkItems_.size() * Priority;
                    WorkItems_.insert(WorkItems_.end() - Index, Scene->Models[i]);
                } else {
                    WorkItems_.push_back(Scene->Models[i]);
                }
            }

            BlockThreads_.unlock();
        }

    }

    // Reset Strings
    RAMQueueString = "";
    VRAMQueueString = "";

    BlockThreads_.lock();
    for (unsigned int i = 0; i < WorkItems_.size(); i++) {
        ERS_STRUCT_Model* Model = WorkItems_[i].get();

        if (Model->TargetTextureLevelRAM > Model->TextureLevelInRAM_) {
            RAMQueueString += "L";
        } else if (Model->TargetTextureLevelRAM < Model->TextureLevelInRAM_) {
            RAMQueueString += "U";
        }

        if (Model->TargetTextureLevelVRAM > Model->TextureLevelInVRAM_) {
            VRAMQueueString += "P";
        } else if (Model->TargetTextureLevelVRAM < Model->TextureLevelInVRAM_) {
            VRAMQueueString += "F";
        }
    }
    BlockThreads_.unlock();




}

void ERS_CLASS_AsyncTextureUpdater::TextureModifierWorkerThread(int Index) {

    // Setup FreeImage
    FreeImage_Initialise();

    // Setup OpenGL Shared Context
    SystemUtils_->Logger_->Log(std::string("Texture Streaming Thead '") + std::to_string(Index) + "' Creating Shared OpenGL Context", 3);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    GLFWwindow* ThreadWindow = glfwCreateWindow(1, 1, std::to_string(Index).c_str(), NULL, MainThreadWindowContext_);
    glfwMakeContextCurrent(ThreadWindow);
    SystemUtils_->Logger_->Log(std::string("Texture Streaming Thead '") + std::to_string(Index) + "' Finished Creating OpenGL Context", 2);


    // Prepare OGL Context
    glEnable(GL_TEXTURE_2D);

    while (!StopThreads_) {


        // Get Work Item If It Exists
        std::shared_ptr<ERS_STRUCT_Model> WorkItem;
        bool HasWorkItem = false;
        BlockThreads_.lock();
        if (WorkItems_.size() > 0) {
            WorkItem = WorkItems_[0];
            if (!WorkItem->TexturesAlreadyBeingProcessed_) {
                HasWorkItem = true;
                WorkItems_.erase(WorkItems_.begin());
            }
        }
        BlockThreads_.unlock();

        // Process Item, If Item Doens't Exist, Sleep Thread
        if (HasWorkItem) {
            WorkItem->TexturesAlreadyBeingProcessed_ = true;
            ProcessWorkItem(WorkItem.get());
            WorkItem->TexturesAlreadyBeingProcessed_ = false;
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

    }

    // Destroy OpenGL Context
    glfwDestroyWindow(ThreadWindow);

    // Shut Down FreeImage
    FreeImage_DeInitialise();
}

int ERS_CLASS_AsyncTextureUpdater::GetNumThreads() {
    return NumThreads_;
}

void ERS_CLASS_AsyncTextureUpdater::SetNumThreads(int NumThreads) {
    NumThreads_ = NumThreads;
}

void ERS_CLASS_AsyncTextureUpdater::SetupThreads() {

    // Setup Threads
    SystemUtils_->Logger_->Log("Starting Worker Thread Pool", 4);
    SystemUtils_->Logger_->Log(std::string("Worker Pool Will Have ") + std::to_string(NumThreads_) + " Threads", 3);
    StopThreads_ = false;
    for (unsigned int i = 0; i < NumThreads_; i++) {
        TextureWorkerThreads_.push_back(std::thread(&ERS_CLASS_AsyncTextureUpdater::TextureModifierWorkerThread, this, i));
        SystemUtils_->Logger_->Log(std::string("Started Worker Thread '") + std::to_string(i) + "'", 2);
    }
    SystemUtils_->Logger_->Log("Setup Worker Thread Pool", 3);

}

void ERS_CLASS_AsyncTextureUpdater::TeardownThreads() {

    // Send Shutdown Command
    SystemUtils_->Logger_->Log("Sending Stop Command To Worker Thread Pool", 5);
    StopThreads_ = true;
    SystemUtils_->Logger_->Log("Stop Command Sent", 3);

    // Join Threads
    SystemUtils_->Logger_->Log("Joining Texture Streaming Worker Thread Pool", 5);
    for (unsigned int i = 0; i < TextureWorkerThreads_.size(); i++) {
        SystemUtils_->Logger_->Log(std::string("Joining Texture Streaming Worker Thread '") + std::to_string(i) + "'", 3);
        TextureWorkerThreads_[i].join();
    }
    TextureWorkerThreads_.clear();

    SystemUtils_->Logger_->Log("Finished Joining Texture Streaming Worker Thread Pool", 4);

}

int ERS_CLASS_AsyncTextureUpdater::GetQueueLimit() {
    return WorkQueueLimit_;
}

void ERS_CLASS_AsyncTextureUpdater::SetQueueLimit(int QueueLimit) {
    WorkQueueLimit_ = QueueLimit;
}

bool ERS_CLASS_AsyncTextureUpdater::GetDupeQueueEntryPrevention() {
    return PreventDuplicateWorkItems_;
}

void ERS_CLASS_AsyncTextureUpdater::SetDupeQueueEntryPrevention(bool State) {
    PreventDuplicateWorkItems_ = State;
}

bool ERS_CLASS_AsyncTextureUpdater::GetQueuePrioritizationEnabled() {
    return PrioritizeQueueByVisualImpact_;
}

void ERS_CLASS_AsyncTextureUpdater::SetQueuePrioritizationEnabled(bool State) {
    PrioritizeQueueByVisualImpact_ = State;
}


