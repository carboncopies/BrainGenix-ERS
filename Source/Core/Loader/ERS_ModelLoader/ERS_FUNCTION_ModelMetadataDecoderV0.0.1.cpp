//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_FUNCTION_ModelMetadataDecoderV0.0.0.h>


bool ERS_FUNCTION_DecodeModelMetadataV001(YAML::Node Metadata, ERS_STRUCT_Model* Model, ERS_STRUCT_SystemUtils* SystemUtils, long AssetID) {

    // Setup Processing Variables
    return false;
    // long ModelID;
    // std::vector<std::string> TexturePaths;
    // std::vector<long> TextureIDs;

    // // Attempt To Decode, Handle Errors
    // try {

    //     if (Metadata["Name"]) {
    //         std::string Name = Metadata["Name"].as<std::string>();
    //         if (Model->Name == std::string("Loading...")) {
    //             Model->Name = Name.substr(Name.find_last_of("/") + 1, Name.length()-1);
    //         } else {
    //             Model->Name = Name; 
    //         }
    //     } else {

    //         Model->Name = "_Error_";
    //         SystemUtils->Logger_->Log(std::string("Error Loading Name From Model Metadata '") + std::to_string(AssetID) + "'", 7); 
    //     }

    //     if (Metadata["ModelID"]) {
    //         Model->ModelDataID = Metadata["ModelID"].as<long>();
    //     } else {
    //         Model->ModelDataID = -1;
    //         SystemUtils->Logger_->Log(std::string("Error Loading 3DAssetID From Model Metadata '") + std::to_string(AssetID) + "'", 7); 
    //     }

    //     if (Metadata["TextureIDs"]) {
    //         YAML::Node TexturePathNode = Metadata["TextureIDs"];
    //         for (YAML::const_iterator it=TexturePathNode.begin(); it!=TexturePathNode.end(); ++it) {
    //             TexturePaths.push_back(it->first.as<std::string>());
    //             TextureIDs.push_back(it->second.as<long>());
    //         }
    //     } else {
    //         TexturePaths = std::vector<std::string>();
    //         TextureIDs = std::vector<long>();
    //         SystemUtils->Logger_->Log(std::string("Error Loading Texture Manifest From Model Metadata'") + std::to_string(AssetID) + "'", 7); 
    //     }

    // } catch(YAML::BadSubscript&) {
    //     SystemUtils->Logger_->Log(std::string(std::string("Error Loading Model '") + std::to_string(AssetID) + std::string("', Asset Metadata Corrupt")).c_str(), 9);
    //     return;

    // } catch(YAML::TypedBadConversion<long>&) {
    //     SystemUtils->Logger_->Log(std::string(std::string("Error Loading Model '") + std::to_string(AssetID) + std::string("', ModelID/TextureIDs Corrupt")).c_str(), 9);
    //     return;

    // } catch(YAML::TypedBadConversion<std::string>&) {
    //     SystemUtils->Logger_->Log(std::string(std::string("Error Loading Model '") + std::to_string(AssetID) + std::string("', Model Name Corrupt")).c_str(), 9);
    //     return;
    // } 


}