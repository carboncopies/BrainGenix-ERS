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
bool ERS_CLASS_AssetIndexIOM::LoadAssetIndex(std::shared_ptr<ERS_STRUCT_IOData> Data) {

    // Log Asset Index Decoding
    Logger_->Log("Loading Asset Index", 4);


    // Decode Asset Index Into YAML::Node
    Logger_->Log("Decoding Asset Index Data From Bytes", 3);
    std::string EncodedString = std::string((const char*)Data->Data.get());
    YAML::Node AssetIndexMetadata;
    try {
        AssetIndexMetadata = YAML::Load(EncodedString);
    } catch(YAML::BadFile) {
        Logger_->Log("Error Decoding, Invalid YAML Syntax", 9);
        return false;
    }
    Logger_->Log("Finished Decoding Asset Index", 4);


    // Clear Internal Maps
    Logger_->Log("Clearing Internal Maps For Asset Metadata", 3);
    AssetTypeName_.erase(AssetTypeName_.begin(), AssetTypeName_.end());
    AssetCreationDate_.erase(AssetCreationDate_.begin(), AssetCreationDate_.end());
    AssetModificationDate_.erase(AssetModificationDate_.begin(), AssetModificationDate_.end());
    Logger_->Log("Finsihed Clearing Internal Maps", 4);

    // Populate Maps


}