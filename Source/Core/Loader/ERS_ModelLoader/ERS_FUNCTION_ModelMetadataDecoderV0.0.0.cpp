//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_FUNCTION_ModelMetadataDecoderV0.0.0.h>


bool ERS_FUNCTION_DecodeModelMetadataV000(YAML::Node Source, ERS_STRUCT_Model* Model) {

    // Process Metadata
    std::string Name;
    long ModelID;
    std::vector<std::string> TexturePaths;
    std::vector<long> TextureIDs;
    try {
        Name = Metadata["Name"].as<std::string>();
        ModelID = Metadata["ModelID"].as<long>();
        YAML::Node TexturePathNode = Metadata["TextureIDs"];
        for (YAML::const_iterator it=TexturePathNode.begin(); it!=TexturePathNode.end(); ++it) {
            TexturePaths.push_back(it->first.as<std::string>());
            TextureIDs.push_back(it->second.as<long>());
        }
    } catch(YAML::BadSubscript&) {
        SystemUtils_->Logger_->Log(std::string(std::string("Error Loading Model '") + std::to_string(AssetID) + std::string("', Asset Metadata Corrupt")).c_str(), 9);
        return;
    } catch(YAML::TypedBadConversion<long>&) {
        SystemUtils_->Logger_->Log(std::string(std::string("Error Loading Model '") + std::to_string(AssetID) + std::string("', ModelID/TextureIDs Corrupt")).c_str(), 9);
        return;        
    } catch(YAML::TypedBadConversion<std::string>&) {
        SystemUtils_->Logger_->Log(std::string(std::string("Error Loading Model '") + std::to_string(AssetID) + std::string("', Model Name Corrupt")).c_str(), 9);
        return;        
    } 

    if (Model->Name == std::string("Loading...")) {
        Model->Name = Name.substr(Name.find_last_of("/") + 1, Name.length()-1);
    }

}