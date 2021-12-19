//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file provides asset import functionality.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-18
*/

#include <GUI_ImportAsset.h>


// Asset Importer Constructor
GUI_ImportAsset::GUI_ImportAsset(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils) {

    // Copy Shared Pointer
    SystemUtils_ = SystemUtils;

    // Log Init
    SystemUtils_->Logger_->Log("Initializing Asset Importer GUI", 5);

}


// Asset Importer Destructor
GUI_ImportAsset::~GUI_ImportAsset() {

    // Log Destructor
    SystemUtils_->Logger_->Log("Asset Importer GUI Destructor Called", 6);

}
