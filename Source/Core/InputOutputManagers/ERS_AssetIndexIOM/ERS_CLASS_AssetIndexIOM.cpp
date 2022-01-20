//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_CLASS_AssetIndexIOM.h>


// Constructor
ERS_CLASS_AssetIndexIOM::ERS_CLASS_AssetIndexIOM(std::shared_ptr<LoggerClass> Logger) {

    // Copy Logger Pointer
    Logger_ = Logger;

    // Log Initialization Start
    Logger_->Log("Initializing ERS Asset Index Input/Output Manager", 5);

}

// Destructor
ERS_CLASS_AssetIndexIOM::~ERS_CLASS_AssetIndexIOM() {

    // Log Destructor Call
    Logger_->Log("ERS Asset Index Input/Output Manager Destructor Called", 6);

}


// Load Asset Index
void ERS_CLASS_AssetIndexIOM::LoadAssetIndex(std::shared_ptr<ERS_STRUCT_IOData> Data) {

    // Log Asset Index Decoding
    Logger_->Log("Loading Asset Index", 4);


    // Decode Asset Index Into YAML::Node
    Logger_->Log("Decoding Asset Index Data From Bytes", 3);

    Logger_->Log("Finished Decoding Asset Index", 3);

}