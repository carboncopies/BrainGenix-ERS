//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_ViewportOverlay.h>


ERS_CLASS_ViewportOverlay::ERS_CLASS_ViewportOverlay(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;

    SystemUtils_->Logger_->Log("Initializing Viewport Overlay Subsystem", 5);

}


ERS_CLASS_ViewportOverlay::~ERS_CLASS_ViewportOverlay() {

    SystemUtils_->Logger_->Log("Viewport Overlay Subsystem Destructor Invoked", 6);

}


void ERS_CLASS_ViewportOverlay::DrawOverlay(ERS_STRUCT_Viewport* Viewport) {

    // 

}