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


// Setup Window Struct
void ERS_CLASS_WindowManager::GenerateWindowStruct(ERS_STRUCT_ProjectUtils* ProjectUtils, ERS_STRUCT_HumanInputDeviceUtils* HIDUtils,
ERS_STRUCT_ControllerSettings* ControllerSettings, ERS_CLASS_VisualRenderer* VisualRenderer,
ERS_CLASS_ThemeManager* ThemeManager, Cursors3D* Gizmo) {

    // Setup Window System
    SystemUtils_->Logger_->Log("WindowManager Subsystem Setting Up Window Struct", 4);


    


}