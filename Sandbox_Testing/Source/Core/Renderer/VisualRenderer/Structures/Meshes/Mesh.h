//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file creates the ERSMesh Struct/Functions.
    Additonal Notes: None
    Date Created: 2021-11-04
*/

#pragma once

#include <glm/glm.hpp>

#define MAX_BONE_INFLUENCE 4


struct ERS_OBJECT_MESH {

    // Set Metadata
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec3 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;

    int BoneIDs[MAX_BONE_INFLUENCE];
    float Weights[MAX_BONE_INFLUENCE];


    // Set Helper Vars
    _HasInitialized = false;


    // Define Helper Functions
    void Initialize() {
        _HasInitialized = true;
    }

    void IsInitialized() {
        return _HasInitialized;
    }


};