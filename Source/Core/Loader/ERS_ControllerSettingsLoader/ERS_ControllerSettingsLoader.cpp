//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the controller settings loader system.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2022-01-09
*/

#include <ERS_ControllerSettingsLoader.h>


// Constructor
ERS_CLASS_ControllerSettingsLoader::ERS_CLASS_ControllerSettingsLoader(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils) {

    // Copy Pointer
    SystemUtils_ = SystemUtils;

    // Log Initialization
    SystemUtils_->Logger_->Log("Initializing ERS Controller Settings Loader", 5);

}


// Destructor
ERS_CLASS_ControllerSettingsLoader::~ERS_CLASS_ControllerSettingsLoader() {

    // Log Destructor Call
    SystemUtils_->Logger_->Log("ERS Controller Settings Loader Destructor Called", 4);

};


// Load System Controller Settings
bool ERS_CLASS_ControllerSettingsLoader::LoadControllerSettings(std::shared_ptr<ERS_STRUCT_ControllerSettings> ControllerSettings, long AssetID) {
    
}