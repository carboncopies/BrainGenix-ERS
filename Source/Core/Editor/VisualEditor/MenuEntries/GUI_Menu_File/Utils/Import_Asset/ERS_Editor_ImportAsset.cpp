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

    // Log Init
    SystemUtils_->Logger_->Log("Initializing Asset Importer Backend", 5);

}


// Asset Importer Destructor
ERS_CLASS_ImportAsset::~ERS_CLASS_ImportAsset() {

    // Log Destructor
    SystemUtils_->Logger_->Log("Asset Importer Backend Destructor Called", 6);

}

// Call To Add Items To Import List
void ERS_CLASS_ImportAsset::AddToImportQueue(std::vector<std::string> AssetPaths) {

    

}