//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing scene decoding.
    Additonal Notes: None
    Date Created: 2021-10-13
*/ 

#pragma once

#include "yaml-cpp/yaml.h"

#include "LoggingSystem.h"
#include "Scene.h"
#include "DataBuffer.h"
#include "ImageDecoder.h"
#include "Model.h"


class AssetLoader {

    private:

        // Init Vars
        LoggerClass *Logger_;
        YAML::Node *SystemConfiguration_;
        ERS_STRUCTURE_DATA_BUFFER DataBuffer_;
        ImageDecoder ImageDecoder_;

        // Configuration Vars
        bool DatabaseLoadingEnabled_;
        std::string AssetPath_;

        // Loading Methods
        void LoadImage(long AssetID, YAML::Node Params);
        void LoadModel(long AssetID, YAML::Node Params);

    public:

        // Constructor
        AssetLoader(LoggerClass *Logger, YAML::Node *SystemConfiguration);

        // Destructor
        ~AssetLoader();

        // Load Assets From Scene
        void LoadSceneAssets(ERS_OBJECT_SCENE InputScene);

        // Return Models To Be Drawn
        std::vector<ERS_OBJECT_MODEL*> GetModelsToDraw();



};