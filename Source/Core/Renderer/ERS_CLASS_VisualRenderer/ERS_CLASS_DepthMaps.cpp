//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_DepthMaps.h>


ERS_CLASS_DepthMaps::ERS_CLASS_DepthMaps(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils) {

    SystemUtils_ = SystemUtils;
    ProjectUtils_ = ProjectUtils;

    SystemUtils_->Logger_->Log("Initializing Viewport Overlay Subsystem", 5);

}


ERS_CLASS_DepthMaps::~ERS_CLASS_DepthMaps() {

    SystemUtils_->Logger_->Log("Viewport Overlay Subsystem Destructor Invoked", 6);

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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
    SystemUtils_->Logger_->Log("Created Depth Map Texture", 3, LogEnable);

    // Attach Depth Map Texture To Framebuffer
    SystemUtils_->Logger_->Log("Attaching Depth Map Texture To Framebuffer", 4, LogEnable);
    glBindFramebuffer(GL_FRAMEBUFFER, Output.FrameBufferObjectID);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, Output.DepthMapTextureID, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0); 
    SystemUtils_->Logger_->Log("Finished Attaching Texture To Framebuffer", 3, LogEnable);


    // Return Output
    return Output;

}