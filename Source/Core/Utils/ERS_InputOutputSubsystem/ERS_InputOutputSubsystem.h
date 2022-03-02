//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <assert.h>
#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <mutex>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <thread>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_CLASS_AssetIndexIOM.h>
#include <ERS_CLASS_LoggingSystem.h>
#include <ERS_FUNCTION_CompareAssetIndexDelta.h>
#include <ERS_STRUCT_IOData.h>

/**
 * @brief This class provides a single input/ouput file operation system. It is
 * thread safe.
 *
 */
class ERS_CLASS_InputOutputSubsystem {

private:
  ERS_CLASS_LoggingSystem* Logger_; /**<Logging Class Pointer*/

public:
  std::unique_ptr<ERS_CLASS_AssetIndexIOM>
      AssetIndexIOManager_; /**<Pointer to Asset Index Metadata System*/

  std::string AssetPath_; /**<Relative Path To Prepend To All IO Operations,
                             Used By File Loading*/

  /**<List Of Asset IDs That Are Already In Use*/
  std::vector<long> UsedAssetIDs_;

  std::mutex LockAssetIDAllocation_; /**<Used When Allocating AssetIDs*/
  bool UseDatabase_; /**<Indicates If The Database Should Be Used For IO. Set By
                        LocalSystemConfiguration Values In Constructor*/

public:
  /**
   * @brief Construct a new ers class inputoutputsubsystem object
   *
   * @param Logger
   * @param LocalSystemConfiguration
   */
  ERS_CLASS_InputOutputSubsystem(
      ERS_CLASS_LoggingSystem* Logger,
      YAML::Node LocalSystemConfiguration);

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
  std::vector<long> BatchAllocateIDs(size_t NumberIDs);

  /**
   * @brief Write Asset Data To ID
   *
   * @param AssetID
   * @param AssetData
   * @return true
   * @return false
   */
  bool WriteAsset(long AssetID, ERS_STRUCT_IOData* AssetData);

  /**
   * @brief Batch Write Data to IDs, Both Lists Should Be The Same Length.
   * Returns List Of Status Variables (true=succes, false=fail)
   *
   * @param AssetIDs
   * @param AssetDatas
   * @return std::vector<bool>
   */
  std::vector<bool> BatchWriteAssets(
      std::vector<long> AssetIDs,
      std::vector<ERS_STRUCT_IOData*> AssetDatas);

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
   * @brief Read A List Of Assets From The Given IDs, Both Vectors Should Be
   * Equal In Length.
   *
   * @param AssetIDs
   * @param AssetDatas
   * @return std::vector<bool>
   */
  std::vector<bool> BatchReadAssets(
      std::vector<long> AssetIDs,
      std::vector<std::shared_ptr<ERS_STRUCT_IOData>> AssetDatas);

  /**
   * @brief Updates the list of used asset IDs to prevent accidental data loss.
   * Called during initialization.
   *
   */
  void IndexUsedAssetIDs();

  /**
   * @brief Update asset path to string passed in. This allows you to change
   * projects (IE: load another project, etc.) REMEMBER TO CALL ASSET ID
   * INDEXING AFTER THIS, ELSE DATA LOSS CAN OCCUR.
   *
   * @param AssetPath
   */
  void UpdateAssetPath(std::string AssetPath);
};
