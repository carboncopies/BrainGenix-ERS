//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file contains the model writer class.
    Documentation Status: Completed
    Additonal Notes: None
    Date Created: 2021-11-22
*/

#include <ERS_ModelWriter.h>


// Constructor
ERS_CLASS_ModelWriter::ERS_CLASS_ModelWriter(std::shared_ptr<LoggerClass> Logger, std::shared_ptr<ERS_CLASS_InputOutputSubsystem> IOSubsystem) {

    // Copy Shared Pointers
    Logger_ = Logger;
    IOSubsystem_ = IOSubsystem;

    // Log Initialization
    Logger_->Log("Initializing ERS ModelWriter Subsystem", 5);

}

// Destructor
ERS_CLASS_ModelWriter::~ERS_CLASS_ModelWriter() {

    // Log Destructor Call
    Logger_->Log("ModelWriter Subsystem Destructor Invoked", 5);

}


// Generate Model Metadata
std::string ERS_CLASS_ModelWriter::GenerateModelMetadata(std::shared_ptr<ERS_OBJECT_MODEL> Model) {

    // Create Model Metadata, Begin Writing
    YAML::Emitter Metadata;
    Metadata << YAML::BeginMap;

    // Set Constant Info
    Metadata << YAML::Key << "Type" << YAML::Value << "ModelDescriptor";
    Metadata << YAML::Key << "FormatVersion" << YAML::Value << "0.0.1";

    // Stop Writing, Return Metadata
    Metadata << YAML::EndMap;
    return std::string(Metadata.c_str());

}

// Write Model
void ERS_CLASS_ModelWriter::WriteModel(
    std::shared_ptr<ERS_STRUCT_IOData> ModelData,
    std::vector<std::shared_ptr<ERS_STRUCT_IOData>> TextureData, 
    std::shared_ptr<ERS_OBJECT_MODEL> Model) {

    // Copy Model Data
    long ModelID = IOSubsystem_->AllocateAssetID();
    IOSubsystem_->WriteAsset(ModelID, ModelData);
    Model->ModelDataID = ModelID;


    // Copy Textures
    std::vector<long> TextureIDs = IOSubsystem_->BatchAllocateIDs(TextureData.size());
    IOSubsystem_->BatchWriteAssets(TextureIDs, TextureData);
    Model->TextureIDs = TextureIDs;


    // Write Model Metadata
    std::string Metadata = GenerateModelMetadata(Model);

    std::shared_ptr<ERS_STRUCT_IOData> Data = std::make_shared<ERS_STRUCT_IOData>();
    Data->Data.reset(new unsigned char[Metadata.size()]);
    ::memcpy(Data->Data.get(), Metadata.c_str(), Metadata.size());
    
    Data->Size_B = Metadata.size();

    long ID = IOSubsystem_->AllocateAssetID();
    IOSubsystem_->WriteAsset(0, Data);

}