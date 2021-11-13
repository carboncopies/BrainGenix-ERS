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

#include "Core/Management/LoggingSystem.h"


class AssetLoader {

    private:

        // Init Vars
        LoggerClass *Logger_;
        YAML::Node *SystemConfiguration_;

        // Configuration Vars
        bool DatabaseLoadingEnabled_;

    public:

        // Constructor
        AssetLoader(LoggerClass *Logger, YAML::Node *SystemConfiguration);


};