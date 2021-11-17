//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This is the asset loader queue struct.
    Additional Notes: None
    Date Created: 2021-11-17
*/

#pragma once

#include <vector>

/**
 * @brief Declare ERS Structure For Asset Loader Queue. Used as a queue of assets to be loaded. (FIXME: MAKE THREAD SAFE!)
 * 
 */
struct ERS_STRUCT_ASSET_LOADER_QUEUE {

    /**
     * @brief queue used to store list of assets to load
     * 
     */
    std::vector<long> AssetIDLoadingQueue;

    
    /**
     * @brief Add Item To Queue
     * 
     * @param QueueID 
     */
    void EmplaceItem(long QueueID);

    /**
     * @brief Get Item From Queue
     * 
     * @return long 
     */
    long GetItem();

};