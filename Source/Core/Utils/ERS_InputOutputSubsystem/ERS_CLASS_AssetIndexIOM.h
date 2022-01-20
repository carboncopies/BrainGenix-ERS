//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//


#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <memory>
#include <map>
#include <thread>
#include <mutex>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>
#include <ERS_STRUCT_IOData.h>


class ERS_CLASS_AssetIndexIOM {

// Private Member Vars
private:

    std::shared_ptr<LoggerClass> Logger_; /**<Pointer To Logger Instance*/
    std::thread AssetMetadataWriterThread_; /**<Thread To Automatically Save Asset Metadata Periodically*/
    float AssetMetadataSavePerodicity_ = 5; /**<Save Asset Metadata With This Delay Inbetween (Units Are Seconds)*/
    std::mutex BlockThreads_; /**<Lock This To Block The Threads*/
    bool ExitThreads_ = false; /**<Set This To True To Make The Threads Exit*/


// Public Member Vars
public:

    std::map<long, std::string> AssetTypeName_; /**<Name of the type of asset, ex: Image or Model*/
    std::map<long, std::string> AssetCreationDate_; /**<Date when initially Allocated*/
    std::map<long, std::string> AssetModificationDate_; /**<Date When Last Modified*/
    std::vector<long> AssetIDsFound_; /**<List of all asset ids in metadata system*/

// Public Methods
public:

    /**
     * @brief Construct a new ers class assetindexIOM object
     * 
     * @param Logger 
     */
    ERS_CLASS_AssetIndexIOM(std::shared_ptr<LoggerClass> Logger);

    /**
     * @brief Destroy the ers class assetindexIOM object
     * 
     */
    ~ERS_CLASS_AssetIndexIOM();
    
    /**
     * @brief Loads the asset index data into memory which is used by the io subsystem.
     * 
     * @param Data 
     * @return true 
     * @return false 
     */
    bool LoadAssetIndex(std::shared_ptr<ERS_STRUCT_IOData> Data);

    /**
     * @brief Writes Asset Index Data To IOData Struct Passed In. Returns True/False For Success/Failure.
     * 
     * @param Data 
     * @return true 
     * @return false 
     */
    bool WriteAssetIndex(std::shared_ptr<ERS_STRUCT_IOData> Data);

};