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
    AssetIDsFound_.erase(AssetIDsFound_.begin(), AssetIDsFound_.end());
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

    // Log Serialization
    Logger_->Log("Serializing Asset Database Metadata", 4);

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
        Metadata<<YAML::Key<<"AssetCreationDate"<<YAML::Value<<AssetCreationDate_[CurrentIndex];
        Metadata<<YAML::Key<<"AssetModificationDate"<<YAML::Value<<AssetModificationDate_[CurrentIndex];

        Metadata<<YAML::EndMap;

    }
    Metadata<<YAML::EndMap;

    // Convert To String
    std::string ByteString = std::string(Metadata.c_str());

    // Finish Serialization
    Logger_->Log("Finished Serializing Asset DB Metadata", 5);


    // Add To Data Struct
    Logger_->Log("Adding Encoded Metadata String To IOData Struct", 3);

        
    Data->Data.reset(new unsigned char[ByteString.size()]);
    Data->Size_B = ByteString.size();
    memcpy(Data->Data.get(), ByteString.c_str(), ByteString.size());

    // Finish Adding To Struct
    Logger_->Log("Finished Adding Encoded Metadata String To IOData Struct", 4);

    // Return Success
    return true;

}

// Update Asset Metadata Info
void ERS_CLASS_AssetIndexIOM::UpdateAssetIndex(long AssetID, std::shared_ptr<ERS_STRUCT_IOData> Data) {

    // Extract Relevant Params
    std::string AssetType = Data->AssetTypeName;
    std::string Modified = Data->AssetModificationDate;
    std::string Created = Data->AssetCreationDate;

    // Add To Internal Maps
    AssetTypeName_[AssetID] = {AssetType};
    AssetCreationDate_[AssetID] = {Created};
    AssetModificationDate_[AssetID] = {Modified};

    // Check If Already In Loaded Assets, If Not, Add
    bool AlreadyInIndex = false;
    for (long i = 0; i < AssetIDsFound_.size(); i++) {
        if (AssetIDsFound_[i] == AssetID) {
            AlreadyInIndex = true;
            break;
        }
    }
    if (!AlreadyInIndex) {
        AssetIDsFound_.push_back(AssetID);
    }
    

}

