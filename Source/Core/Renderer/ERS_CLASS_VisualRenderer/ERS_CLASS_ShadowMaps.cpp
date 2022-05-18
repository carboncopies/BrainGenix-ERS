//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_ShadowMaps.h>


ERS_CLASS_ShadowMaps::ERS_CLASS_ShadowMaps(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils, ERS_CLASS_MeshRenderer* Renderer) {

    SystemUtils_ = SystemUtils;
    ProjectUtils_ = ProjectUtils;
    Renderer_ = Renderer;

    SystemUtils_->Logger_->Log("Initializing Shadow Map Subsystem", 5);
    ERS_CLASS_DepthMaps_ = std::make_unique<ERS_CLASS_DepthMaps>(SystemUtils_, ProjectUtils_, Renderer_); 


}

ERS_CLASS_ShadowMaps::~ERS_CLASS_ShadowMaps() {

    SystemUtils_->Logger_->Log("Viewport Overlay Subsystem Destructor Invoked", 6);

}


void ERS_CLASS_ShadowMaps::UpdateShadowMaps(ERS_STRUCT_Shader* DepthMapShader) {



}