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

#include "Core/Structures/Scene/Scene.h"



struct ERS_STRUCTURE_DATA_BUFFER {

    // Create Buffers
    std::map<long, long> IndexMap; // Stores as follows: {AssetID: Index In Vector}
    std::vector<std::variant<ERS_STRUCTURE_SCENE>> Test;

    // Add To Data Buffer
    void AddToBuffer(auto Input, long ID, LoggerClass *Logger_, bool LoggerEnabled = false) {

        // If Logger Enabled, Log Entry To Buffer
        if (LoggerEnabled) {
            Logger_->Log(std::string(std::string("Adding Asset To Data Buffer With Index: ") + std::to_string(ID)).to_str(), 7);
        }

        Test.push_back(Input);
        IndexMap.insert({ID, (long)Test.size()});

    }


};

