//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file provides asset import functionality.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-18
*/

#include <ERS_Editor_ImportAsset.h>


// Asset Importer Constructor
ERS_CLASS_ImportAsset::ERS_CLASS_ImportAsset(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils) {

    // Copy Shared Pointer
    SystemUtils_ = SystemUtils;

}

