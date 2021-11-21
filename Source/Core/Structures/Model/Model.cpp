//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

/*
    Description: This file creates the ERSModel Struct/Functions.
    Additonal Notes: None
    Date Created: 2021-11-04
*/ 


#include "Model.h"


// Draw Model
void ERS_OBJECT_MODEL::Draw(ERS_OBJECT_SHADER &Shader) {

    // Draw All Meshes
    for (unsigned int i=0; i<Meshes.size(); i++) {
        Meshes[i].Draw(Shader);
    }

}