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
#include <filesystem>
#include <thread>
#include <mutex>

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
        std::vector<long> UsedAssetIDs_; /**<List Of Asset IDs That Are Already In Use*/
        std::mutex LockAssetIDAllocation_; /**<Used When Allocating AssetIDs*/
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
         * @brief Returns an unused assetid that is guarenteed to not already exist.
         * 
         * @return long 
         */
        long AllocateAssetID();


        /**
         * @brief Allocate A Batch Of IDs For Usage, Returns Vector Of Allocated IDs
         * 
         * @param NumberIDs 
         * @return std::vector<long> 
         */
        std::vector<long> BatchAllocateIDs(int NumberIDs);


        /**
         * @brief Write Asset Data To ID
         * 
         * @param AssetID 
         * @param AssetData 
         * @return true 
         * @return false 
         */
        bool WriteAsset(long AssetID, std::shared_ptr<ERS_STRUCT_IOData> AssetData);

        /**
         * @brief Batch Write Data to IDs, Both Lists Should Be The Same Length. Returns List Of Status Variables (true=succes, false=fail)
         * 
         * @param AssetIDs 
         * @param AssetDatas 
         * @return std::vector<bool> 
         */
        std::vector<bool> BatchWriteAssets(std::vector<long> AssetIDs, std::vector<std::shared_ptr<ERS_STRUCT_IOData>> AssetDatas);

        /**
         * @brief Read Asset Data From ID
         * 
         * @param AssetID 
         * @param AssetData 
         * @return true 
         * @return false 
         */
        bool ReadAsset(long AssetID, std::shared_ptr<ERS_STRUCT_IOData> AssetData);

        /**
         * @brief Read A List Of Assets From The Given IDs, Both Vectors Should Be Equal In Length.
         * 
         * @param AssetIDs 
         * @param AssetDatas 
         * @return std::vector<bool> 
         */
        std::vector<bool> BatchReadAssets(std::vector<long> AssetIDs, std::vector<std::shared_ptr<ERS_STRUCT_IOData>> AssetDatas);


        /**
         * @brief Updates the list of used asset IDs to prevent accidental data loss. Called during initialization.
         * 
         */
        void IndexUsedAssetIDs();




};