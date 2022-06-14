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

    glTexImage3D(GL_TEXTURE_CUBE_MAP_ARRAY,
        0,                        // Current 'mipmap level', We're not using these so 0 is fine
        GL_DEPTH_COMPONENT24,     // Storage Format, Using Depth Format Here As We're Setting Up A Depth Map
        DepthTextureArrayWidth_,  // Cubemap Width
        DepthTextureArrayHeight_, // Cubemap Height
        NumberOfTextures * 6,         // Total Number Of Textures In The Array
        0,                        // Border, we're not using this
        GL_DEPTH_COMPONENT,       // Tells opengl what kind of data we're storing in this texture
        GL_FLOAT,                 // tells opengl how to store the data
        NULL                      // if we were loading an image in, we could then pass the data in here, but we're not so this is left as null
    );

    for (unsigned int i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, DepthTextureArrayWidth_, DepthTextureArrayHeight_, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    float BorderColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_BORDER_COLOR, BorderColor); 
    SystemUtils_->Logger_->Log("Cubemap Depth Map Texture Array Initialization Complete", 4, LogEnabled);


    // Update Allocation Array
    SystemUtils_->Logger_->Log("Checking Cubemap Depth Map Texture Array Allocation Array", 3, LogEnabled);
    unsigned long SizeOfAllocationArray = DepthMapTexturesCubemapAlreadyAllocated_.size();
    if (SizeOfAllocationArray > (unsigned int)NumberOfTextures) {
        SystemUtils_->Logger_->Log("Downsizing Cubemap Array To Match Target Number Of Textures", 4, LogEnabled);
        DepthMapTexturesCubemapAlreadyAllocated_.erase(DepthMapTexturesCubemapAlreadyAllocated_.begin() + NumberOfTextures, DepthMapTexturesCubemapAlreadyAllocated_.end());
    } else if (SizeOfAllocationArray < (unsigned int)NumberOfTextures) {
        SystemUtils_->Logger_->Log("Upsizing Cubemap Array To Match Target Number Of Textures", 4, LogEnabled);
        for (unsigned int i = 0; i < NumberOfTextures - SizeOfAllocationArray; i++) {
            DepthMapTexturesCubemapAlreadyAllocated_.push_back(ERS_STRUCT_CubemapFBOIndexes());
        }
    }
    SystemUtils_->Logger_->Log("Done Updating/Checking Cubemap Allocation Array", 3, LogEnabled);


    // Rebind Any Framebuffers
    SystemUtils_->Logger_->Log("Rebinding Framebuffer Objects Cubemap Depth Textures", 4, LogEnabled);
    for (unsigned int i = 0; i < DepthMapTexturesCubemapAlreadyAllocated_.size(); i++) {

        long IDs[6];
        IDs[0] = DepthMapTexturesCubemapAlreadyAllocated_[i].FBO1;
        IDs[1] = DepthMapTexturesCubemapAlreadyAllocated_[i].FBO2;
        IDs[2] = DepthMapTexturesCubemapAlreadyAllocated_[i].FBO3;
        IDs[3] = DepthMapTexturesCubemapAlreadyAllocated_[i].FBO4;
        IDs[4] = DepthMapTexturesCubemapAlreadyAllocated_[i].FBO5;
        IDs[5] = DepthMapTexturesCubemapAlreadyAllocated_[i].FBO6;
        

        for (unsigned int x = 0; x < 6; x++) {

            // Check If Valid ID
            if (glIsFramebuffer(IDs[x])) {

                // If Valid, Rebind
                SystemUtils_->Logger_->Log(std::string("Rebinding Framebuffer '") + std::to_string(IDs[x]) + std::string("' To Texture At Index '") + std::to_string(i*6 + x) + std::string("'"), 4, LogEnabled);
                glBindFramebuffer(GL_FRAMEBUFFER, IDs[x]);
                glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, DepthTextureArrayID_, 0, i*6 + x);
            
            } else if (IDs[x] != -1) {
                SystemUtils_->Logger_->Log("Framebuffer Object Is Invalid, Removing From Allocation Table", 4, LogEnabled);
                DepthMapTexturesCubemapAlreadyAllocated_[i] = ERS_STRUCT_CubemapFBOIndexes();
            }

        }

    }

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
    DepthMapTexturesCubemapAlreadyAllocated_[Index] = ERS_STRUCT_CubemapFBOIndexes();
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

unsigned int ERS_CLASS_DepthMaps::AllocateDepthMapIndexCubemap(ERS_STRUCT_CubemapFBOIndexes FBOs) {

    // If Enough Textures Exist, Find One
    SystemUtils_->Logger_->Log("Allocating Cubemap Depth Map Texture Array Index", 5);
    for (unsigned int i = 0; i < DepthMapTexturesCubemapAlreadyAllocated_.size(); i++) {
        if (DepthMapTexturesCubemapAlreadyAllocated_[i].FBO1 == -1) {
            SystemUtils_->Logger_->Log(std::string("Allocated Cubemap Depth Map Texture Array Index: ") + std::to_string(i), 5);
            DepthMapTexturesCubemapAlreadyAllocated_[i] = FBOs;
            return i;
        }
    }

    // IF Not, Batch Allocate More
    SystemUtils_->Logger_->Log("Depth Cubemap Map Texture Array Full, Regenerating With More Textures", 5);
    int StartSize = DepthMapTexturesCubemapAlreadyAllocated_.size();
    RegenerateDepthMapTextureArrayCubemap(StartSize + DepthMapAllocationChunkSize_);
    SystemUtils_->Logger_->Log(std::string("Finished Updating Cubemap Depth Map Array, Allocating Depth Map Texture Array Index: ") + std::to_string(StartSize + DepthMapAllocationChunkSize_), 5);

    DepthMapTexturesCubemapAlreadyAllocated_[StartSize + 1] = FBOs;

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

    // Iterate Over Total Quantity To Be Generated
    for (unsigned int i = 0; i < (unsigned int)Number; i++) {

        // Generate FBO
        SystemUtils_->Logger_->Log("Generating Framebuffer Object", 4, LogEnable);
        unsigned int FBOID;
        glGenFramebuffers(1, &FBOID);
        Output.FrameBufferObjectIDs.push_back(FBOID);
        SystemUtils_->Logger_->Log("Generated Framebuffer Object", 3, LogEnable);

        // Allocate Depth Map Texture ID
        Output.DepthMapTextureIndexes.push_back(AllocateDepthMapIndex2D(Output.FrameBufferObjectIDs[i]));

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



ERS_STRUCT_DepthMap ERS_CLASS_DepthMaps::GenerateDepthMapCubemap(bool LogEnable) {


    SystemUtils_->Logger_->Log(std::string("Creating Cubemap Depth Map With Resolution Of ") + std::to_string(DepthTextureArrayWidth_) + std::string("x") + std::to_string(DepthTextureArrayHeight_), 5, LogEnable);

    // Setup Struct
    ERS_STRUCT_DepthMap Output;


    for (unsigned int i = 0; i < 6; i++) {

        // Generate FBOs
        SystemUtils_->Logger_->Log("Generating Framebuffer Objects", 4, LogEnable);
        unsigned int FBOID;
        glGenFramebuffers(1, &FBOID);
        Output.FrameBufferObjectIDs.push_back(FBOID);
        SystemUtils_->Logger_->Log("Generated Framebuffer Objects", 3, LogEnable);

    }

    // Allocate Depth Map Texture ID
    Output.DepthMapTextureIndexes.push_back(AllocateDepthMapIndex2D(Output.FrameBufferObjectIDs[i]));

    // Attach Depth Map Texture To Framebuffer
    SystemUtils_->Logger_->Log(std::string("Attaching Depth Map Texture To Framebuffer Texture '") + std::to_string(Output.DepthMapTextureIndexes[i]) + std::string("'"), 4, LogEnable);
    glBindFramebuffer(GL_FRAMEBUFFER, Output.FrameBufferObjectIDs[i]);
    glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, DepthTextureArrayID_, 0, Output.DepthMapTextureIndexes[i]);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0); 
    SystemUtils_->Logger_->Log("Finished Attaching Texture To Framebuffer", 3, LogEnable);

    
    Output.Initialized = true;

    // Return Output
    return Output;

}


// TODO: Remove extra light space matrix array junk, and also remove extra texture index array stuff.
// Then, implement cubemap array texture to allow us to render many point lights, add to depthmap struct to store the opengl ids needed for this
// finally, update the visual renderer to use this, and update the shader to use these cubemaps.

void ERS_CLASS_DepthMaps::UpdateDepthMap(ERS_STRUCT_DirectionalLight* Light, ERS_STRUCT_Shader* DepthShader) {

    // Check Settings
    CheckSettings();

    // Clear LSM Array
    std::vector<glm::mat4>* LightSpaceMatrixArray = &Light->DepthMap.TransformationMatricies;
    LightSpaceMatrixArray->clear();

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
    LightSpaceMatrixArray->push_back(ObjectSpace);

    glViewport(0, 0, DepthTextureArrayWidth_, DepthTextureArrayHeight_);
    glBindFramebuffer(GL_FRAMEBUFFER, Light->DepthMap.FrameBufferObjectIDs[0]);

    
    glClear(GL_DEPTH_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    Renderer_->RenderSceneNoTextures(TargetScene, DepthShader);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    

}

void ERS_CLASS_DepthMaps::UpdateDepthMap(ERS_STRUCT_PointLight* Light, ERS_STRUCT_Shader* DepthShader) {

    // Check Settings
    CheckSettings();

    // Clear LSM Array
    std::vector<glm::mat4>* LightSpaceMatrixArray = &Light->DepthMap.TransformationMatricies;
    LightSpaceMatrixArray->clear();

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
        LightSpaceMatrixArray->push_back(ShadowTransforms[i]);

        glViewport(0, 0, DepthTextureArrayWidth_, DepthTextureArrayHeight_);
        glBindFramebuffer(GL_FRAMEBUFFER, Light->DepthMap.FrameBufferObjectIDs[i]); // fix this later
        glClear(GL_DEPTH_BUFFER_BIT);
        glActiveTexture(GL_TEXTURE0);
        Renderer_->RenderSceneNoTextures(TargetScene, DepthShader);

        //glBindFramebuffer(GL_FRAMEBUFFER, 0);

    }

}

void ERS_CLASS_DepthMaps::UpdateDepthMap(ERS_STRUCT_SpotLight* Light, ERS_STRUCT_Shader* DepthShader) {

    // Check Settings
    CheckSettings();

    // Clear LSM Array
    std::vector<glm::mat4>* LightSpaceMatrixArray = &Light->DepthMap.TransformationMatricies;
    LightSpaceMatrixArray->clear();

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
    LightSpaceMatrixArray->push_back(ObjectSpace);
    

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
            Light->DepthMap = GenerateDepthMap2D(6); // Point lights need 6 depth maps for a "cubemap", which is a shadow map for each side of the cube, allowing shadows around the light in all directions
        }

        // Render To Depth Map
        UpdateDepthMap(Light, DepthShader); // set this to false later, debugging


    } 


    // Return To Normal Culling
    glCullFace(GL_BACK);

}