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
    Logger_->Log("Populating Asset Index Metadata", 3);
    for (YAML::const_iterator it=AssetIndexMetadata.begin(); it!=AssetIndexMetadata.end(); ++it) {

        // Log Reading Of Asset With ID
        Logger_->Log(std::string(std::string("Loading Metadata For Asset With ID: ") + std::to_string(it->first.as<long>())).c_str(), 3);

        // Get Asset Metadata Node
        long Index = it->first.as<long>();
        YAML::Node AssetMetadata = it->second;

        // Populate Metadata
        AssetIDsFound_.push_back(Index);
        AssetTypeName_[Index] = {AssetMetadata["AssetType"].as<std::string>()};
        AssetCreationDate_[Index] = {AssetMetadata["AssetCreationDate"].as<std::string>()};
        AssetModificationDate_[Index] = {AssetMetadata["AssetModificationDate"].as<std::string>()};


    }
    Logger_->Log("Finished Populating Asset Index Metadata", 4);


    // Return Success
    return true;

}

// Write Asset Index
bool ERS_CLASS_AssetIndexIOM::WriteAssetIndex(std::shared_ptr<ERS_STRUCT_IOData> Data) {

    // Log Writing
    Logger_->Log("Writing Asset Database Metadata", 4);

    // Create Yaml Emitter
    YAML::Emitter Metadata;
    Metadata<<YAML::BeginMap;
    for (long i = 0; i < AssetIDsFound_.size(); i++) {
        
        // Log Asset ID Writing
        Logger_->Log(std::string(std::string("Serializing Metadata For Asset ") + std::to_string(AssetIDsFound_[i])).c_str(), 3);

        // Add To Metadata
        long CurrentIndex = AssetIDsFound_[i];
        Metadata<<YAML::Key<<CurrentIndex<<YAML::BeginMap;
        
        Metadata<<YAML::Key<<"AssetType"<<YAML::Value<<AssetTypeName_[CurrentIndex];
        

        Metadata<<YAML::EndMap;

    }
    Metadata<<YAML::EndMap;

    // Finish Writing
    Logger_->Log("Finished Writing Asset DB Metadata", 5);

}


