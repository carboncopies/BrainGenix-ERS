//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for implementing hardware information collection.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-03
*/

#include <HardwareInformation.h>


// HWinfo Constructor
HardwareInformation::HardwareInformation(LoggerClass *Logger) {

    // Copy Pointers
    Logger_ = Logger;

    // Log Initialization
    Logger_->Log("Initializing Hardware Info Subsystem", 5);

    // Collect Static Hardware Information
    Logger_->Log("Collecting Static Hardware Information", 4);

    



}