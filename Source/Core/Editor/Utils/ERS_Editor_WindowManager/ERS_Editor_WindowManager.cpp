//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_Editor_WindowManager.h>


ERS_CLASS_WindowManager::ERS_CLASS_WindowManager(ERS_STRUCT_SystemUtils* SystemUtils) {

    SystemUtils_ = SystemUtils;
    SystemUtils_->Logger_->Log("Initializing WindowManager Subsystem", 4);



}

ERS_CLASS_WindowManager::~ERS_CLASS_WindowManager() {

    SystemUtils_->Logger_->Log("WindowManager Subsystem Destructor Called", 6);

}


