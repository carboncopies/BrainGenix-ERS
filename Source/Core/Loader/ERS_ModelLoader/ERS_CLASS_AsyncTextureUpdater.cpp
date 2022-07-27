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
            Threads = std::thread::hardware_concurrency();
        }
    }

    Threads = 1;

    // Setup Threads
    SystemUtils_->Logger_->Log("Starting Worker Thread Pool", 4);
    SystemUtils_->Logger_->Log(std::string("Worker Pool Will Have ") + std::to_string(Threads) + " Threads", 3);
    StopThreads_ = false;
    HasTex = false;
    for (unsigned int i = 0; i < Threads; i++) {
        TextureWorkerThreads_.push_back(std::thread(&ERS_CLASS_AsyncTextureUpdater::TextureModifierWorkerThread, this));
        SystemUtils_->Logger_->Log(std::string("Started Worker Thread '") + std::to_string(i) + "'", 2);
    }


    while (!HasTex) {
    }

    if (glIsTexture(TestTexID)) {
    std::cout<<"Main thread: True"<<std::endl;
    } else {
    std::cout<<"Main thread: False"<<std::endl;
    }    
    
    //glfwMakeContextCurrent(MainThreadWindowContext_);
    SystemUtils_->Logger_->Log("Setup Worker Thread Pool", 3);

}

ERS_CLASS_AsyncTextureUpdater::~ERS_CLASS_AsyncTextureUpdater() {

    SystemUtils_->Logger_->Log("Automatic Texture Loading Subsystem Shutdown Invoked", 6);

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
    SystemUtils_->Logger_->Log("Finished Joining Texture Streaming Worker Thread Pool", 4);

    // Cleanup
    SystemUtils_->Logger_->Log("Cleaning Up OpenGL/GLFW", 6);
    glfwTerminate();

}


bool ERS_CLASS_AsyncTextureUpdater::LoadImageData(ERS_STRUCT_Texture* Texture, int Level, bool LogEnable) {

    // Check If Requested Level Exists
    if (Level < 0) {
        SystemUtils_->Logger_->Log("Texture Updater Tried To Load Negative Texture Level", 8, LogEnable);
        return false;
    } else if (Level > Texture->LevelResolutions.size()) {
        SystemUtils_->Logger_->Log("Texture Updater Tried To Load Nonexistant Texture Level", 8, LogEnable);
        return false;
    }

    // Check If Level Already Loaded
    if (Texture->LevelBitmaps[Level] != nullptr) {
        SystemUtils_->Logger_->Log("Texture Updater Tried To Load Already Loaded Image", 8, LogEnable);
        return false;
    }


    // Load Image Data
    ERS_STRUCT_IOData ImageData;
    long LevelAssetID = Texture->LevelTextureIDs[Level];
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

bool ERS_CLASS_AsyncTextureUpdater::UnloadImageData(ERS_STRUCT_Texture* Texture, int Level, bool LogEnable) {

    // Check If Requested Level Exists
    if (Level < 0) {
        SystemUtils_->Logger_->Log("Texture Updater Tried To Unload Negative Texture Level", 8, LogEnable);
        return false;
    } else if (Level > Texture->LevelResolutions.size()) {
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

bool ERS_CLASS_AsyncTextureUpdater::UploadTextureData(FIBITMAP* ImageData, int Width, int Height, int Channels, unsigned int TextureID, int MipMapLevel) {

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

    // Load Image
    unsigned char* ImageBytes = (unsigned char*)ImageData->data;
    glBindTexture(GL_TEXTURE_2D, TextureID);
    glTexImage2D(GL_TEXTURE_2D, MipMapLevel, TextureInternFormat, Width, Height, 0, TextureExternFormat, GL_UNSIGNED_BYTE, ImageBytes);


    // Try using normal (non-pbo) operations
    // see if we can upload texutres this way without the need for a pbo.
    // if we need to use pbos, let's start with uploading it all at once, and then implement the code to upload bit by bit later.
    // then work on sorting out other texture management/RAM loading
    // on a side note, we should regenerate the texture for every mip-map level we load in (async of course), perhaps we can change this later but for now it's okay 
    // - we could always implement settings to skip unloading unless needed by memory or some other issue.

    // // Generate PBO
    // // We use this as an intermediary stage to transfer image data from ram to GPU texture
    // unsigned int PixelBufferObjectID;
    // glGenBuffers(1, &PixelBufferObjectID);

    // // Initialize PBO
    // glBindBuffer(GL_PIXEL_UNPACK_BUFFER, PixelBufferObjectID);
    // glBufferData(GL_PIXEL_UNPACK_BUFFER, Width*Height*Channels, NULL, GL_STREAM_DRAW);

    // // Get Image Data, Copy Into Buffer
    // unsigned char* ImageBytes = (unsigned char*)ImageData->data;
    // void* MappedBufferData = glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
    // memcpy(MappedBufferData, ImageBytes, Width*Height*Channels*sizeof(unsigned char));

    // // Identify Format
    // GLint TextureInternFormat;
    // GLenum TextureExternFormat;
    // if (Channels == 4) {
    //     TextureInternFormat = GL_RGBA;
    //     TextureExternFormat = GL_BGRA;
    // } else if (Channels == 3) {
    //     TextureInternFormat = GL_RGB;
    //     TextureExternFormat = GL_BGR;
    // } else if (Channels == 2) {
    //     TextureInternFormat = GL_RG;
    //     TextureExternFormat = GL_RG;
    // } else if (Channels == 1) {
    //     TextureInternFormat = GL_RED;
    //     TextureExternFormat = GL_RED;
    // } else {
    //     glBindTexture(GL_TEXTURE_2D, 0);
    //     glDeleteBuffers(1, &PixelBufferObjectID);
    //     return false;
    // }

    // // Transfer Data From Buffer To Texture (Async)
    // glBindBuffer(GL_PIXEL_UNPACK_BUFFER, PixelBufferObjectID);
    // glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
    // glTexImage2D(GL_TEXTURE_2D, MipMapLevel, TextureInternFormat, Width, Height, 0, TextureExternFormat, GL_UNSIGNED_BYTE, 0);
    

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
            WorkItems_.push_back(Scene->Models[i]);
            BlockThreads_.unlock();
        }

    }

}

void ERS_CLASS_AsyncTextureUpdater::TextureModifierWorkerThread() {

    // Setup OpenGL Shared Context
    //glfwMakeContextCurrent(MainThreadWindowContext_);
    //gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    GLFWwindow* ThreadWindow = glfwCreateWindow(1, 1, "", NULL, MainThreadWindowContext_);
    glfwMakeContextCurrent(ThreadWindow);

    while (!StopThreads_) {

        // Get Work Item If It Exists
        std::shared_ptr<ERS_STRUCT_Model> WorkItem;
        bool HasWorkItem = false;
        BlockThreads_.lock();
        if (WorkItems_.size() > 0) {
            WorkItem = WorkItems_[0];
            HasWorkItem = true;
            WorkItems_.erase(WorkItems_.begin());
        }
        BlockThreads_.unlock();

        glEnable(GL_TEXTURE_2D);

        const char* Path = "EditorAssets/Icons/LoadingTexture/4x4/LoadingTexture1024.png";
        std::cout<<"Loading Texture "<<std::endl;
        FreeImage_Initialise();
        FREE_IMAGE_FORMAT TexFormat = FreeImage_GetFileType(Path, 0);
        FIBITMAP* TexImageData = FreeImage_Load(TexFormat, Path);
        unsigned char* RawImageData = FreeImage_GetBits(TexImageData);
        int Width = FreeImage_GetWidth(TexImageData);
        int Height = FreeImage_GetHeight(TexImageData);
        int Channels = FreeImage_GetLine(TexImageData) / Width;
        std::cout<<"sending to gpu"<<std::endl;

        unsigned int OpenGLTextureID;
        glGenTextures(1, &OpenGLTextureID);
        glBindTexture(GL_TEXTURE_2D, OpenGLTextureID);
        std::cout<<"Tex ID: "<<OpenGLTextureID<<std::endl;
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        if (Channels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, RawImageData);
        } else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_BGR, GL_UNSIGNED_BYTE, RawImageData);
        }
        glGenerateMipmap(GL_TEXTURE_2D);

        FreeImage_Unload(TexImageData);
        UploadTextureData(TexImageData, 1024, 1024, 3, OpenGLTextureID, 0);
        glFinish();


        std::cout<<"Done, checking tex state"<<std::endl;

        TestTexID = OpenGLTextureID;

        if (glIsTexture(TestTexID)) {
        std::cout<<"Tex thread: True"<<std::endl;
        } else {
        std::cout<<"Tex thread: False"<<std::endl;
        }  
        HasTex = true;
        while (!StopThreads_) {

        }

        // todo:
        // test shared objects (make texture here and use it in main thread?)
        // then setup model texture level loading system (finally!)
        // exciting isn't it?


        // Process Item, If Item Doens't Exist, Sleep Thread
        if (HasWorkItem) {
            // Process Work Item
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

    }

    FreeImage_DeInitialise();
    glfwDestroyWindow(ThreadWindow);
}


