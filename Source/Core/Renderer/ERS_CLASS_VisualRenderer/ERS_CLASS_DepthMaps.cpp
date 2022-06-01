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



}

ERS_CLASS_DepthMaps::~ERS_CLASS_DepthMaps() {

    SystemUtils_->Logger_->Log("Viewport Overlay Subsystem Destructor Invoked", 6);

}



bool ERS_CLASS_DepthMaps::RegenerateDepthMapTextureArray(int NumberOfTextures, int Width, int Height) {


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

    // Generate Depth Map Texture (What We Render The Depth Map To)
    SystemUtils_->Logger_->Log("Creating Depth Map Texture", 4, LogEnable);
    glGenTextures(1, &Output.DepthMapTextureID);
    glBindTexture(GL_TEXTURE_2D, Output.DepthMapTextureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, ResolutionX, ResolutionY, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER); 
    float BorderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, BorderColor);  
    SystemUtils_->Logger_->Log("Created Depth Map Texture", 3, LogEnable);

    // Attach Depth Map Texture To Framebuffer
    SystemUtils_->Logger_->Log("Attaching Depth Map Texture To Framebuffer", 4, LogEnable);
    glBindFramebuffer(GL_FRAMEBUFFER, Output.FrameBufferObjectID);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, Output.DepthMapTextureID, 0);
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
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, Target->DepthMapTextureID);
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