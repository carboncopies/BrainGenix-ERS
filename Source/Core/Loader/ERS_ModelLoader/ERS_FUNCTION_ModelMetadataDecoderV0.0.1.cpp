//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_FUNCTION_ModelMetadataDecoderV0.0.0.h>


bool ERS_FUNCTION_DecodeModelMetadataV001(YAML::Node Metadata, ERS_STRUCT_Model* Model, ERS_STRUCT_SystemUtils* SystemUtils, long AssetID) {


    // Setup Processing Variables
    bool DecodeStatus = true;

    // Attempt To Decode, Handle Errors
    try {

        SystemUtils->Logger_->Log("Decoding Model Metadata", 3);

        if (Metadata["Name"]) {
            std::string Name = Metadata["Name"].as<std::string>();
            Model->Name = Name.substr(Name.find_last_of("/") + 1, Name.length()-1);
        } else {
            Model->Name = "_Error_";
            SystemUtils->Logger_->Log(std::string("Error Loading Name From Model Metadata '") + std::to_string(AssetID) + "'", 7); 
            DecodeStatus = false;
        }

        if (Metadata["ModelID"]) {
            Model->ModelDataID = Metadata["ModelID"].as<long>();
        } else {
            Model->ModelDataID = -1;
            SystemUtils->Logger_->Log(std::string("Error Loading 3DAssetID From Model Metadata '") + std::to_string(AssetID) + "'", 7); 
            DecodeStatus = false;
        }

        if (Metadata["Textures"]) {
            YAML::Node TexturePathNode = Metadata["Textures"];
            for (YAML::const_iterator it=TexturePathNode.begin(); it!=TexturePathNode.end(); ++it) {

                // Setup Texture Struct
                ERS_STRUCT_Texture Texture;
                Texture.Path = it->first.as<std::string>();
                SystemUtils->Logger_->Log(std::string("Found Texture '") + Texture.Path + "'", 3);

                // Add All Levels To This Texture
                YAML::Node TextureLevels = it->second;
                for (YAML::const_iterator LevelIterator = TextureLevels.begin(); LevelIterator != TextureLevels.end(); ++LevelIterator) {

                    YAML::Node LevelInfo = LevelIterator->second;
                    Texture.LevelTextureIDs.push_back(LevelInfo["TextureLevelAssetID"].as<long>());
                    Texture.LevelMemorySizeBytes.push_back(LevelInfo["TextureLevelMemorySizeBytes"].as<int>());
                    Texture.LevelResolutions.push_back(std::make_pair(LevelInfo["TextureLevelResolutionX"].as<int>(), LevelInfo["TextureLevelResolutionY"].as<int>()));

                    SystemUtils->Logger_->Log(std::string("Detected Texture Level '") + std::to_string(LevelIterator->first.as<int>())
                    + "', Resolution '" + std::to_string(LevelInfo["TextureLevelResolutionX"].as<int>())
                    + "x" + std::to_string(LevelInfo["TextureLevelResolutionY"].as<int>())
                    + "'", 1);

                }

                Model->Textures_.push_back(Texture);
            }
        } else {
            SystemUtils->Logger_->Log(std::string("Error Loading Texture Manifest From Model Metadata'") + std::to_string(AssetID) + "'", 7); 
            DecodeStatus = false;
        }

        SystemUtils->Logger_->Log("Finished Decoding Model Metadata", 3);
        return DecodeStatus;

    } catch(YAML::BadSubscript&) {
        SystemUtils->Logger_->Log(std::string(std::string("Error Loading Model '") + std::to_string(AssetID) + std::string("', Asset Metadata Corrupt")).c_str(), 9);
        return false;

    } catch(YAML::TypedBadConversion<long>&) {
        SystemUtils->Logger_->Log(std::string(std::string("Error Loading Model '") + std::to_string(AssetID) + std::string("', ModelID/TextureIDs Corrupt")).c_str(), 9);
        return false;

    } catch(YAML::TypedBadConversion<std::string>&) {
        SystemUtils->Logger_->Log(std::string(std::string("Error Loading Model '") + std::to_string(AssetID) + std::string("', Model Name Corrupt")).c_str(), 9);
        return false;
    } 

}