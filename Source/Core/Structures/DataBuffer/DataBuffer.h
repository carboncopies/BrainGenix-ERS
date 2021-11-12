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



struct ERS_STRUCTURE_DATA_BUFFER {

    // Create Data Buffers
    std::vector<std::vector<int>, std::vector<float>> Test;

    // Add Type
    void AddStructToBuffer(auto Input);

        std::cout<<typeid(Input).name()<<std::endl;


};

