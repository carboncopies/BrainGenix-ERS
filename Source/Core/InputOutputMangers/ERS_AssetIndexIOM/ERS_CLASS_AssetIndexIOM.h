 //======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//


#pragma once

// Standard Libraries (BG convention: use <> instead of "")
#include <memory>

// Third-Party Libraries (BG convention: use <> instead of "")
#include <yaml-cpp/yaml.h>

// Internal Libraries (BG convention: use <> instead of "")
#include <LoggingSystem.h>
#include <ERS_STRUCT_IOData.h>


class ERS_CLASS_AssetIndexIOM {

private:

    std::shared_ptr<LoggerClass> Logger_; /**<Pointer To Logger Instance*/
    

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
     * @brief Load The Asset Index Into Memory
     * 
     * @param Data 
     */
    void LoadAssetIndex(std::shared_ptr<ERS_STRUCT_IOData> Data);


};