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


// Export Helpers
bool ERS_CLASS_ModelWriter::WriteModelVertexData(ERS_STRUCT_ModelWriterData &Data, std::string ExportFormat) {

    // Export Model File
    Logger_->Log(std::string("Exporting Model Geometry To Blob With Encoding '") + ExportFormat + "'", 4);

    Assimp::Exporter Exporter;
    const aiExportDataBlob* Blob = Exporter.ExportToBlob(Data.ModelScene, ExportFormat);

    std::string ExportStatus = Exporter.GetErrorString();
    if (ExportStatus == "") {
        Logger_->Log(std::string("Finished Exporting Model Geometry To Blob"), 3);
    } else {
        Logger_->Log(std::string("Error Exporting Model Geometry '") + ExportStatus + "'", 7);
    }
    

    // Copy Model File
    std::unique_ptr<ERS_STRUCT_IOData> IOData = std::make_unique<ERS_STRUCT_IOData>();
    IOData->Data.reset(new unsigned char[Blob->size]);
    ::memcpy(IOData->Data.get(), Blob->data, Blob->size);
    IOData->Size_B = Blob->size;

    long ModelID = IOSubsystem_->AllocateAssetID();
    Logger_->Log(std::string(std::string("Assigning ID '") + std::to_string(ModelID) + std::string("' To Model '") + Data.Model->Name + std::string("'")).c_str(), 4);
    IOSubsystem_->WriteAsset(ModelID, IOData.get());    



}


std::string ERS_CLASS_ModelWriter::GenerateModelMetadata(ERS_STRUCT_Model* Model) {

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

void ERS_CLASS_ModelWriter::WriteModel(ERS_STRUCT_Model &Model) {



}


