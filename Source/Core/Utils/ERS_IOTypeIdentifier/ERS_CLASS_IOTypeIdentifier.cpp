//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_IOTypeIdentifier.h>


// Constructor
ERS_CLASS_IOTypeIdentifier::ERS_CLASS_IOTypeIdentifier(std::shared_ptr<ERS_CLASS_LoggingSystem> Logger) {
    
    // Copy Logger Pointer
    Logger_ = Logger;

    // Log Initialization
    Logger_->Log("Initializing IO Type Identification System", 5);

}


// Destructor
ERS_CLASS_IOTypeIdentifier::~ERS_CLASS_IOTypeIdentifier() {

    // Log Destructor Call
    Logger_->Log("IO Type Identification System Destructor Called", 6);

}

