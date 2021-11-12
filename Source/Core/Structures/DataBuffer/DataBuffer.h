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
    //std::vector<std::vector<int>, std::vector<float>> Test;
    //std::map<long, std::vector<int, int>> IndexMap; // Stores as follows: {AssetID: {Index Of Vector Stored In, Position In That Vector}}

    std::vector<std::variant<int, float>> Test;

    // Add Type
    void AddIntToBuffer(int Input, int ID) {

        Test.push_back(std::in_place_index_t<0>{}, 5); 

    }


};

