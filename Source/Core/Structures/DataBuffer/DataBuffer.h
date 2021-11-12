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



struct ERS_STRUCTURE_DATA_BUFFER {

    // Internal Vars
    LoggerClass *Logger_ = nullptr;

    // Create Buffers
    std::map<long, long> IndexMap; // Stores as follows: {AssetID: Index In Vector}
    std::vector<std::variant<ERS_STRUCTURE_SCENE, int>> StructureBuffer;


    // Initialize Buffer
    void Init( LoggerClass *Logger) {

        // Copy Pointer To The Logger
        Logger_ = Logger;

        // Log System Initialization
        Logger_->Log("Initialized ERS Data Buffer", 6);

    }

    // Add To Data Buffer
    void AddToBuffer(auto Input, long ID) {

        // If Logger Enabled, Log Entry To Buffer
        if (Logger_ != nullptr) {
            Logger_->Log(std::string(std::string("Adding Asset To Data Buffer With Index: ") + std::to_string(ID)).c_str(), 7);
        }

        StructureBuffer.push_back(Input);
        IndexMap.insert({ID, (long)StructureBuffer.size()});

    }

    // Get Data From Buffer
    auto* PullFromBuffer(long ID) {

        // Get Data From Buffer
        long VectorIndex = IndexMap[ID];
        return &StructureBuffer[VectorIndex];

    }


};

