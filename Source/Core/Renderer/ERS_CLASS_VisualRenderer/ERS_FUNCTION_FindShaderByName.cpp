//======================================================================//
// This file is part of the BrainGenix-ERS Environment Rendering System //
//======================================================================//

#include <ERS_FUNCTION_CheckForMeshTransparency.h>


void ERS_FUNCTION_FindShaderByName(std::string Name, ) {

    long Index = 0;
    for (unsigned long i = 0; i < Shaders_.size(); i++) {
        if (Shaders_[i]->InternalName == Name) {
            Index = i;
            break;
        }
    }

    return Index;

}