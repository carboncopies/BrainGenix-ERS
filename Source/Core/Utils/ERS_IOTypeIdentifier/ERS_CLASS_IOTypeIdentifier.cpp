//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_IOTypeIdentifier.h>


// Constructor
ERS_CLASS_IOTypeIdentifier::ERS_CLASS_IOTypeIdentifier(std::shared_ptr<LoggerClass> Logger) {
    
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


// ID Type
void ERS_CLASS_IOTypeIdentifier::IdentifyType(std::shared_ptr<ERS_STRUCT_IOData> Data) {

    // Read First 65535 Bytes For Metadata
    unsigned char* MetadataBytes = new unsigned char[65535];
    memcpy(MetadataBytes, Data->Data.get(), 65535);

    // Convert To YAML::Node
    

}