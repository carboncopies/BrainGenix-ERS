//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file provides asset import functionality.
    Documentation Status: Complete
    Additonal Notes: None
    Date Created: 2021-12-18
*/

#pragma once


// Standard Libraries (BG convention: use <> instead of "")
#include <memory>
#include <string>
#include <vector>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <ERS_STRUCT_SystemUtils.h>


/**
 * @brief This class provides the backend to the import asset option within the file menu.
 *
 */
class ERS_CLASS_ImportAsset {

    private:

        std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils_; /**<used to get access to system utilites like IOmanager, logger, etc.*/
        std::mutex LockAssetImportQueue_; /**<Mutex used to control access to list of assets to be imported*/
        std::vector<std::string> AssetImportQueue_; /**<List of assets to be imported, accessed by other threads so use mutex to control access*/

        // Stats
        long CurrentSubitemTotal_; /**<Stats for the loading bar*/
        long CurrentSubitemIndex_; /**<Stats for the loading bar*/
        long TotalItemsToImport_; /**<Stats for the loading bar*/
        long TotalItemsProcessed_; /**<Stats for the loading bar*/


    public:


        /**
         * @brief Construct a new ers class importasset object
         * 
         * @param SystemUtils 
         */
        ERS_CLASS_ImportAsset(std::shared_ptr<ERS_STRUCT_SystemUtils> SystemUtils);

        /**
         * @brief Destroy the ers class importasset object
         * 
         */
        ~ERS_CLASS_ImportAsset();


        /**
         * @brief Add items to be imported.
         * 
         * @param AssetPaths 
         */
        void AddToImportQueue(std::vector<std::string> AssetPaths);

        /**
         * @brief Get the Total Subitems Imported number
         * 
         * @return long 
         */
        long GetTotalSubitemsImported();

        /**
         * @brief Get the Total Subitems number
         * 
         * @return long 
         */
        long GetTotalSubitems();

        long GetTotalItemsToImport();
        long GetTotalItemsImported();


};