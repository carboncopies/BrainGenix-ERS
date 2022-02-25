//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_LightIconRenderer.h>



ERS_CLASS_LightIconRenderer::ERS_CLASS_LightIconRenderer(ERS_STRUCT_SystemUtils* SystemUtils, std::shared_ptr<ERS_STRUCT_Shader> LightIconRendererShader) {


    SystemUtils_ = SystemUtils;
    LightIconRendererShader_ = LightIconRendererShader;


    SystemUtils_->Logger_->Log("Setting Up VisualRenderer LightIconRenderer System", 5);


}

ERS_CLASS_LightIconRenderer::~ERS_CLASS_LightIconRenderer() {

    SystemUtils_->Logger_->Log("LightIconRenderer Destructor Called", 6);

}