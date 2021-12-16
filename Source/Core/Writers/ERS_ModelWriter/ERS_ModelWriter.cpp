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
    Metadata << YAML::Key << "Type" << YAML::Value << "Model";

    // Stop Writing, Return Metadata
    Metadata << YAML::EndMap;
    return std::string(Metadata.c_str());

}

// Write Model
void ERS_CLASS_ModelWriter::WriteModel(std::shared_ptr<ERS_OBJECT_MODEL> Model) {


    std::string Metadata = GenerateModelMetadata(Model);

    std::shared_ptr<ERS_STRUCT_IOData> Data = std::make_shared<ERS_STRUCT_IOData>();
    Data->Data = (unsigned char*)Metadata.c_str();
    IOSubsystem_->WriteAsset(0, Data);

}