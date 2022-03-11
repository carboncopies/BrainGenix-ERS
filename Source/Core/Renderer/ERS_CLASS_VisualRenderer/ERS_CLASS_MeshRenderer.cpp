//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_MeshRenderer.h>



ERS_CLASS_MeshRenderer::ERS_CLASS_MeshRenderer(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;
    SystemUtils_->Logger_->Log("Initializing MeshRenderer Class Instance", 5);

}

ERS_CLASS_MeshRenderer::~ERS_CLASS_MeshRenderer() {

    SystemUtils_->Logger_->Log("MeshRenderer Destructor Called", 6);

}


void ERS_CLASS_MeshRenderer::RenderScene(ERS_STRUCT_Scene* Scene, ERS_STRUCT_OpenGLDefaults* OpenGLDefaults, std::shared_ptr<ERS_STRUCT_Shader> Shader) {

    



}