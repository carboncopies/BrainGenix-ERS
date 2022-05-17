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


    ERS_STRUCT_DepthMap Output;

    // Generate FBO
    
    glGenFramebuffers(1, &Output.FrameBufferObjectID);




}