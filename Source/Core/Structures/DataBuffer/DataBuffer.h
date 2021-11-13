//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file is responsible for implementing in-memory storage of all loaded assets.
    Additonal Notes: None
    Date Created: 2021-11-12
*/   

#pragma once


#include <vector>
#include <variant>

#include "Core/Management/LoggingSystem.h"

#include "Core/Structures/Scene/Scene.h"
#include "Core/Structures/Model/Model.h"




struct ERS_STRUCTURE_DATA_BUFFER {

    // Create Internal Structures
    struct VectorData {

        std::string AssetType; // Stores Type Of Object, EG: "ERS_OBJECT_MODEL" or "ERS_OBJECT_SCENE"
        long VectorIndex; // Stores Position In Given Vector

    };

    // Internal Vars
    LoggerClass *Logger_ = nullptr;

    // Create Buffers
    std::map<long, VectorData> MetadataMap_;
    std::vector<ERS_OBJECT_MODEL> ERS_OBJECT_MODEL_Vector_;
    std::vector<ERS_OBJECT_SCENE> ERS_OBJECT_MODEL_Scene_;



    // Initialize Buffer
    void Init( LoggerClass *Logger) {

        // Copy Pointer To The Logger
        Logger_ = Logger;

        // Log System Initialization
        Logger_->Log("Initialized ERS Data Buffer", 6);

    }

    // Add Types To Buffer
    void Add_ERS_OBJECT_MODEL(ERS_OBJECT_MODEL Input, long AssetID) {

        // Add Model To Buffer
        ERS_OBJECT_MODEL_Vector_.push_back(Input);

        VectorData AssetData;
        AssetData.AssetType = "ERS_OBJECT_MODEL";
        AssetData.VectorIndex = (long)ERS_OBJECT_MODEL_Vector_.size()-1;

        MetadataMap_.insert({AssetID, AssetData});

        // Log Model Loading
        if (Logger_ != nullptr) {
            Logger_->Log(std::string(std::string("Adding ERS_OBJECT_MODEL Asset To Data Buffer With Global Asset ID: ") + std::to_string(AssetID)).c_str(), 7);
        }

    }



};

