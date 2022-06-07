//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_DepthMaps.h>


ERS_CLASS_DepthMaps::ERS_CLASS_DepthMaps(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils, ERS_CLASS_MeshRenderer* Renderer) {

    SystemUtils_ = SystemUtils;
    ProjectUtils_ = ProjectUtils;
    Renderer_ = Renderer;

    SystemUtils_->Logger_->Log("Initializing Viewport Overlay Subsystem", 5);

    // Create Array Texture For Depth Maps
    RegenerateDepthMapTextureArray(256, 2048, 2048);


}

ERS_CLASS_DepthMaps::~ERS_CLASS_DepthMaps() {

    SystemUtils_->Logger_->Log("Viewport Overlay Subsystem Destructor Invoked", 6);

}

bool ERS_CLASS_DepthMaps::RegenerateDepthMapTextureArray(int NumberOfTextures, int Width, int Height, bool LogEnabled) {


    SystemUtils_->Logger_->Log(
        std::string("Generating Depth Map Texture Array Of ") + std::to_string(NumberOfTextures)
         + std::string(" Textures, With Width Of ") + std::to_string(Width)
         + std::string(" Pixels, And Height Of ") + std::to_string(Height)
         + std::string(" Pixels")
        , 5, LogEnabled);

    // Check If Already Texture, If So, Delete So We Can Overwrite it
    SystemUtils_->Logger_->Log("Checking If Texture Array Already Exists", 4, LogEnabled);
    bool TextureAlreadyExists = glIsTexture(DepthTextureArrayID_);
    if (TextureAlreadyExists) {
        SystemUtils_->Logger_->Log("Array ID Already In Use, Freeing First", 4, LogEnabled);
        glDeleteTextures(1, &DepthTextureArrayID_);
    } else {
        SystemUtils_->Logger_->Log("Array ID Not Already In Use", 4, LogEnabled);
    }

    // Handle The Creation Of A New Texture Array
    SystemUtils_->Logger_->Log("Setting Up Texture Array Metadata", 4, LogEnabled);
    DepthTextureArrayWidth_ = Width;
    DepthTextureArrayHeight_ = Height;
    DepthTextureNumTextures_ = NumberOfTextures;

    SystemUtils_->Logger_->Log("Setting Up Texture Array OpenGL Parameters", 5, LogEnabled);
    glGenTextures(1, &DepthTextureArrayID_);
    glActiveTexture(GL_TEXTURE8);
    glBindTexture(GL_TEXTURE_2D_ARRAY, DepthTextureArrayID_);
    
    glTexStorage3D(GL_TEXTURE_2D_ARRAY,
        0, // Number OF Mipmaps, Note that we're not using mipmaps so this is set to 1
        GL_DEPTH_COMPONENT, // Storage Format, Using Depth Format Here As We're Setting Up A Depth Map
        Width, Height, // Width and Height, Pretty Self Explanitory
        NumberOfTextures // Total Number Of Textures In The Array
    );
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float BorderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, BorderColor); 
    SystemUtils_->Logger_->Log("Depth Map Texture Array Initialization Complete", 5, LogEnabled);


    // Update Allocation Array
    SystemUtils_->Logger_->Log("Checking Depth Map Texture Array Allocation Array", 4, LogEnabled);
    unsigned long SizeOfAllocationArray = DepthMapTexturesAlreadyAllocated_.size();
    if (SizeOfAllocationArray > (unsigned int)NumberOfTextures) {
        SystemUtils_->Logger_->Log("Downsizing Array To Match Target Number Of Textures", 5, LogEnabled);
        DepthMapTexturesAlreadyAllocated_.erase(DepthMapTexturesAlreadyAllocated_.begin() + NumberOfTextures, DepthMapTexturesAlreadyAllocated_.end());
    } else if (SizeOfAllocationArray < (unsinged int)NumberOfTextures) {
        SystemUtils_->Logger_->Log("Upsizing Array To Match Target Number Of Textures", 5, LogEnabled);
        for (unsigned int i = 0; i < NumberOfTextures - SizeOfAllocationArray; i++) {
            DepthMapTexturesAlreadyAllocated_.push_back(false);
        }
    }
    SystemUtils_->Logger_->Log("Done Updating/Checking Allocation Array", 5, LogEnabled);

    return true;

}

bool ERS_CLASS_DepthMaps::FreeDepthMapIndex(unsigned int Index) {

    // Sanity Check
    if (Index > DepthMapTexturesAlreadyAllocated_.size() - 1) {
        return false; // Indicate Failure, Out Of Range
    }

    // DeAllocate From Array
    DepthMapTexturesAlreadyAllocated_[Index] = false;
    return true;

}

unsigned int ERS_CLASS_DepthMaps::AllocateDepthMapIndex() {

    // If Enough Textures Exist, Find One
    SystemUtils_->Logger_->Log("Allocating Depth Map Texture Array Index", 5);
    for (unsigned int i = 0; i < DepthMapTexturesAlreadyAllocated_.size(); i++) {
        if (!DepthMapTexturesAlreadyAllocated_[i]) {
            SystemUtils_->Logger_->Log(std::string("Allocated Depth Map Texture Array Index: ") + std::to_string(i), 5);
            DepthMapTexturesAlreadyAllocated_[i] = true;
            return i;
        }
    }

    // IF Not, Batch Allocate More
    SystemUtils_->Logger_->Log("Depth Map Texture Array Full, Regenerating With More Textures", 5);
    int StartSize = DepthMapTexturesAlreadyAllocated_.size();
    RegenerateDepthMapTextureArray(StartSize + DepthMapAllocationChunkSize_, DepthTextureArrayWidth_, DepthTextureArrayHeight_);
    SystemUtils_->Logger_->Log(std::string("Finished Updating Depth Map Array, Allocating Depth Map Texture Array Index: ") + std::to_string(StartSize + DepthMapAllocationChunkSize_), 5);

    return StartSize + DepthMapAllocationChunkSize_;
    


}

ERS_STRUCT_DepthMap ERS_CLASS_DepthMaps::GenerateDepthMap(int ResolutionX, int ResolutionY, bool LogEnable) {


    SystemUtils_->Logger_->Log(std::string("Creating Depth Map With Resolution Of ") + std::to_string(ResolutionX) + std::string("x") + std::to_string(ResolutionY), 5, LogEnable);

    // Setup Struct
    ERS_STRUCT_DepthMap Output;
    Output.ResolutionX = ResolutionX;
    Output.ResolutionY = ResolutionY;

    // Generate FBO
    SystemUtils_->Logger_->Log("Generating Framebuffer Object", 4, LogEnable);
    glGenFramebuffers(1, &Output.FrameBufferObjectID);
    SystemUtils_->Logger_->Log("Generated Framebuffer Object", 3, LogEnable);

    // Allocate Depth Map Texture ID
    Output.DepthMapTextureIndex = AllocateDepthMapIndex();

    // Attach Depth Map Texture To Framebuffer
    SystemUtils_->Logger_->Log("Attaching Depth Map Texture To Framebuffer", 4, LogEnable);
    glBindFramebuffer(GL_FRAMEBUFFER, Output.FrameBufferObjectID);
    glFramebufferTexture3D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D_ARRAY, DepthTextureArrayID_, 0, Output.DepthMapTextureIndex);
    //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, Output.DepthMapTextureID, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0); 
    SystemUtils_->Logger_->Log("Finished Attaching Texture To Framebuffer", 3, LogEnable);


    Output.Initialized = true;

    // Return Output
    return Output;

}

void ERS_CLASS_DepthMaps::UpdateDepthMap(ERS_STRUCT_DepthMap* Target, ERS_STRUCT_Shader* DepthShader, glm::vec3 Pos, glm::vec3 Rot, bool Orthogonal, glm::mat4* LightSpaceMatrix) {

    // Setup Variables
    ERS_STRUCT_Scene* TargetScene = ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_].get();
    glm::mat4 ObjectProjection, ObjectView, ObjectSpace;
    float NearPlane = 0.1f, FarPlane = 15.0f;

    // Calculate Project, View, Space Matrices
    if (Orthogonal) {
        ObjectProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, NearPlane, FarPlane); // ortho models directional light source
    } else {
        float AspectRatio = Target->ResolutionX / Target->ResolutionY;
        ObjectProjection = glm::perspective(glm::radians(110.0f), AspectRatio, NearPlane, FarPlane); // Perspective models regular light source
    }

    glm::vec3 Front = glm::normalize(Rot);
    ObjectView = glm::lookAt(Pos, Pos+Front, glm::vec3(0.0f, 1.0f, 0.0f));
    ObjectSpace = ObjectProjection * ObjectView;

    // Render With Depth Shader
    DepthShader->MakeActive();
    DepthShader->SetMat4("LightSpaceMatrix", ObjectSpace);

    if (LightSpaceMatrix != nullptr) {
        *LightSpaceMatrix = ObjectSpace;
    }

    glViewport(0, 0, Target->ResolutionX, Target->ResolutionY);
    glBindFramebuffer(GL_FRAMEBUFFER, Target->FrameBufferObjectID);

    glClear(GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE8);
    glBindTexture(GL_TEXTURE_2D_ARRAY, DepthTextureArrayID_);
    Renderer_->RenderSceneNoTextures(TargetScene, DepthShader);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void ERS_CLASS_DepthMaps::UpdateDepthMaps(ERS_STRUCT_Shader* DepthShader) {

    // Fix Offset (Peter Panning)
    glCullFace(GL_FRONT);

    // Get Active Scene
    ERS_STRUCT_Scene* ActiveScene = ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_].get();

    // Handle Directional Lights
    for (unsigned int i = 0; i < ActiveScene->DirectionalLights.size(); i++) {

        // Extract Struct
        ERS_STRUCT_DirectionalLight* Light = ActiveScene->DirectionalLights[i].get();

        // Check If Light Has DepthMap
        if (!Light->DepthMap.Initialized) {
            Light->DepthMap = GenerateDepthMap(2048, 2048);   
        }

        // Render To Depth Map
        glm::mat4* LightSpaceMatrix = new glm::mat4();
        UpdateDepthMap(&Light->DepthMap, DepthShader, Light->Pos, Light->Rot, true, LightSpaceMatrix);
        Light->LightSpaceMatrix = *LightSpaceMatrix;

    } 

    // Handle Spot Lights
    for (unsigned int i = 0; i < ActiveScene->SpotLights.size(); i++) {

        // Extract Struct
        ERS_STRUCT_SpotLight* Light = ActiveScene->SpotLights[i].get();

        // Check If Light Has DepthMap
        if (!Light->DepthMap.Initialized) {
            Light->DepthMap = GenerateDepthMap(2048, 2048);   
        }

        // Render To Depth Map
        glm::mat4* LightSpaceMatrix = new glm::mat4();
        UpdateDepthMap(&Light->DepthMap, DepthShader, Light->Pos, Light->Rot, false, LightSpaceMatrix);
        Light->LightSpaceMatrix = *LightSpaceMatrix;

    }

    // Handle Point Lights
    for (unsigned int i = 0; i < ActiveScene->PointLights.size(); i++) {

        // Extract Struct
        ERS_STRUCT_PointLight* Light = ActiveScene->PointLights[i].get();

        // Check If Light Has DepthMap
        if (!Light->DepthMap.Initialized) {
            Light->DepthMap = GenerateDepthMap(2048, 2048);   
        }

        // Render To Depth Map
        glm::mat4* LightSpaceMatrix = new glm::mat4();
        UpdateDepthMap(&Light->DepthMap, DepthShader, Light->Pos, Light->Pos, false, LightSpaceMatrix); // set this to false later, debugging
        Light->LightSpaceMatrix = *LightSpaceMatrix;

    } 


    // Return To Normal Culling
    glCullFace(GL_BACK);

}