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
    std::map<int, int> IndexMap; // Stores as follows: {AssetID: Index In Vector}
    std::vector<std::variant<int, double>> Test;

    // Add Type
    void AddIntToBuffer(int Input, int ID) {

        Test.push_back(5);
        IndexMap.push_back(IndexMap.size(), {{ID, Test.size()}})

    }


};

