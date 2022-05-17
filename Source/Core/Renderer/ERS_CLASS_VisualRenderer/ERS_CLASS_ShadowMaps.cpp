//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_ShadowMaps.h>


ERS_CLASS_ShadowMaps::ERS_CLASS_ShadowMaps(ERS_STRUCT_SystemUtils* SystemUtils, ERS_STRUCT_ProjectUtils* ProjectUtils) {

    SystemUtils_ = SystemUtils;
    ProjectUtils_ = ProjectUtils;

    SystemUtils_->Logger_->Log("Initializing Viewport Overlay Subsystem", 5);

}

ERS_CLASS_ShadowMaps::~ERS_CLASS_ShadowMaps() {

    SystemUtils_->Logger_->Log("Viewport Overlay Subsystem Destructor Invoked", 6);

}

