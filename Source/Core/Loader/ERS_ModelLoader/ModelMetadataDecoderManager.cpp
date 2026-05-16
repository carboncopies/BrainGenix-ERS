//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

// cppcheck-suppress missingIncludeSystem
#include <algorithm>

#include <ModelMetadataDecoderManager.h>


bool ERS_FUNCTION_DecodeModelMetadata(YAML::Node Metadata, ERS_STRUCT_Model* Model, ERS_STRUCT_SystemUtils* SystemUtils, long AssetID, bool LogEnable) {

    // Detect The Current Version
    SystemUtils->Logger_->Log("Attempting To Decode Model Metadata Version", 4, LogEnable);
    std::string FormatVersion = "0.0.0";
    if (Metadata["FormatVersion"]) {
        FormatVersion = Metadata["FormatVersion"].as<std::string>();
    }

    // Decode Based On Version
    bool Status = false;
    if (FormatVersion == "0.0.0") {
        SystemUtils->Logger_->Log("Determined Model Metadata Version To Be '0.0.0', Attempting To Decode Model Metadata", 3, LogEnable);
        ERS_FUNCTION_Legacy_PreprocessTextureInfo(Metadata, Model, SystemUtils, LogEnable);
        Status =  ERS_FUNCTION_DecodeModelMetadataV000(Metadata, Model, SystemUtils, AssetID, LogEnable);
    } else if (FormatVersion == "0.0.1") {
        SystemUtils->Logger_->Log("Determined Model Metadata Version To Be '0.0.1', Attempting To Decode Model Metadata", 3, LogEnable);
        ERS_FUNCTION_Legacy_PreprocessTextureInfo(Metadata, Model, SystemUtils, LogEnable);
        Status =  ERS_FUNCTION_DecodeModelMetadataV001(Metadata, Model, SystemUtils, AssetID, LogEnable);
    } else if (FormatVersion == "0.0.2") {
        SystemUtils->Logger_->Log("Determined Model Metadata Version To Be '0.0.2', Attempting To Decode Model Metadata", 3, LogEnable);
        Status =  ERS_FUNCTION_DecodeModelMetadataV002(Metadata, Model, SystemUtils, AssetID, LogEnable);
    } else {
        // Failed To Decode Version
        SystemUtils->Logger_->Log("Unsupported Format Version, Aborting Load", 8);
        return false;
    }


    // Sort All Texture Levels
    for (unsigned int TextureIndex = 0; TextureIndex < Model->Textures_.size(); TextureIndex++) {

        auto& TextureLevels = Model->Textures_[TextureIndex].TextureLevels;
        std::stable_sort(TextureLevels.begin(), TextureLevels.end(),
            [](const ERS_STRUCT_TextureLevel& A, const ERS_STRUCT_TextureLevel& B) {
                return A.Level < B.Level;
            });
    }

    return Status;
}
