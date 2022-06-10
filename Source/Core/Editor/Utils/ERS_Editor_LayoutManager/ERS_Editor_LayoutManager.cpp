//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_Editor_LayoutManager.h>


ERS_CLASS_LayoutManager::ERS_CLASS_LayoutManager(ERS_CLASS_LoggingSystem* Logger, const char* UserProfilePath) {

    Logger_ = Logger;
    Logger_->Log("Initializing Layout Manager", 5);

 }


ERS_CLASS_LayoutManager::~ERS_CLASS_LayoutManager() {

    Logger_->Log("Layout Manager Destructor Called", 6);

}

bool ERS_CLASS_LayoutManager::IndexConfigs() {



}