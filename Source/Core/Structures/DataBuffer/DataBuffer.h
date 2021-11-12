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



struct ERS_STRUCTURE_DATA_BUFFER {

    // Create Data Buffer Vector
    std::vector<std::vector<std::variant<char, int, double>>> Test;


};

