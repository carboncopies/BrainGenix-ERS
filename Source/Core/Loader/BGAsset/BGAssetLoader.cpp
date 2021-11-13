//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for loading assets from the scene.
    Additonal Notes: None
    Date Created: 2021-10-13
*/ 

#include "BGAssetLoader.h"

////////////////////////
// TODO: RENAME ASSETLOADER TO ASSETMANAGER AND GIVE OWN ROOT DIR IN SOURCE TREE
////////////////////////

// Asset Loader Constructor
AssetLoader::AssetLoader(LoggerClass *Logger, YAML::Node *SystemConfiguration) {

    // Initialization Start
    Logger->Log("Initializing Asset Loader Class", 6);

    // Copy Pointer
    Logger_ = Logger;
    SystemConfiguration_ = SystemConfiguration;
    DataBuffer_ = DataBuffer;

    // Get Config Values
    DatabaseLoadingEnabled_ = (*SystemConfiguration_)["DatabaseLoadingEnabled"].as<bool>();
    // TODO: ADD OTHER DB PARAMS HERE (SEE CONFIG FOR MORE INFO)
    // TODO: ADD CONFIG STRING FOR LOCAL FILE ASSET PATH (ALSO ADD TO CONFIG FILE)


    // Log Initialization
    Logger_->Log("Initialized Asset Loader Class", 5);

}

// Read Scene Subnodes And Load Models/Textures Requested By That Scene
AssetLoader::LoadSceneAssets(ERS_OBJECT_SCENE InputScene) {

    // Iterate Through Scene Data
    for (long i = 0; i < InputScene.NumberSubnodes; i++) {

        // Get Subnode
        YAML::Node Subnode = InputScene.Subnodes[i];

        // Get Attributes
        long AssetID = Subnode["ID"].as<long>();
        std::string AssetType = Subnode["Type"].as<std::string>();

        std::cout<<AssetID<<AssetType<<std::endl;

    }

}

// Read Scene -> Load Images/etc [load model last] -> Push into data buffer