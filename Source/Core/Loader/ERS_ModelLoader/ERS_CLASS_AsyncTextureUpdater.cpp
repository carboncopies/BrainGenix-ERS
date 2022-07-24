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
    SystemUtils_->Logger_->Log("Joining Worker Thread Pool", 5);
    for (unsigned int i = 0; i < TextureWorkerThreads_.size(); i++) {
        SystemUtils_->Logger_->Log(std::string("Joining Worker Thread '") + std::to_string(i) + "'", 3);
        TextureWorkerThreads_[i].join();
    }
    SystemUtils_->Logger_->Log("Finished Joining Worker Thread Pool", 4);

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
    glfwTerminate();

}


