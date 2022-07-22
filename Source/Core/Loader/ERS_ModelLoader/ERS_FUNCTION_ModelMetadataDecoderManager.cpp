//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_FUNCTION_ModelMetadataDecoderManager.h>


bool ERS_FUNCTION_DecodeModelMetadata(YAML::Node Metadata, ERS_STRUCT_Model* Model, ERS_STRUCT_SystemUtils* SystemUtils, long AssetID) {

    // Detect The Current Version
    SystemUtils->Logger_->Log("Attempting To Decode Model Metadata Version", 4);
    std::string FormatVersion = "0.0.0";
    if (Metadata["FormatVersion"]) {
        FormatVersion = Metadata["FormatVersion"].as<std::string>();
    }

    // Decode Based On Version
    if (FormatVersion == "0.0.0") {
        SystemUtils->Logger_->Log("Determined Model Metadata Version To Be '0.0.0', Attempting To Decode Model Metadata", 3);
        return ERS_FUNCTION_DecodeModelMetadataV000(Metadata, Model, SystemUtils, AssetID);
    } else if (FormatVersion == "0.0.1") {
        SystemUtils->Logger_->Log("Determined Model Metadata Version To Be '0.0.1', Attempting To Decode Model Metadata", 3);
        return ERS_FUNCTION_DecodeModelMetadataV001(Metadata, Model, SystemUtils, AssetID);
    }

    // Failed To Decode Version
    SystemUtils->Logger_->Log("Failed To Decode Metadata Version, Aborting Load", 8);
    return false;

}