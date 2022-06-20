//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_DepthMaps.h>


ERS_CLASS_DepthMaps::ERS_CLASS_DepthMaps(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils, ERS_CLASS_MeshRenderer* Renderer) {

    SystemUtils_ = SystemUtils;
    ProjectUtils_ = ProjectUtils;
    Renderer_ = Renderer;

    SystemUtils_->Logger_->Log("Initializing Depth Map Subsystem", 5);

    // Create Array Texture For Depth Maps
    RegenerateDepthMapTextureArray2D(16, SystemUtils_->RendererSettings_->ShadowMapX_, SystemUtils_->RendererSettings_->ShadowMapY_);
    RegenerateDepthMapTextureArrayCubemap(2);


    // // configure depth map FBO
    // // -----------------------
    // const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
    // unsigned int depthMapFBO;
    // glGenFramebuffers(1, &depthMapFBO);

    // // create depth cubemap texture
    // unsigned int depthCubemap;
    // glGenTextures(1, &depthCubemap);
    // glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
    // for (unsigned int i = 0; i < 6; ++i)
    //     glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    // // attach depth texture as FBO's depth buffer
    // glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    // glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
    // glDrawBuffer(GL_NONE);
    // glReadBuffer(GL_NONE);
    // glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // TESTFBO = depthMapFBO;
    // TESTCubemap = depthCubemap;


}

ERS_CLASS_DepthMaps::~ERS_CLASS_DepthMaps() {

    SystemUtils_->Logger_->Log("Depth Map Destructor Invoked", 6);


    SystemUtils_->Logger_->Log("Depth Map Subsystem Destroying Array Textures", 4);
    glDeleteTextures(1, &DepthTextureArrayID_);
    SystemUtils_->Logger_->Log("Depth Map Subsystem Destroyed 2D Depth Array Texture", 4);
    glDeleteTextures(1, &DepthTextureCubemapArrayID_);
    SystemUtils_->Logger_->Log("Depth Map Subsystem Destroyed 3D Cubemap Array Texutre", 4);
    

}

bool ERS_CLASS_DepthMaps::RegenerateDepthMapTextureArray2D(int NumberOfTextures, int Width, int Height, bool LogEnabled) {


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
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
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

bool ERS_CLASS_DepthMaps::RegenerateDepthMapTextureArrayCubemap(int NumberOfTextures, bool LogEnabled) {


    SystemUtils_->Logger_->Log(
        std::string("Generating Depth Map Texture Cube Map Array Of ") + std::to_string(NumberOfTextures)
         + std::string(" Textures, With Width Of ") + std::to_string(DepthTextureArrayWidth_)
         + std::string(" Pixels, And Height Of ") + std::to_string(DepthTextureArrayHeight_)
         + std::string(" Pixels")
        , 5, LogEnabled);

    // Check If Already Texture, If So, Delete So We Can Overwrite it
    SystemUtils_->Logger_->Log("Checking If Texture Cubemap Array Already Exists", 4, LogEnabled);
    bool TextureAlreadyExists = glIsTexture(DepthTextureCubemapArrayID_);
    if (TextureAlreadyExists) {
        SystemUtils_->Logger_->Log("Cubemap Array ID Already In Use, Freeing First", 3, LogEnabled);
        glDeleteTextures(1, &DepthTextureCubemapArrayID_);
    } else {
        SystemUtils_->Logger_->Log("Cubemap Array ID Not Already In Use", 3, LogEnabled);
    }

    // Handle The Creation Of A New Texture Array
    SystemUtils_->Logger_->Log("Setting Up Cubemap Texture Array Metadata", 3, LogEnabled);
    DepthTextureCubemapNumTextures_ = NumberOfTextures;

    SystemUtils_->Logger_->Log("Setting Up Cubemap Texture Array OpenGL Parameters", 4, LogEnabled);
    glGenTextures(1, &DepthTextureCubemapArrayID_);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, DepthTextureCubemapArrayID_);

    for (unsigned int i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, DepthTextureArrayWidth_, DepthTextureArrayHeight_, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    float BorderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_BORDER_COLOR, BorderColor); 

    glTexImage3D(GL_TEXTURE_CUBE_MAP_ARRAY,
        0,                        // Current 'mipmap level', We're not using these so 0 is fine
        GL_DEPTH_COMPONENT24,     // Storage Format, Using Depth Format Here As We're Setting Up A Depth Map
        DepthTextureArrayWidth_,  // Cubemap Width
        DepthTextureArrayHeight_, // Cubemap Height
        NumberOfTextures * 6,     // Total Number Of Textures In The Array
        0,                        // Border, we're not using this
        GL_DEPTH_COMPONENT,       // Tells opengl what kind of data we're storing in this texture
        GL_FLOAT,                 // tells opengl how to store the data
        NULL                      // if we were loading an image in, we could then pass the data in here, but we're not so this is left as null
    );
    glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, 0);


 
    SystemUtils_->Logger_->Log("Cubemap Depth Map Texture Array Initialization Complete", 4, LogEnabled);



    if (!glIsFramebuffer(CubemapFBO_)) {
        glGenFramebuffers(1, &CubemapFBO_);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, CubemapFBO_);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, DepthTextureCubemapArrayID_, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    // Update Allocation Array
    SystemUtils_->Logger_->Log("Checking Cubemap Depth Map Texture Array Allocation Array", 3, LogEnabled);
    unsigned long SizeOfAllocationArray = DepthMapTexturesCubemapAlreadyAllocated_.size();
    if (SizeOfAllocationArray > (unsigned int)NumberOfTextures) {
        SystemUtils_->Logger_->Log("Downsizing Cubemap Array To Match Target Number Of Textures", 4, LogEnabled);
        DepthMapTexturesCubemapAlreadyAllocated_.erase(DepthMapTexturesCubemapAlreadyAllocated_.begin() + NumberOfTextures, DepthMapTexturesCubemapAlreadyAllocated_.end());
    } else if (SizeOfAllocationArray < (unsigned int)NumberOfTextures) {
        SystemUtils_->Logger_->Log("Upsizing Cubemap Array To Match Target Number Of Textures", 4, LogEnabled);
        for (unsigned int i = 0; i < NumberOfTextures - SizeOfAllocationArray; i++) {
            DepthMapTexturesCubemapAlreadyAllocated_.push_back(false);
        }
    }

    // for (unsigned int i = 0; i < DepthMapTexturesCubemapAlreadyAllocated_.size(); i++) {

    //     long ID = DepthMapTexturesCubemapAlreadyAllocated_[i];

    //     // Check If Valid ID
    //     if (glIsFramebuffer(ID)) {
            
    //     } else if (ID != -1) {
    //         SystemUtils_->Logger_->Log("Framebuffer Object Is Invalid, Removing From Allocation Table", 4, LogEnabled);
    //         DepthMapTexturesCubemapAlreadyAllocated_[i] = -1;
    //     }

    // }
    SystemUtils_->Logger_->Log("Done Updating/Checking Cubemap Allocation Array", 3, LogEnabled);




    return true;

}

bool ERS_CLASS_DepthMaps::FreeDepthMapIndex2D(unsigned int Index) {

    // Sanity Check
    if (Index > DepthMapTexturesAlreadyAllocated_.size() - 1) {
        return false; // Indicate Failure, Out Of Range
    }

    // DeAllocate From Array
    DepthMapTexturesAlreadyAllocated_[Index] = -1;
    return true;

}

bool ERS_CLASS_DepthMaps::FreeDepthMapIndexCubemap(unsigned int Index) {

    // Sanity Check
    if (Index > DepthMapTexturesCubemapAlreadyAllocated_.size() - 1) {
        return false; // Indicate Failure, Out Of Range
    }

    // DeAllocate From Array
    DepthMapTexturesCubemapAlreadyAllocated_[Index] = -1; //ERS_STRUCT_CubemapFBOIndexes();
    return true;

}

unsigned int ERS_CLASS_DepthMaps::AllocateDepthMapIndex2D(unsigned int FramebufferObjectID) {

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
    RegenerateDepthMapTextureArray2D(StartSize + DepthMapAllocationChunkSize_, DepthTextureArrayWidth_, DepthTextureArrayHeight_);
    SystemUtils_->Logger_->Log(std::string("Finished Updating Depth Map Array, Allocating Depth Map Texture Array Index: ") + std::to_string(StartSize + DepthMapAllocationChunkSize_), 5);

    DepthMapTexturesAlreadyAllocated_[StartSize + 1] = FramebufferObjectID;

    return StartSize + 1;

}


// unsigned int ERS_CLASS_DepthMaps::AllocateDepthMapIndexCubemap() {

//     // If Enough Textures Exist, Find One
//     SystemUtils_->Logger_->Log("Allocating Cubemap Depth Map Texture Array Index", 5);
//     for (unsigned int i = 0; i < DepthMapTexturesCubemapAlreadyAllocated_.size(); i++) {
//         if (DepthMapTexturesCubemapAlreadyAllocated_[i] == -1) {
//             SystemUtils_->Logger_->Log(std::string("Allocated Cubemap Depth Map Texture Array Index: ") + std::to_string(i), 5);
//             DepthMapTexturesCubemapAlreadyAllocated_[i] = FramebufferObjectID;
//             return i;
//         }
//     }

//     // IF Not, Batch Allocate More
//     SystemUtils_->Logger_->Log("Depth Cubemap Map Texture Array Full, Regenerating With More Textures", 5);
//     int StartSize = DepthMapTexturesCubemapAlreadyAllocated_.size();
//     RegenerateDepthMapTextureArrayCubemap(StartSize + DepthMapAllocationChunkSize_);
//     SystemUtils_->Logger_->Log(std::string("Finished Updating Cubemap Depth Map Array, Allocating Depth Map Texture Array Index: ") + std::to_string(StartSize + DepthMapAllocationChunkSize_), 5);

//     DepthMapTexturesCubemapAlreadyAllocated_[StartSize + 1] = FramebufferObjectID;

//     return StartSize + 1;

// }


unsigned int ERS_CLASS_DepthMaps::AllocateDepthMapIndexCubemap() {

    // If Enough Textures Exist, Find One
    SystemUtils_->Logger_->Log("Allocating Cubemap Depth Map Texture Array Index", 5);
    for (unsigned int i = 0; i < DepthMapTexturesCubemapAlreadyAllocated_.size(); i++) {
        if (DepthMapTexturesCubemapAlreadyAllocated_[i] == false) {
            SystemUtils_->Logger_->Log(std::string("Allocated Cubemap Depth Map Texture Array Index: ") + std::to_string(i), 5);
            DepthMapTexturesCubemapAlreadyAllocated_[i] = true;
            return i;
        }
    }

    // IF Not, Batch Allocate More
    SystemUtils_->Logger_->Log("Depth Cubemap Map Texture Array Full, Regenerating With More Textures", 5);
    int StartSize = DepthMapTexturesCubemapAlreadyAllocated_.size();
    RegenerateDepthMapTextureArrayCubemap(StartSize + DepthMapAllocationChunkSize_);
    SystemUtils_->Logger_->Log(std::string("Finished Updating Cubemap Depth Map Array, Allocating Depth Map Texture Array Index: ") + std::to_string(StartSize + DepthMapAllocationChunkSize_), 5);

    DepthMapTexturesCubemapAlreadyAllocated_[StartSize + 1] = true;

    return StartSize + 1;

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
        RegenerateDepthMapTextureArray2D(DepthTextureNumTextures_, DepthTextureArrayWidth_, DepthTextureArrayHeight_);
        RegenerateDepthMapTextureArrayCubemap(DepthTextureCubemapNumTextures_);
    }

}

ERS_STRUCT_DepthMap ERS_CLASS_DepthMaps::GenerateDepthMap2D(int Number, bool LogEnable) {


    SystemUtils_->Logger_->Log(std::string("Creating ") + std::to_string(Number) + std::string(" Depth Map(s) With Resolution Of ") + std::to_string(DepthTextureArrayWidth_) + std::string("x") + std::to_string(DepthTextureArrayHeight_), 5, LogEnable);

    // Setup Struct
    ERS_STRUCT_DepthMap Output;


    // Generate FBO
    SystemUtils_->Logger_->Log("Generating Framebuffer Object", 4, LogEnable);
    glGenFramebuffers(1, &Output.FrameBufferObjectID);
    
    SystemUtils_->Logger_->Log("Generated Framebuffer Object", 3, LogEnable);

    // Allocate Depth Map Texture ID
    Output.DepthMapTextureIndex = AllocateDepthMapIndex2D(Output.FrameBufferObjectID);

    // Attach Depth Map Texture To Framebuffer
    SystemUtils_->Logger_->Log(std::string("Attaching Depth Map Texture To Framebuffer Texture '") + std::to_string(Output.DepthMapTextureIndex) + std::string("'"), 4, LogEnable);
    glBindFramebuffer(GL_FRAMEBUFFER, Output.FrameBufferObjectID);
    glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, DepthTextureArrayID_, 0, Output.DepthMapTextureIndex);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0); 
    SystemUtils_->Logger_->Log("Finished Attaching Texture To Framebuffer", 3, LogEnable);

    

    Output.Initialized = true;

    // Return Output
    return Output;

}

// ERS_STRUCT_DepthMap ERS_CLASS_DepthMaps::GenerateDepthMapCubemap(bool LogEnable) {

//     // SystemUtils_->Logger_->Log(std::string("Creating Cubemap Depth Map With Resolution Of ") + std::to_string(DepthTextureArrayWidth_) + std::string("x") + std::to_string(DepthTextureArrayHeight_), 5, LogEnable);

//     // // Setup Struct
//     // ERS_STRUCT_DepthMap Output;


//     // // Generate FBOs
//     // SystemUtils_->Logger_->Log("Generating Cubemap Framebuffer Objects", 4, LogEnable);
//     // glGenFramebuffers(1, &Output.FrameBufferObjectID);
//     // SystemUtils_->Logger_->Log("Generated Cubemap Framebuffer Objects", 3, LogEnable);


//     // Allocate Depth Map Texture ID
//     Output.DepthMapTextureIndex = AllocateDepthMapIndexCubemap(Output.FrameBufferObjectID);

//     // Attach Depth Map Texture To Framebuffer
//     SystemUtils_->Logger_->Log(std::string("Attaching Cubemap Depth Map Texture To Framebuffer Texture '") + std::to_string(Output.DepthMapTextureIndex) + std::string("'"), 4, LogEnable);
//     glBindFramebuffer(GL_FRAMEBUFFER, Output.FrameBufferObjectID);
//     glDrawBuffer(GL_NONE);
//     glReadBuffer(GL_NONE);
//     SystemUtils_->Logger_->Log("Finished Attaching Cubemap Texture To Framebuffer", 3, LogEnable);

    
//     Output.Initialized = true;

//     // Return Output
//     return Output;

// }


// TODO: Remove extra light space matrix array junk, and also remove extra texture index array stuff.
// Then, implement cubemap array texture to allow us to render many point lights, add to depthmap struct to store the opengl ids needed for this
// finally, update the visual renderer to use this, and update the shader to use these cubemaps.

void ERS_CLASS_DepthMaps::UpdateDepthMap(ERS_STRUCT_DirectionalLight* Light, ERS_STRUCT_Shader* DepthShader) {

    // Check Settings
    CheckSettings();

    // Setup Variables
    glm::mat4* LightSpaceMatrixArray = &Light->DepthMap.TransformationMatrix;
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
    *LightSpaceMatrixArray = ObjectSpace;

    glViewport(0, 0, DepthTextureArrayWidth_, DepthTextureArrayHeight_);
    glBindFramebuffer(GL_FRAMEBUFFER, Light->DepthMap.FrameBufferObjectID);

    
    glClear(GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    Renderer_->RenderSceneNoTextures(TargetScene, DepthShader);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    

}

void ERS_CLASS_DepthMaps::UpdateDepthMap(ERS_STRUCT_PointLight* Light, ERS_STRUCT_Shader* DepthShader) {

    // Check Settings
    CheckSettings();

    // Setup Variables
    ERS_STRUCT_Scene* TargetScene = ProjectUtils_->SceneManager_->Scenes_[ProjectUtils_->SceneManager_->ActiveScene_].get();
    float NearPlane, FarPlane;
    NearPlane = 0.1f;
    FarPlane = Light->MaxDistance;

    // Calculate Project, View, Space Matrices
    float AspectRatio = DepthTextureArrayWidth_ / DepthTextureArrayHeight_;
    glm::mat4 ShadowProjection = glm::perspective(glm::radians(90.0f), AspectRatio, NearPlane, FarPlane); // Perspective models regular light source
    
    std::vector<glm::mat4> ShadowTransforms;
    ShadowTransforms.push_back(ShadowProjection * glm::lookAt(Light->Pos, Light->Pos + glm::vec3( 1.0, 0.0, 0.0), glm::vec3(0.0,-1.0, 0.0)));
    ShadowTransforms.push_back(ShadowProjection * glm::lookAt(Light->Pos, Light->Pos + glm::vec3(-1.0, 0.0, 0.0), glm::vec3(0.0,-1.0, 0.0)));
    ShadowTransforms.push_back(ShadowProjection * glm::lookAt(Light->Pos, Light->Pos + glm::vec3( 0.0, 1.0, 0.0), glm::vec3(0.0, 0.0, 1.0)));
    ShadowTransforms.push_back(ShadowProjection * glm::lookAt(Light->Pos, Light->Pos + glm::vec3( 0.0,-1.0, 0.0), glm::vec3(0.0, 0.0,-1.0)));
    ShadowTransforms.push_back(ShadowProjection * glm::lookAt(Light->Pos, Light->Pos + glm::vec3( 0.0, 0.0, 1.0), glm::vec3(0.0,-1.0, 0.0)));
    ShadowTransforms.push_back(ShadowProjection * glm::lookAt(Light->Pos, Light->Pos + glm::vec3( 0.0, 0.0,-1.0), glm::vec3(0.0,-1.0, 0.0)));



    // Render All Sides
    glViewport(0, 0, DepthTextureArrayWidth_, DepthTextureArrayHeight_);
    glBindFramebuffer(GL_FRAMEBUFFER, CubemapFBO_);//Light->DepthMap.FrameBufferObjectID);
    DepthShader->MakeActive();

    // Render With Depth Shader
    //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, DepthTextureCubemapArrayID_, Light->DepthMap.DepthMapTextureIndex*6, 0);
    for (unsigned int i = 0; i < ShadowTransforms.size(); i++) {
        DepthShader->SetMat4(std::string("ShadowMatrices[") + std::to_string(i) + std::string("]"), ShadowTransforms[i]);
    }

    // These uniforms don't seem to do anything in the geometry shader - perhaps there's something special we need to do? Or perhaps there's something special about sampling to a framebuffer?
    // Not sure what's going on but try setting the gl_FraPos in the vert shader manually to figure out what's going on so that we can get this problem resolved.

    DepthShader->SetVec3("LightPos", Light->Pos);
    DepthShader->SetFloat("FarPlane", Light->MaxDistance);
    glClear(GL_DEPTH_BUFFER_BIT);
    //glActiveTexture(GL_TEXTURE0);
    Renderer_->RenderSceneNoTextures(TargetScene, DepthShader);

}

void ERS_CLASS_DepthMaps::UpdateDepthMap(ERS_STRUCT_SpotLight* Light, ERS_STRUCT_Shader* DepthShader) {

    // Check Settings
    CheckSettings();


    // Setup Variables
    glm::mat4* LightSpaceMatrixArray = &Light->DepthMap.TransformationMatrix;
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
    *LightSpaceMatrixArray = ObjectSpace;

    glViewport(0, 0, DepthTextureArrayWidth_, DepthTextureArrayHeight_);
    glBindFramebuffer(GL_FRAMEBUFFER, Light->DepthMap.FrameBufferObjectID);
    glClear(GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    Renderer_->RenderSceneNoTextures(TargetScene, DepthShader);

}

void ERS_CLASS_DepthMaps::UpdateDepthMaps(ERS_STRUCT_Shader* DepthShader,  ERS_STRUCT_Shader* CubemapDepthShader) {


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
            Light->DepthMap = GenerateDepthMap2D();   
        }

        // Render To Depth Map
        UpdateDepthMap(Light, DepthShader);

    } 

    // Handle Spot Lights
    for (unsigned int i = 0; i < ActiveScene->SpotLights.size(); i++) {

        // Extract Struct
        ERS_STRUCT_SpotLight* Light = ActiveScene->SpotLights[i].get();

        // Check If Light Has DepthMap
        if (!Light->DepthMap.Initialized) {
            Light->DepthMap = GenerateDepthMap2D();   
        }

        // Render To Depth Map
        UpdateDepthMap(Light, DepthShader);

    }

    // Handle Point Lights
    for (unsigned int i = 0; i < ActiveScene->PointLights.size(); i++) {

        // Extract Struct
        ERS_STRUCT_PointLight* Light = ActiveScene->PointLights[i].get();

        // Check If Light Has DepthMap
        if (!Light->DepthMap.Initialized) {
            Light->DepthMap.DepthMapTextureIndex = AllocateDepthMapIndexCubemap();
            Light->DepthMap.Initialized = true;
        }

        // Render To Depth Map
        UpdateDepthMap(Light, CubemapDepthShader);


    } 


    // Return To Normal Culling
    glCullFace(GL_BACK);

}