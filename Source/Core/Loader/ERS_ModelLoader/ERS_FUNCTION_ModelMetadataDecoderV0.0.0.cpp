//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_FUNCTION_ModelMetadataDecoderV0.0.0.h>


bool ERS_FUNCTION_DecodeModelMetadataV000(YAML::Node Metadata, ERS_STRUCT_Model* Model, ERS_STRUCT_SystemUtils* SystemUtils, long AssetID) {

    // Setup Processing Variables
    bool DecodeStatus = true;

    // Attempt To Decode, Handle Errors
    try {


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

        if (Metadata["TextureIDs"]) {
            YAML::Node TexturePathNode = Metadata["TextureIDs"];
            for (YAML::const_iterator it=TexturePathNode.begin(); it!=TexturePathNode.end(); ++it) {
                ERS_STRUCT_Texture Texture;
                Texture.Path = it->first.as<std::string>();
                Texture.LevelTextureAssetIDs.push_back(it->second.as<long>());
                Texture.LevelTextureOpenGLIDs.push_back(0);
                Texture.LevelLoadedInRAM.push_back(false);
                Texture.LevelLoadedInVRAM.push_back(false);
                Texture.LevelChannels.push_back(-1);
                Texture.LevelBitmaps.push_back(nullptr);
                Texture.LevelMemorySizeBytes.push_back(-1);
                Texture.LevelResolutions.push_back(std::make_pair(-1, -1));
                Model->Textures_.push_back(Texture);
                Model->MaxTextureLevel_ = 0;
            }
        } else {
            SystemUtils->Logger_->Log(std::string("Error Loading Texture Manifest From Model Metadata'") + std::to_string(AssetID) + "'", 7); 
            DecodeStatus = false;
        }

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