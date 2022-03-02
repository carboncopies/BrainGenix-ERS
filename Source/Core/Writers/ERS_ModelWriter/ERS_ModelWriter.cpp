//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_ModelWriter.h>


ERS_CLASS_ModelWriter::ERS_CLASS_ModelWriter(ERS_CLASS_LoggingSystem* Logger, ERS_CLASS_InputOutputSubsystem* IOSubsystem) {

    Logger_ = Logger;
    IOSubsystem_ = IOSubsystem;
    Logger_->Log("Initializing ERS ModelWriter Subsystem", 5);

}

ERS_CLASS_ModelWriter::~ERS_CLASS_ModelWriter() {

    Logger_->Log("ModelWriter Subsystem Destructor Invoked", 5);

}


std::string ERS_CLASS_ModelWriter::GenerateModelMetadata(std::shared_ptr<ERS_STRUCT_Model> Model) {

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


void ERS_CLASS_ModelWriter::WriteModel(ERS_STRUCT_IOData* ModelData, std::vector<std::shared_ptr<ERS_STRUCT_IOData>> TextureData, std::shared_ptr<ERS_STRUCT_Model> Model) {


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

    std::shared_ptr<ERS_STRUCT_IOData> Data = std::make_unique<ERS_STRUCT_IOData>();
    
    // Set Metadata
    Data->AssetTypeName = "Model";

    Data->Data.reset(new unsigned char[Metadata.size()]);
    ::memcpy(Data->Data.get(), Metadata.c_str(), Metadata.size());
    
    Data->Size_B = Metadata.size();

    long ID = IOSubsystem_->AllocateAssetID();
    IOSubsystem_->WriteAsset(ID, Data);

}