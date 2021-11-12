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
#include <typeinfo>

#include <iostream>



struct ERS_STRUCTURE_DATA_BUFFER {

    // Create Buffers
    std::vector<std::vector<int>, std::vector<float>> Test;
    std::map<long, std::map<long, long>> IndexMap; // Stores as follows: {AssetID: {Index Of Vector Stored In, Position In That Vector}}

    // Add Type
    void AddIntToBuffer(int Input, long ID) {

        Test[0].push_back(Input);

        std::map<long, long> InsertMap = {0, Test[0].size()};
        IndexMap[ID] = InsertMap;
    
    }


};

