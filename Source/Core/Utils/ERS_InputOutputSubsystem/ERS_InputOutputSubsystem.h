//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is responsible for providing a single I/O interface for asset loading/saving.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-19
*/

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <assert.h>
#include <stdlib.h>
#include <chrono>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>

#include <ERS_STRUCT_IOData.h>


/**
 * @brief This class provides a single input/ouput file operation system. It is thread safe.
 * 
 */
class ERS_CLASS_InputOutputSubsystem {

    private:

        std::shared_ptr<LoggerClass> Logger_; /**<Logging Class Pointer*/
        std::string AssetPath_; /**<Relative Path To Prepend To All IO Operations, Used By File Loading*/
        bool UseDatabase_; /**<Indicates If The Database Should Be Used For IO. Set By LocalSystemConfiguration Values In Constructor*/

    public:

        /**
         * @brief Construct a new ers class inputoutputsubsystem object
         * 
         * @param Logger 
         * @param LocalSystemConfiguration 
         */
        ERS_CLASS_InputOutputSubsystem(std::shared_ptr<LoggerClass> Logger, YAML::Node LocalSystemConfiguration);
        
        /**
         * @brief Destroy the ers class inputoutputsubsystem object
         * 
         */
        ~ERS_CLASS_InputOutputSubsystem();

        /**
         * @brief Write Asset To ID
         * 
         * @param AssetID 
         * @param AssetData 
         */
        bool WriteAsset(long AssetID, std::shared_ptr<ERS_STRUCT_IOData> AssetData);

        /**
         * @brief Read Asset From ID
         * 
         * @param AssetID 
         * @return char* 
         */
        ERS_STRUCT_IOData ReadAsset(long AssetID);

};