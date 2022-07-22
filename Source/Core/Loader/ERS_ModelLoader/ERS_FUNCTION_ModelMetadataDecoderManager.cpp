//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_FUNCTION_ModelMetadataDecoderManager.h>


bool ERS_FUNCTION_DecodeModelMetadata(YAML::Node Metadata, ERS_STRUCT_Model* Model, ERS_STRUCT_SystemUtils* SystemUtils, long AssetID) {

    // Detect The Current Version
    std::string FormatVersion = "0.0.0";
    if (Metadata["FormatVersion"]) {
        FormatVersion = Metadata["FormatVersion"].as<std::string>();
    }

    // Decode Based On Version
    if (FormatVersion == "0.0.0") {

    } else if (FormatVersion == "0.0.1") {
        
    }


}