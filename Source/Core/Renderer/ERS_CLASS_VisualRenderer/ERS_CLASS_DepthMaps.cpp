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
    RegenerateDepthMapTextureArray(16, SystemUtils_->RendererSettings_->ShadowMapX_, SystemUtils_->RendererSettings_->ShadowMapY_);


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
        SystemUtils_->Logger_->Log("Array ID Already In Use, Freeing First", 3, LogEnabled);
        glDeleteTextures(1, &DepthTextureArrayID_);
    } else {
        SystemUtils_->Logger_->Log("Array ID Not Already In Use", 3, LogEnabled);
    }

    // Handle The Creation Of A New Texture Array
    SystemUtils_->Logger_->Log("Setting Up Texture Array Metadata", 3, LogEnabled);
    DepthTextureArrayWidth_ = Width;
    DepthTextureArrayHeight_ = Height;
    DepthTextureNumTextures_ = NumberOfTextures;

    SystemUtils_->Logger_->Log("Setting Up Texture Array OpenGL Parameters", 4, LogEnabled);
    glGenTextures(1, &DepthTextureArrayID_);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, DepthTextureArrayID_);
    
    
    // ** THIS CAUSES A SEGFAULT FOR SOME REASON...? NOT SURE WHY, SO USING WORKAROUND BELOW **
    // glTextureStorage3D(GL_TEXTURE_2D_ARRAY,
    //     0, // Number OF Mipmaps, Note that we're not using mipmaps so this is set to 1
    //     GL_DEPTH_COMPONENT16, // Storage Format, Using Depth Format Here As We're Setting Up A Depth Map
    //     Width, Height, // Width and Height, Pretty Self Explanitory
    //     NumberOfTextures // Total Number Of Textures In The Array
    // );

    glTexImage3D(GL_TEXTURE_2D_ARRAY,
        0,                    // Current 'mipmap level', We're not using these so 0 is fine
        GL_DEPTH_COMPONENT24, // Storage Format, Using Depth Format Here As We're Setting Up A Depth Map
        Width, Height,        // Width and Height, Pretty Self Explanitory
        NumberOfTextures,     // Total Number Of Textures In The Array
        0,                    // Border, we're not using this
        GL_DEPTH_COMPONENT,   // Tells opengl what kind of data we're storing in this texture
        GL_FLOAT,             // tells opengl how to store the data
        NULL                  // if we were loading an image in, we could then pass the data in here, but we're not so this is left as null
    );

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    float BorderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_BORDER_COLOR, BorderColor); 
    SystemUtils_->Logger_->Log("Depth Map Texture Array Initialization Complete", 4, LogEnabled);


    // Update Allocation Array
    SystemUtils_->Logger_->Log("Checking Depth Map Texture Array Allocation Array", 3, LogEnabled);
    unsigned long SizeOfAllocationArray = DepthMapTexturesAlreadyAllocated_.size();
    if (SizeOfAllocationArray > (unsigned int)NumberOfTextures) {
        SystemUtils_->Logger_->Log("Downsizing Array To Match Target Number Of Textures", 4, LogEnabled);
        DepthMapTexturesAlreadyAllocated_.erase(DepthMapTexturesAlreadyAllocated_.begin() + NumberOfTextures, DepthMapTexturesAlreadyAllocated_.end());
    } else if (SizeOfAllocationArray < (unsigned int)NumberOfTextures) {
        SystemUtils_->Logger_->Log("Upsizing Array To Match Target Number Of Textures", 4, LogEnabled);
        for (unsigned int i = 0; i < NumberOfTextures - SizeOfAllocationArray; i++) {
            DepthMapTexturesAlreadyAllocated_.push_back(-1);
        }
    }
    SystemUtils_->Logger_->Log("Done Updating/Checking Allocation Array", 3, LogEnabled);


    // Rebind Any Framebuffers
    SystemUtils_->Logger_->Log("Rebinding Framebuffer Objects Depth Textures", 4, LogEnabled);
    for (unsigned int i = 0; i < DepthMapTexturesAlreadyAllocated_.size(); i++) {

        long ID = DepthMapTexturesAlreadyAllocated_[i];

        // Check If Valid ID
        if (glIsFramebuffer(ID)) {

            // If Valid, Rebind
            SystemUtils_->Logger_->Log(std::string("Rebinding Framebuffer '") + std::to_string(ID) + std::string("' To Texture At Index '") + std::to_string(i) + std::string("'"), 4, LogEnabled);
            glBindFramebuffer(GL_FRAMEBUFFER, ID);
            glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, DepthTextureArrayID_, 0, i);
        
        } else if (ID != -1) {
            SystemUtils_->Logger_->Log("Framebuffer Object Is Invalid, Removing From Allocation Table", 4, LogEnabled);
            DepthMapTexturesAlreadyAllocated_[i] = -1;
        }

    }

    return true;

}

bool ERS_CLASS_DepthMaps::FreeDepthMapIndex(unsigned int Index) {

    // Sanity Check
    if (Index > DepthMapTexturesAlreadyAllocated_.size() - 1) {
        return false; // Indicate Failure, Out Of Range
    }

    // DeAllocate From Array
    DepthMapTexturesAlreadyAllocated_[Index] = -1;
    return true;

}

unsigned int ERS_CLASS_DepthMaps::AllocateDepthMapIndex(unsigned int FramebufferObjectID) {

    // If Enough Textures Exist, Find One
    SystemUtils_->Logger_->Log("Allocating Depth Map Texture Array Index", 5);
    for (unsigned int i = 0; i < DepthMapTexturesAlreadyAllocated_.size(); i++) {
        if (DepthMapTexturesAlreadyAllocated_[i] == -1) {
            SystemUtils_->Logger_->Log(std::string("Allocated Depth Map Texture Array Index: ") + std::to_string(i), 5);
            DepthMapTexturesAlreadyAllocated_[i] = FramebufferObjectID;
            return i;
        }
    }

    // IF Not, Batch Allocate More
    SystemUtils_->Logger_->Log("Depth Map Texture Array Full, Regenerating With More Textures", 5);
    int StartSize = DepthMapTexturesAlreadyAllocated_.size();
    RegenerateDepthMapTextureArray(StartSize + DepthMapAllocationChunkSize_, DepthTextureArrayWidth_, DepthTextureArrayHeight_);
    SystemUtils_->Logger_->Log(std::string("Finished Updating Depth Map Array, Allocating Depth Map Texture Array Index: ") + std::to_string(StartSize + DepthMapAllocationChunkSize_), 5);

    DepthMapTexturesAlreadyAllocated_[StartSize + 1] = FramebufferObjectID;

    return StartSize + 1;

}

ERS_STRUCT_DepthMap ERS_CLASS_DepthMaps::GenerateDepthMap(int Number, bool LogEnable) {


    SystemUtils_->Logger_->Log(std::string("Creating ") + std::to_string(Number) + std::string(" Depth Map(s) With Resolution Of ") + std::to_string(DepthTextureArrayWidth_) + std::string("x") + std::to_string(DepthTextureArrayHeight_), 5, LogEnable);

    // Setup Struct
    ERS_STRUCT_DepthMap Output;

    // Iterate Over Total Quantity To Be Generated
    for (unsigned int i = 0; i < (unsigned int)Number; i++) {

        // Generate FBO
        SystemUtils_->Logger_->Log("Generating Framebuffer Object", 4, LogEnable);
        unsigned int FBOID;
        glGenFramebuffers(1, &FBOID);
        Output.FrameBufferObjectIDs.push_back(FBOID);
        SystemUtils_->Logger_->Log("Generated Framebuffer Object", 3, LogEnable);

        // Allocate Depth Map Texture ID
        Output.DepthMapTextureIndexes.push_back(AllocateDepthMapIndex(Output.FrameBufferObjectIDs[i]));

        // Attach Depth Map Texture To Framebuffer
        SystemUtils_->Logger_->Log(std::string("Attaching Depth Map Texture To Framebuffer Texture '") + std::to_string(Output.DepthMapTextureIndexes[i]) + std::string("'"), 4, LogEnable);
        glBindFramebuffer(GL_FRAMEBUFFER, Output.FrameBufferObjectIDs[i]);
        glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, DepthTextureArrayID_, 0, Output.DepthMapTextureIndexes[i]);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0); 
        SystemUtils_->Logger_->Log("Finished Attaching Texture To Framebuffer", 3, LogEnable);

    }

    Output.Initialized = true;

    // Return Output
    return Output;

}

void ERS_CLASS_DepthMaps::CheckSettings() {

    // Check Depth Maps
    bool NeedsToUpdate = true;
    
    if (SystemUtils_->RendererSettings_->ShadowMapX_ != DepthTextureArrayWidth_) {
        DepthTextureArrayWidth_ = SystemUtils_->RendererSettings_->ShadowMapX_;
    } else if (SystemUtils_->RendererSettings_->ShadowMapX_ != DepthTextureArrayHeight_) {
        DepthTextureArrayHeight_ = SystemUtils_->RendererSettings_->ShadowMapY_;
    } else {
        NeedsToUpdate = false;
    }

    if (NeedsToUpdate) {
        RegenerateDepthMapTextureArray(DepthTextureNumTextures_, DepthTextureArrayWidth_, DepthTextureArrayHeight_);
    }

}

void ERS_CLASS_DepthMaps::UpdateDepthMap(ERS_STRUCT_DirectionalLight* Light, ERS_STRUCT_Shader* DepthShader, glm::mat4* LightSpaceMatrix) {


    // Check Settings
    CheckSettings();

    // Setup Variables
    ERS_STRUCT_Scene* TargetScene = ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_].get();
    glm::mat4 ObjectProjection, ObjectView, ObjectSpace;
    float NearPlane = 0.1f, FarPlane = 15.0f;

    // Calculate Project, View, Space Matrices
    ObjectProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, NearPlane, FarPlane); // ortho models directional light source


    // Re-Do Rotation
    glm::vec3 XYZRotation = ERS_FUNCTION_ConvertRotationToFrontVector(Light->Rot);

    glm::vec3 Front = glm::normalize(XYZRotation);
    ObjectView = glm::lookAt(Light->Pos, Light->Pos+Front, glm::vec3(0.0f, 1.0f, 0.0f)); // Pos+Front
    ObjectSpace = ObjectProjection * ObjectView;

    // Render With Depth Shader
    DepthShader->MakeActive();
    DepthShader->SetMat4("LightSpaceMatrix", ObjectSpace);

    if (LightSpaceMatrix != nullptr) {
        *LightSpaceMatrix = ObjectSpace;
    }

    glViewport(0, 0, DepthTextureArrayWidth_, DepthTextureArrayHeight_);
    glBindFramebuffer(GL_FRAMEBUFFER, Light->DepthMap.FrameBufferObjectIDs[0]);

    
    glClear(GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    Renderer_->RenderSceneNoTextures(TargetScene, DepthShader);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    

}

void ERS_CLASS_DepthMaps::UpdateDepthMap(ERS_STRUCT_PointLight* Light, ERS_STRUCT_Shader* DepthShader, std::vector<glm::mat4>* LightSpaceMatrixArray) {

    // Check Settings
    CheckSettings();

    // Setup Variables
    ERS_STRUCT_Scene* TargetScene = ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_].get();
    float NearPlane, FarPlane;
    NearPlane = 0.1f;
    FarPlane = Light->MaxDistance;

    // Calculate Project, View, Space Matrices
    float AspectRatio = DepthTextureArrayWidth_ / DepthTextureArrayHeight_;
    glm::mat4 ObjectProjection = glm::perspective(glm::radians(90.0f), AspectRatio, NearPlane, FarPlane); // Perspective models regular light source
    
    std::vector<glm::mat4> ShadowTransforms;
    ShadowTransforms.push_back(ObjectProjection * glm::lookAt(Light->Pos, Light->Pos + glm::vec3( 1.0, 0.0, 0.0), glm::vec3(0.0,-1.0, 0.0)));
    ShadowTransforms.push_back(ObjectProjection * glm::lookAt(Light->Pos, Light->Pos + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0,-1.0, 0.0)));
    ShadowTransforms.push_back(ObjectProjection * glm::lookAt(Light->Pos, Light->Pos + glm::vec3( 0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
    ShadowTransforms.push_back(ObjectProjection * glm::lookAt(Light->Pos, Light->Pos + glm::vec3( 0.0,-1.0, 0.0), glm::vec3(0.0, 0.0,-1.0)));
    ShadowTransforms.push_back(ObjectProjection * glm::lookAt(Light->Pos, Light->Pos + glm::vec3( 0.0, 0.0, 1.0), glm::vec3(0.0,-1.0, 0.0)));
    ShadowTransforms.push_back(ObjectProjection * glm::lookAt(Light->Pos, Light->Pos + glm::vec3( 0.0, 0.0,-1.0), glm::vec3(0.0,-1.0, 0.0)));

    // Render All Sides
    for (unsigned int i = 0; i < ShadowTransforms.size(); i++) {

        // Render With Depth Shader
        DepthShader->MakeActive();
        DepthShader->SetMat4("LightSpaceMatrix", ShadowTransforms[i]);

        if (LightSpaceMatrix != nullptr) {
            *LightSpaceMatrix = ObjectSpace;
        }

        glViewport(0, 0, DepthTextureArrayWidth_, DepthTextureArrayHeight_);
        glBindFramebuffer(GL_FRAMEBUFFER, Light->DepthMap.FrameBufferObjectIDs[0]); // fix this later
        glClear(GL_DEPTH_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        Renderer_->RenderSceneNoTextures(TargetScene, DepthShader);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

    }

}

void ERS_CLASS_DepthMaps::UpdateDepthMap(ERS_STRUCT_SpotLight* Light, ERS_STRUCT_Shader* DepthShader, glm::mat4* LightSpaceMatrix) {

    // Check Settings
    CheckSettings();

    // Setup Variables
    ERS_STRUCT_Scene* TargetScene = ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_].get();
    glm::mat4 ObjectProjection, ObjectView, ObjectSpace;
    float NearPlane, FarPlane;
    NearPlane = 0.1f;
    FarPlane = Light->MaxDistance;

    // Calculate Project, View, Space Matrices
    float AspectRatio = DepthTextureArrayWidth_ / DepthTextureArrayHeight_;
    float FOV = glm::radians(130.0f);// * (0.01745329));
    ObjectProjection = glm::perspective(FOV, AspectRatio, NearPlane, FarPlane); // Perspective models regular light source
    
    // Re-Do Rotation
    glm::vec3 XYZRotation = ERS_FUNCTION_ConvertRotationToFrontVector(Light->Rot);
    glm::vec3 Front = glm::normalize(XYZRotation);
    ObjectView = glm::lookAt(Light->Pos, Light->Pos+Front, glm::vec3(0.0f, 1.0f, 0.0f)); // Pos+Front
    ObjectSpace = ObjectProjection * ObjectView;

    // Render With Depth Shader
    DepthShader->MakeActive();
    DepthShader->SetMat4("LightSpaceMatrix", ObjectSpace);

    if (LightSpaceMatrix != nullptr) {
        *LightSpaceMatrix = ObjectSpace;
    }

    glViewport(0, 0, DepthTextureArrayWidth_, DepthTextureArrayHeight_);
    glBindFramebuffer(GL_FRAMEBUFFER, Light->DepthMap.FrameBufferObjectIDs[0]);
    glClear(GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
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
            Light->DepthMap = GenerateDepthMap();   
        }

        // Render To Depth Map
        glm::mat4* LightSpaceMatrix = new glm::mat4();
        UpdateDepthMap(Light, DepthShader, LightSpaceMatrix);
        Light->LightSpaceMatrix = *LightSpaceMatrix;

    } 

    // Handle Spot Lights
    for (unsigned int i = 0; i < ActiveScene->SpotLights.size(); i++) {

        // Extract Struct
        ERS_STRUCT_SpotLight* Light = ActiveScene->SpotLights[i].get();

        // Check If Light Has DepthMap
        if (!Light->DepthMap.Initialized) {
            Light->DepthMap = GenerateDepthMap();   
        }

        // Render To Depth Map
        glm::mat4* LightSpaceMatrix = new glm::mat4();
        UpdateDepthMap(Light, DepthShader, LightSpaceMatrix);
        Light->LightSpaceMatrix = *LightSpaceMatrix;

    }

    // Handle Point Lights
    for (unsigned int i = 0; i < ActiveScene->PointLights.size(); i++) {

        // Extract Struct
        ERS_STRUCT_PointLight* Light = ActiveScene->PointLights[i].get();

        // Check If Light Has DepthMap
        if (!Light->DepthMap.Initialized) {
            Light->DepthMap = GenerateDepthMap(6); // Point lights need 6 depth maps for a "cubemap", which is a shadow map for each side of the cube, allowing shadows around the light in all directions
        }

        // Render To Depth Map
        glm::mat4* LightSpaceMatrix = new glm::mat4();
        UpdateDepthMap(Light, DepthShader, LightSpaceMatrix); // set this to false later, debugging
        Light->LightSpaceMatrix = *LightSpaceMatrix;

    } 


    // Return To Normal Culling
    glCullFace(GL_BACK);

}