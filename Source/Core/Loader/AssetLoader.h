//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the asset loader class.
    Additional Notes: None
    Date Created: 2021-11-17
*/

#pragma once

#include <yaml-cpp/yaml.h>

#include "LoggingSystem.h"

/**
 * @brief The Asset Loader provides a unified multithreaded system for loading assets from both local disk and network (Database) storage.
 * 
 */
class AssetLoader {

    private:

        LoggerClass* Logger_;


    public:

        /**
         * @brief Construct a new Asset Loader object
         * 
         */
        AssetLoader(LoggerClass* Logger, YAML::Node* InitialSystemConfig);

        /**
         * @brief Destroy the Asset Loader object
         * 
         */
        ~AssetLoader();

};