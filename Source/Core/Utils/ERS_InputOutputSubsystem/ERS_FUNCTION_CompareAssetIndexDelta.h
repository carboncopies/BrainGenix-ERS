//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <vector>
#include <map>
#include <memory>

// Third-Party Libraries (BG convention: use <> instead of "")

// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>
#include <ERS_CLASS_AssetIndexIOM.h>


/**
 * @brief This function is used to compare the differences between actual assets and asset metadata to check for potential issues
 * 
 * @param Logger
 * @param UsedAssetIDIndex 
 * @param AssetIndexIOM 
 */
void ERS_FUNCTION_CompareIndexDelta(std::shared_ptr<LoggerClass> Logger, std::shared_ptr<std::vector<long>> UsedAssetIDIndex, std::shared_ptr<ERS_CLASS_AssetIndexIOM> AssetIndexIOM);
