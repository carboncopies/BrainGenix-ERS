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

    // Initialize Data Buffer
    DataBuffer_.Init(Logger_);

    // Iniitalize Image Loader (THIS SHOULD BE THREADS LATER ON...)
    ImageDecoder_.Initialize(Logger_);
    

    // Get Config Values
    Logger_->Log("Reading Configuration File For 'DatabaseLoadingEnabled' Parameter", 1);
    DatabaseLoadingEnabled_ = (*SystemConfiguration_)["DatabaseLoadingEnabled"].as<bool>();

    Logger_->Log("Reading Configuration File For 'AssetPath' Parameter", 1);
    AssetPath_ = (*SystemConfiguration_)["AssetPath"].as<std::string>();

    // TODO: ADD OTHER DB PARAMS HERE (SEE CONFIG FOR MORE INFO)
    // TODO: ADD CONFIG STRING FOR LOCAL FILE ASSET PATH (ALSO ADD TO CONFIG FILE)


    // Log Initialization
    Logger_->Log("Initialized Asset Loader Class", 5);

}

// Destructor
AssetLoader::~AssetLoader() {

    // Log Call
    Logger_->Log("Destructor Called For AssetLoader, Cleaning Up", 6);

    // Uninit ImageDecoder
    ImageDecoder_.Cleanup();

    // Uninit ERS Data Buffer
        // ADD ME LATER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

}


// Read Scene Subnodes And Load Models/Textures Requested By That Scene
void AssetLoader::LoadSceneAssets(ERS_OBJECT_SCENE InputScene) {

    // Iterate Through Scene Data, Load Non-Essential Assets (EG No Dependencies such as Images)
    for (long i = 0; i < (long)size(InputScene.Subnodes); i++) {

        // Get Subnode
        YAML::Node Subnode = InputScene.Subnodes[i];

        // Get Attributes
        long AssetID = Subnode["ID"].as<long>();
        std::string AssetType = Subnode["Type"].as<std::string>();


        // Load Image
        if (AssetType == "Image") {

            LoadImage(AssetID, Subnode);

        }

    }

    // Load Models
    for (long i = 0; i < (long)size(InputScene.Subnodes); i++) {

        // Get Subnode
        YAML::Node Subnode = InputScene.Subnodes[i];

        // Get Attributes
        long AssetID = Subnode["ID"].as<long>();
        std::string AssetType = Subnode["Type"].as<std::string>();


        // Load Model
        if (AssetType == "Model") {
            LoadModel(AssetID, Subnode);
        }

    }

}

// Load Model
void AssetLoader::LoadModel(long AssetID, YAML::Node Params) {

    // Load From DB
    if (DatabaseLoadingEnabled_) {

        // TODO: ADD DATABASE LOADING FUNCTIONALITY LATER!

    } else {

        // Calculate File Path
        std::string FilePath = AssetPath_;
        FilePath += std::to_string(AssetID);
        FilePath += std::string(".bg");

        // Load Model
        ERS_OBJECT_MODEL Model;
        Model.LoadModelFromFile(1, Logger_);

        // Place Into Data Buffer
        //DataBuffer_.Add_ERS_OBJECT_MODEL(Image, AssetID);

    }

}

// Load Image
void AssetLoader::LoadImage(long AssetID, YAML::Node Params) { // MAKE SURE TO COPY IN THE PATH FROM THE PARAMS VAR

    // Load From DB
    if (DatabaseLoadingEnabled_) {

        // TODO: ADD DATABASE LOADING FUNCTIONALITY LATER!

    } else {

        // Calculate File Path
        std::string FilePath = AssetPath_;
        FilePath += std::to_string(AssetID);
        FilePath += std::string(".bg");

        // Get Asset Path
        std::string Path = Params["Path"].as<std::string>();

        // Load Image
        ERSImage Image = ImageDecoder_.LoadImageFromFile(FilePath.c_str());

        // Place Into Data Buffer
        DataBuffer_.Add_ERS_OBJECT_IMAGE(Image, AssetID, Path);

    }

}

// Returns All Models Loaded In The Asset Buffer And Marked To Be Drawn
std::vector<ERS_OBJECT_MODEL*> AssetLoader::GetModelsToDraw() {

    // Create Pointer Vector
    std::vector<ERS_OBJECT_MODEL*> ModelPointers;

    // Get Struct Data
    for (long i = 0; i < (long)size(DataBuffer_.ERS_OBJECT_MODEL_Vector_); i++) {
        ModelPointers.push_back(&DataBuffer_.ERS_OBJECT_MODEL_Vector_[i]);
    }

    // Return Output
    return ModelPointers;


};
